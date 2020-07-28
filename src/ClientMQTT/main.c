
#include "../includes/comm.h"
#include "../includes/regs_ctrl.h"
#include "../includes/mac_regs.h"
#include "../includes/mac_cmd.h"
#include "../includes/pkt_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <mosquitto.h>
int fd;
const char* addr;
const char* port;
const char* topic;

// Uart thread initially stopped
int threadControl = 0;

int publishMQTT(u_int8_t *databuf){

	int rc;
	struct mosquitto * mosq;

	mosquitto_lib_init();

	mosq = mosquitto_new("publisher-test", true, NULL);

	rc = mosquitto_connect(mosq, addr, atoi(port), 60);
	if(rc != 0){
		printf("Client could not connect to broker! Error Code: %d\n", rc);
		mosquitto_destroy(mosq);
		return -1;
	}
	printf("Sending TAG to the server MQTT\n");

	mosquitto_publish(mosq, NULL, topic, 6, databuf, 0, false);
	
	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	return 0;
}

//Callback to receive the RFID frames
void onPacketReceived(int fd,u_int8_t *databuf,u_int16_t framelength,u_int16_t pkt_type)
{
    int i = 0;
	char hex[10];
	char hexstring[4*framelength];
	hexstring[0]="";
	switch(pkt_type){
		case CMD_BEGIN:
			printf("INVENTORY STARTED\n");
		break;
		case INV:
			printf("TAG_RECEIVED\n");
			for (i=0;i<framelength;i++){
				sprintf(hex, "%02X", databuf[i]);
				strcat(hexstring, hex);
   			}
			printf("\n");
			publishMQTT(hexstring);
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
void enableTagSuppression(int fd) {
	printf("Enabling tag suppression\n");
	modifyBitInMacRegister(HST_IMPINJ_EXTENSIONS, 4, 1);
}

int main(int argc, const char *argv[]) 
{

    /* get topic (argv[1] if present) */
    if (argc > 1) {
		topic = argv[1];
    } else {
        topic = "xinoid";
    }

    /* get address (argv[2] if present) */
    if (argc > 2) {
		addr = argv[2];
    } else {
        addr = "localhost";
		
    }

    /* get the port  */
    if (argc > 3) {
        port = argv[3];
    } else {
        port = "1883";
    }


	// Callback where are receiving modem response; 
	fd = initRFID(*onPacketReceived, &threadControl);

	enableTagSuppression(fd);
	// Catch Ctrl-C event 
	signal(SIGINT, stopInterruption);

	// Launch inventory
	startInventory(fd);
	
	// Wait until Ctrl-C
    while(1){
        msleep(1);
    }
	
}