
#ifndef MAC_COM_H
#define MAC_COM_H
#define CMD_NONE 0x00 //NA CMD_NONE
#define CMD_NV_MEM_UPDATE 0x01 //NA NV Memory Update
#define CMD_WROEM 0x02 //NA Write OEM Configuration Area
#define CMD_RDOEM 0x03 //NA Read OEM Configuration Area
#define CMD_ENGTEST 0x04 //NA //Engineering Test - Base command for following sub-commands
#define CMD_ENGTEST_PACKETS 0x04 0x00 //Engineering Test - Send All Packet Types
#define CMD_ENGTEST_INV_PACKETS 0x04 0x01 //Engineering Test - Send Inventory Packets
#define CMD_ENGTEST_RESERVED_02 0x04 0x02 //Engineering Test - Reserved 0x02
#define CMD_ENGTEST_DEBUG_SHELL 0x04 0x03 //Engineering Test - Invoke Debug Shell
#define CMD_ENGTEST_POWER_CYCLE_INDY 0x04 0x04 //Engineering Test - Power Cycle Indy Reader Chip
#define CMD_ENGTEST_RSSI_TEST 0x04 0x05 //Engineering Test - RSSI Streaming Test
#define CMD_ENGTEST_PLL_LOCK 0x04 0x06 //Engineering Test - PLL Lock
#define CMD_ENGTEST_IFFILTER_TUNE 0x04 0x07 //Engineering Test - TX RX IF Filter Tuning
#define CMD_ENGTEST_RESERVED_08 0x04 0x08 //Engineering Test - Reserved 0x08
#define CMD_ENGTEST_SSP_CONTROL 0x04 0x09 //Engineering Test - SSP On/Off Control
#define CMD_ENGTEST_BER_PER_TEST 0x04 0x0A //Engineering Test - BER/PER Test
#define CMD_ENGTEST_READ_SENSORS 0x04 0x0B //Engineering Test - Read Sensors
#define CMD_ENGTEST_ANTENNA 0x04 0x0C //Engineering Test - Activate Antenna
#define CMD_ENGTEST_SJC_TEST 0x04 0x0D //Engineering Test - SJC Test
#define CMD_ENGTEST_TX_COMMAND 0x04 0x0E //Engineering Test - Tx Command
#define CMD_ENGTEST_DEBUG_PACKET 0x04 0x0F //Engineering Test - Test Debug Packet
#define CMD_ENGTEST_MEMORY_DUMP 0x04 0x10 //Engineering Test - Memory Dump
#define CMD_ENGTEST_SENSOR_INTERPOLATE 0x04 0x11 //Engineering Test - Calculate Sensor Interpolations
#define CMD_ENGTEST_LBT_TEST 0x04 0x12 //Engineering Test - LBT Test
#define CMD_ENGTEST_UART_TEST 0x04 0x13 //Engineering Test - UART Test String
#define CMD_ENGTEST_LED_TEST 0x04 0x14 //Engineering Test - LED Test
#define CMD_ENGTEST_GPIO_CONTROL 0x04 0x15 //Engineering Test - Generic GPIO Control
#define CMD_ENGTEST_TX_CONTROL 0x04 0x16 //Engineering Test - Generic Transmitter Control
#define CMD_ENGTEST_DAC_CONTROL 0x04 0x17 //Engineering Test - Generic DAC Control
#define CMD_ENGTEST_DRM_FILTER 0x04 0x18 //Engineering Test - DRM Filter
#define CMD_ENGTEST_RECEIVER_TEST 0x04 0x19 //Engineering Test - Receiver Test
#define CMD_ENGTEST_RSSI_MEASUREMENT 0x04 0x1A //Engineering Test - RSSI Measurement
#define CMD_ENGTEST_SSP_STRESS 0x04 0x1B //Engineering Test - SSP Stress Test
#define CMD_MBPRDREG 0x05 //NA MAC Bypass Register Read
#define CMD_MBPWRREG 0x06 //NA MAC Bypass Register Write
#define CMD_RESERVED_07 0x07 //NA CMD_RESERVED_07 - Command not supported
#define CMD_RESERVED_08 0x08 //NA CMD_RESERVED_08 - Command not supported
#define CMD_RESERVED_09 0x09 //NA CMD_RESERVED_09 - Command not supported
#define CMD_RESERVED_0A 0x0A //NA CMD_RESERVED_0A - Command not supported
#define CMD_RESERVED_0B 0x0B //NA CMD_RESERVED_0B - Command not supported
#define CMD_RDGPIO 0x0C //NA Read GPIO
#define CMD_WRGPIO 0x0D //NA Write GPIO
#define CMD_CFGGPIO 0x0E //NA Configure GPIO
#define CMD_18K6CINV 0x0F //NA ISO 18000-6C Inventory
#define CMD_18K6CREAD 0x10 //NA ISO 18000-6C Read
#define CMD_18K6CWRITE 0x11 //NA ISO 18000-6C Write
#define CMD_18K6CLOCK 0x12 //NA ISO 18000-6C Lock
#define CMD_18K6CKILL 0x13 //NA ISO 18000-6C Kill
#define CMD_SETPWRMGMTCFG 0x14 //NA Set Power Management Configuration

#define CCMD_RESET 0x02
#define CCMD_CANCEL 0x01
#define CCMD_ABORT 0x03
#define CCMD_PAUSE 0x04
#define CCMD_RESUME 0x05
#define CCMD_BOOTLOADER 0x07
#define GET_SERNUMBER {0xC0,0x06,0x00,0x00,0x00,0x00,0x00,0x00}

#endif
