#include "../includes/comm.h"
#include "../includes/regs_ctrl.h"
#include "../includes/mac_regs.h"
#include "../includes/oem_reg.h"
#include "../includes/mac_cmd.h"
#include "../includes/pkt_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>

int fd;

// Uart thread initially stopped
int threadControl = 0;

void enableAllAntennaPorts() {
	AppEntry_R2000WriteOemRegister(fd, OEMCFGADDR_ANT_AVAIL, 0x00, 0x00, 0x00, 0x00);
}

int main() {

	printf("Enable all antenna ports example:\n");

	// Callback where are receiving modem response; 
	fd = initRFID(NULL, &threadControl); 

	enableAllAntennaPorts();
	
}
