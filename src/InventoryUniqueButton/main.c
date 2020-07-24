
#include "../includes/comm.h"
#include "../includes/regs_ctrl.h"
#include "../includes/mac_regs.h"
#include "../includes/mac_cmd.h"
#include "../includes/pkt_types.h"
#include "../includes/ctrl_io.h"
#include "../includes/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "tag_list.h"
int fd;


// Uart thread initially stopped
int threadControl = 0;
enum State {idle, reading};
#define TAG "Main"
#define END_TIME 10 //seconds
#define ANTENNA_PORT 0
#define ANTENNA_POWER 250 	// 30 dB
#define DWELL_TIME 150		// ms
#define LOGIC_ANTENNAS 1

u_int8_t getEpc(u_int8_t *epc,u_int8_t * frame, u_int16_t framelength){	
	u_int8_t epcLength = framelength-14-2;
	memcpy(epc,frame+14,epcLength);
	return epcLength;	
}

void modifyBitInMacRegister(u_int16_t address, int bit_position, int new_value) {
	
	// Get register value
	u_int8_t * buf = malloc(sizeof(u_int8_t)*4);
	AppEntry_R2000ReadRegister(fd, address, buf);

	// Modify register value
	int byte = bit_position / 8;
	buf[byte] ^= (-new_value ^ buf[byte]) & (1 << bit_position);

	// Write the new register value
	AppEntry_R2000WriteRegister(fd, address, buf[0], 
		buf[1], buf[2], buf[3]);

}

void configureAntennas(int fd) {

	int logic_antenna, antenna_port;
	u_int8_t powerBytes[2];
  	u_int8_t dwellBytes[2];

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

void enableTagSuppression(int fd) {
	printf("Enabling tag suppression\n");
	modifyBitInMacRegister(HST_IMPINJ_EXTENSIONS, 4, 1);
}

//Callback to receive the RFID frames
void onPacketReceived(int fd,u_int8_t *databuf,u_int16_t framelength,u_int16_t pkt_type)
{
	u_int8_t epc[20];
    int i = 0,epclength = 0;
	switch(pkt_type){
		case CMD_BEGIN:
			printf("INVENTORY STARTED\n");
		break;
		case INV:
			printf("TAG_RECEIVED\n");
			epclength = getEpc(epc,databuf,framelength);
			addTagToList(epc,epclength);
			
			//digitalWrite(1, HIGH);
        	//digitalWrite(1, LOW);
		break;
		case CMD_ACTIVE:
			printf("COMMAND ACTIVE\n");
		break;
		case CMD_END:
			printf("INVENTORY END\n");
		break;
		default:
			printf("UNKNOWN PACKET TYPE %d\n", pkt_type);
		break;
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
	printTagList();
	sleep(5);
	close(fd);
	exit(0);
}

int main()
{
	int start_time = 0;
	// Callback where are receiving modem response; 
	fd = initRFID(*onPacketReceived, &threadControl); 
	init(); 
	// Catch Ctrl-C event 
	signal(SIGINT, stopInterruption);
	configureAntennas(fd);
	enableTagSuppression(fd);
	// Launch inventory
	enum State state = idle ;
	
	// Wait until Ctrl-C
    while(1){
		switch(state){
			case idle:
				if (readDigital(0)){
					while(readDigital(0));
					startInventory(fd);
					start_time = (int)time(NULL);
					state = reading;
				}
				break;
			case reading:
				{
					int inventory_time = (int)time(NULL) - start_time;
					//printf("inventory time %i \n",inventory_time);
					if (inventory_time > END_TIME){
						ControlCommand(fd,CCMD_PAUSE);
						printTagList();
						state = idle;
					}
				}
			 	break;

		}
        msleep(1);
    }
	
}
