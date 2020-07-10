#include "../includes/comm.h"
#include "../includes/regs_ctrl.h"
#include "../includes/mac_regs.h"
#include "../includes/mac_cmd.h"
#include "../includes/pkt_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>

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

void getMACerror(int fd) {
	
	// Get register value
	u_int8_t * buf = malloc(sizeof(u_int8_t)*4);
	AppEntry_R2000ReadRegister(fd, MAC_ERROR, buf);

	printf("MAC Error: ");
	for (int i = 0; i < 4; i++ ) {
    	printf("%02X", buf[i]);
	}
	printf("\n");

}

int main() {

	printf("Read MAC error example:\n");

	// Callback where are receiving modem response; 
	fd = initRFID(*onPacketReceived, &threadControl); 

	// Get MAC error
	getMACerror(fd);
	
}
