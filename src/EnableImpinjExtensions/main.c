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
			printf("Packet length: %d\n", framelength);
			// for (i=0;i<framelength;i++){
        	// 	printf("%02X",databuf[i]);
   			// }
			// printf("\n");
	}
}

void modifyBitInMacRegister(u_int16_t address, int bit_position, int new_value) {
	
	int i = 0;
	u_int8_t * buf = malloc(sizeof(u_int8_t)*8);
	int byte = bit_position / 8;

	// Send read request message (HOST_REG_REQ)
	AppEntry_R2000ReadRegister(fd, address);

	// Read response message from RFID chip (HOST_REG_REQ_READ)
	R2000_Read(fd, buf, 8);

	// Parse register value (4 bytes) from response message
	uint8_t register_value[4];
	for (i=4;i<8;i++){
        register_value[i-4] = buf[i];
   	}
	
	// Modify register value
	register_value[byte] ^= (-new_value ^ register_value[byte]) & (1 << bit_position);

	// Write new register value
	AppEntry_R2000WriteRegister(fd, address, register_value[0], 
		register_value[1], register_value[2], register_value[3]);

}

void enableTagSuppression(int fd) {
	printf("Enabling tag suppression\n");
	modifyBitInMacRegister(HST_IMPINJ_EXTENSIONS, 4, 1);
}

void enableFastID() {
	printf("Enabling Fast ID\n");
	modifyBitInMacRegister(HST_IMPINJ_EXTENSIONS, 5, 1);
}

void enableImpinjExtensions(int fd) {

	printf("Enabling impinj extensions\n"); 
	enableTagSuppression(fd);
	enableFastID(fd);
	printf("Done.\n");

}

void startInventory(int fd) {

	printf("Starting inventory\n");

	// Infinity antenna cycles
	AppEntry_R2000WriteRegister(fd, HST_ANT_CYCLES, 0xFF, 0xFF, 0x00, 0x00);

	// Start inventory
	AppEntry_R2000CommandExcute(fd, CMD_18K6CINV);
}

// Stop inventory and close serial port
void stopInterruption() {
	printf("Stopping inventory");
    ControlCommand(fd, CCMD_RESET);
	sleep(1);
	close(fd);
	exit(0);
}

int main() {

	printf("Enable impinj extensions example:\n");

	// Callback where are receiving modem response; 
	fd = initRFID(*onPacketReceived, &threadControl); 

	// Catch Ctrl-C event 
	signal(SIGINT, stopInterruption);

	// Enable Impinj extensions
	enableImpinjExtensions(fd);

	// Launch inventory
	startInventory(fd);
	
	// Wait until Ctrl-C
    while(1){
        msleep(1);
    }
	
}
