#include "../includes/comm.h"
#include "../includes/regs_ctrl.h"
#include "../includes/mac_regs.h"
#include "../includes/mac_cmd.h"
#include "../includes/pkt_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <errno.h>
#include <inttypes.h> /* strtoimax */

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

// Stop inventory and close serial port
void stopInterruption() {
	printf("\nStopping inventory\n");
	threadControl = 0;
    ControlCommand(fd, CCMD_RESET);
	sleep(1);
	close(fd);
	exit(0);
}

//Convert string to u_int16_t
int str_to_uint16(const char *str, u_int16_t *res)
{
  char *end;
  errno = 0;
  intmax_t val = strtoimax(str, &end, 16);
  if (errno == ERANGE || val < 0 || val > UINT16_MAX || end == str || *end != '\0')
    return 0;
  *res = (uint16_t) val;
  return 1;
}

int main(int argc, char *argv[]) {

	u_int16_t addressH;

	if (argc < 2){
		printf("Address argument is necesary \n");
		exit(-1);
	}
	
	
	if (str_to_uint16(argv[1],&addressH) == 0){
		printf("Error during hex conversion \n");
		exit(-1);
	}
	printf("Reading register from mac address 0x%02X \n ",addressH);


	// Callback where are receiving modem response; 
	fd = initRFID(*onPacketReceived, &threadControl); 

	// Catch Ctrl-C event 
	signal(SIGINT, stopInterruption);

	// Get register value
	u_int8_t * buf = malloc(sizeof(u_int8_t)*4);
	AppEntry_R2000ReadRegister(fd, addressH, buf);
	
	int  i = 0;
	printf("Value: ");
	for (i=3;i>=0;i--){
        printf("%02X",buf[i]);
   	}
	printf("\n");
	
}
