

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

#define msleep(n)		usleep(1000*n)

/**
 * @brief Calcula checksum de un buffer
 * 
 * @param uBuff buffer para comprobar...
 * @param uBuffLen longitud del buffer
 * @return valor del checksum
 */
u_int8_t CheckSum(unsigned char *uBuff, int uBuffLen);


/**
 * @brief Start RFID communication
 * 
 * @param devName Path del tty
 * @param baudrate velocidad
 * @return int
 */
int initRFID(void *callback, int* threadControl);




/**
 * @brief Escribe en el puerto serie la trama indicada
 * 
 * @param fd descriptor del puerto serie
 * @param Uart_Send_Buf trama a enviar
 * @param length longitud de la trama a enviar
 * @return void
 */
void R2000_Send(int fd,u_int8_t *Uart_Send_Buf,unsigned int length);

void R2000_Read(int fd, u_int8_t * buf, int num_bytes);