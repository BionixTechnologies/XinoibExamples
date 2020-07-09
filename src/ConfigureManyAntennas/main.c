#include "../includes/comm.h"
#include "../includes/regs_ctrl.h"
#include "../includes/mac_regs.h"
#include "../includes/mac_cmd.h"
#include "../includes/pkt_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>

#define ANTENNA_PORTS 1
#define LOGIC_ANTENNAS 16
#define ANTENNA_POWER 300 	// 30 dB
#define DWELL_TIME 150		// ms

int fd;

// Uart thread initially stopped
int threadControl = 0;

//Callback to receive the RFID frames
void onPacketReceived(int fd,u_int8_t *databuf,u_int16_t framelength,u_int16_t pkt_type)
{
    int i = 0;
	switch(pkt_type){
		case CMD_BEGIN:
			printf("INVENTORY STARTED\n");
		break;
		case INV:
			printf("TAG_RECEIVED\n");
			for (i=0;i<framelength;i++){
        		printf("%02X",databuf[i]);
   			}
			printf("\n");
		break;
		case CMD_ACTIVE:
			printf("COMMAND ACTIVE\n");
		break;
		case CMD_END:
			printf("INVENTORY END\n");
		break;
	}
}

int getPhysicalPortByLogicAntenna(int logic_antenna) {
	int antennasPerPort = LOGIC_ANTENNAS / ANTENNA_PORTS;
	return logic_antenna/antennasPerPort;
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

		antenna_port = getPhysicalPortByLogicAntenna(logic_antenna);

		// Select logic antenna
		AppEntry_R2000WriteRegister(fd, HST_ANT_DESC_SEL, logic_antenna, 0x00, 0x00, 0x00);
		
		// Enable antenna
		AppEntry_R2000WriteRegister(fd, HST_ANT_DESC_CFG, 0x01, 0x00, 0x00, 0x00);

		// Link logic antenna to physical antenna port
		AppEntry_R2000WriteRegister(fd, HST_ANT_DESC_PORTDEF, antenna_port, 0x00, 0x00, 0x00);

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

	// Start inventory
	AppEntry_R2000CommandExcute(fd,CMD_18K6CINV);
}



// Stop inventory and close serial port
void stopInterruption() {
	printf("\nStopping inventory\n");
    ControlCommand(fd, CCMD_RESET);
	sleep(5);
	close(fd);
	exit(0);
}

int main()
{

	printf("Configure many antennas example:\n");

	// Callback where are receiving modem response; 
	fd = initRFID(*onPacketReceived, &threadControl);

	// Catch Ctrl-C event 
	signal(SIGINT, stopInterruption);
	
	// Configure logic antennas and ports
	configureAntennas(fd);

	// Launch inventory
	startInventory(fd);
	
	// Wait until Ctrl-C
    while(1){
        msleep(1);
    }
}
