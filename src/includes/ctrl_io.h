#ifndef CTRL_IO_H
#define CTRL_IO_H

enum DIGITAL_VALUES {
    LOW = 0,
    HIGH = 1,
};


void init();

void digitalWrite(int address, enum DIGITAL_VALUES digital_value);

enum DIGITAL_VALUES readDigital(int address);

#endif
