#include "../includes/comm.h"
#include "../includes/regs_ctrl.h"
#include "../includes/mac_regs.h"
#include "../includes/mac_cmd.h"
#include "../includes/pkt_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

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

int main()
{

	// Callback where are receiving modem response; 
	fd = initRFID(*onPacketReceived, &threadControl); 
	
	// Catch Ctrl-C event 
	signal(SIGINT, stopInterruption);

	// Launch inventory
	startInventory(fd);
	
	// Wait until Ctrl-C
    while(1){
        msleep(1);
    }
	
}
