#include "../includes/ctrl_io.h"
#include "../includes/util.h"
#include <stdio.h>
#include <unistd.h>

#define TAG "Main"

int main()
{
	init(); 
	while (1){
		digitalWrite(0, HIGH);
		sleep(1);
		digitalWrite(0, LOW);
		sleep(1);
	}	
}
