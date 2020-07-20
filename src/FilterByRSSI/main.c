#include "../includes/comm.h"
#include "../includes/regs_ctrl.h"
#include "../includes/mac_regs.h"
#include "../includes/mac_cmd.h"
#include "../includes/pkt_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>

#define ANTENNA_PORT 0
#define ANTENNA_POWER 330 	// 30 dB
#define DWELL_TIME 150		// ms
#define LOGIC_ANTENNAS 1

#define LT_TH_1 0x02 //Less than threeshold 1
#define GT_TH_1 0x12 //Greater than  threeshold 1
#define EQ_TH_1 0x22 //Equal than threeshold 1
#define GT_TH_1_LT_2 0x32 //Greater than th1 less than th2
#define LT_TH_1_GT_2 0x42 //Less than th1 and greater than th2

int fd;

// Uart thread initially stopped
int threadControl = 0;
// Print the rssi value from frame
int16_t getRssi(char * frame){
	int16_t rssi = 0;
	rssi = frame[8];
	rssi += frame[9]<<8;
	return rssi;
}

//Configure the filter RSSI
void filterByRSSI(int fd,u_int8_t type,float threeshold_1,float threeshold_2){

	u_int16_t u_th1 = (u_int16_t) ((int)(threeshold_1*10.0)); 
	u_int16_t u_th2 = (u_int16_t) ((int)(threeshold_2*10.0));
	u_int8_t th_1[2] = {u_th1 & 0xFF,u_th1 >> 8};
	u_int8_t th_2[2] = {u_th2 & 0xFF,u_th2 >> 8};
//FILTERING RSSI 
	AppEntry_R2000WriteRegister(fd, HST_INV_RSSI_FILTERING_CONFIG, type, 0x00, 0x00, 0x00);
	AppEntry_R2000WriteRegister(fd, HST_INV_RSSI_FILTERING_THRESHOLD, th_1[0],th_1[1] ,th_2[0], th_1[1]);
}

//Callback to receive the RFID frames
void onPacketReceived(int fd,u_int8_t *databuf,u_int16_t framelength,u_int16_t pkt_type)
{
    int i = 0;
	switch(pkt_type){
		case CMD_BEGIN:
			printf("INVENTORY STARTED\n");
		break;
		case INV:
			printf("TAG_RECEIVED length %i\n",(int)framelength);
			for (i=0;i<framelength;i++){
        		printf("%02X",databuf[i]);
   			}
			printf(" %.1f \n",(float)((float)getRssi(databuf)/10.0));
		break;
		case CMD_ACTIVE:
			printf("COMMAND ACTIVE\n");
		break;
		case CMD_END:
			printf("INVENTORY END\n");
		break;
		default:
			printf("UNKNOWN PACKET TYPE %04X\n", pkt_type);
		break;
	}
}

void configureAntennas(int fd) {

	int logic_antenna, antenna_port;
	uint8_t powerBytes[2];
  	uint8_t dwellBytes[2];

	powerBytes[0] = ANTENNA_POWER & 0xFF;
	powerBytes[1] = ANTENNA_POWER >> 8;

	dwellBytes[0] = DWELL_TIME & 0xFF;
	dwellBytes[1] = DWELL_TIME >> 8;

	printf("Antenna ports: %d\n", ANTENNA_POWER);
	printf("Logic antennas: %d\n", LOGIC_ANTENNAS);
	printf("Antenna power: %d\n", ANTENNA_POWER);
	printf("Dwell time: %d\n", DWELL_TIME);
	printf("\n");

	// Infinity antenna cycles
	AppEntry_R2000WriteRegister(fd, HST_ANT_CYCLES, 0xFF, 0xFF, 0x00, 0x00); 

	for (logic_antenna = 0; logic_antenna < LOGIC_ANTENNAS; logic_antenna++) {

		// antenna_port = getPhysicalPortByLogicAntenna(logic_antenna);

		// Select logic antenna
		AppEntry_R2000WriteRegister(fd, HST_ANT_DESC_SEL, logic_antenna, 0x00, 0x00, 0x00);
		
		// Enable antenna
		AppEntry_R2000WriteRegister(fd, HST_ANT_DESC_CFG, 0x01, 0x00, 0x00, 0x00);

		// Link logic antenna to physical antenna port
		AppEntry_R2000WriteRegister(fd, HST_ANT_DESC_PORTDEF, ANTENNA_PORT, 0x00, 0x00, 0x00);

		// Configure antenna power
		AppEntry_R2000WriteRegister(fd, HST_ANT_DESC_RFPOWER, powerBytes[0], powerBytes[1], 0x00, 0x00);

		// Configure time between logic antennas
		AppEntry_R2000WriteRegister(fd, HST_ANT_DESC_DWELL, dwellBytes[0], dwellBytes[1], 0x00, 0x00);

		printf("Configured logic antenna %d on port %d\n", logic_antenna, antenna_port);

	}

}

void startInventory(int fd) {

	printf("Starting inventory\n");

	// Enable inventory response parser thread
	threadControl = 1;

	// Infinity antenna cycles
	AppEntry_R2000WriteRegister(fd, HST_ANT_CYCLES, 0xFF, 0xFF, 0x00, 0x00);

	//Select profile 3 
	AppEntry_R2000WriteRegister(fd, HST_RFTC_CURRENT_PROFILE, 0x03, 0x00, 0x00, 0x00);
	AppEntry_R2000CommandExcute(fd,0x19);
	
	// Start inventory
	AppEntry_R2000CommandExcute(fd, CMD_18K6CINV);
}


//Stop inventory and close serial port
void stopInterruption() {
	printf("\nStopping inventory\n");
	threadControl = 0;
    ControlCommand(fd,CCMD_RESET);
	sleep(5);
	close(fd);
	exit(0);
}

int main(int argc, char *argv[])
{
	int filter = 0;
	float threeshold_1 = 0.0;
	float threeshold_2 = 0.0;
	u_int8_t filter_type;
	if (argc < 4){
		printf("./filter_by_rssi <int>filter <float>threeshold_1 <float>threeshold_2 \n");
		printf("filter 1 -> rssi less than threeshold_1  \n");
		printf("filter 2 -> rssi greater than threeshold_1  \n");
		printf("filter 3 -> rssi equal threeshold_1  \n");
		printf("filter 4 -> rssi less than threeshold_2 and greater than threeshold_1  \n");
		printf("filter 5 -> rssi less than threeshold_1 and greater than threeshold_2  \n");
		exit(-1);
	}
	filter = atoi(argv[1]);
	threeshold_1 = strtof(argv[2],NULL);
	threeshold_2 = strtof(argv[3],NULL);
	switch (filter){
		case 1:
			filter_type = LT_TH_1;
			break;
		case 2:
			filter_type = GT_TH_1;
			break;
		case 3:
			filter_type = EQ_TH_1;
			break;
		case 4:
			filter_type = GT_TH_1_LT_2;
			break;
		case 5:
			filter_type = LT_TH_1_GT_2;
			break;
		default:
			printf("Unknown option \n");
			exit(-1);
	}	
	
	// Callback where are receiving modem response; 
	fd = initRFID(*onPacketReceived, &threadControl); 
	
	// Catch Ctrl-C event 
	signal(SIGINT, stopInterruption);

	configureAntennas(fd);

	filterByRSSI(fd,filter_type,threeshold_1,threeshold_2);
	
	// Launch inventory
	startInventory(fd);
	
	// Wait until Ctrl-C
    while(1){
        sleep(1);
    }
	
}
