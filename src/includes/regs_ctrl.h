#include <sys/types.h>

#define CTRL_CMD(CMD) {0x40,CMD,0x00,0x00,0x00,0x00,0x00,0x00}


/**
 * @brief Escribe un registro de configuracion del R2000
 * 
 * @param fd descriptor del puerto serie
 * @param Address direccion del registro
 * @param Data1 primer byte de la trama
 * @param Data2 "
 * @param Data3 "
 * @param Data4 "
 * @return void
 */
void AppEntry_R2000CommandExcute(int fd,u_int8_t R2000_Command);


/**
 * @brief Escribe comando para leer registro cuyo valor sera devuelto por funcion callback
 * 
 * @param fd descriptor del puerto serie
 * @param Address direccion del registro a leer
 * @return void
 */
void AppEntry_R2000WriteRegister(int fd,u_int16_t Address, u_int8_t Data1,u_int8_t Data2,u_int8_t Data3,u_int8_t Data4);


/**
 * @brief Realiza la ejecucion de un comando en el R2000
 * 
 * @param fd descriptor del puerto serie
 * @param R2000_Command comando a ejecutar
 * @return void
 */
void AppEntry_R2000ReadRegister(int fd,u_int16_t Address, u_int8_t * register_value);


/**
 * @brief Realiza la ejecucion de un comando de control
 * 
 * @param fd descriptor del puerto serie
 * @param control_cmd comando de control
 * @return void
 */
void ControlCommand(int fd,u_int8_t control_cmd);

void AppEntry_R2000WriteOemRegister(int16_t fd, u_int32_t address, u_int8_t data1, u_int8_t data2, u_int8_t data3, u_int8_t data4);

void AppEntry_R2000ReadOemRegister(int16_t fd, u_int32_t address, u_int8_t * register_value);
