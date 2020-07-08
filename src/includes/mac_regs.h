
#ifndef MAC_REG_H
#define MAC_REG_H
/***** GENERAL REGISTERS *****/
#define MAC_VER 0x0000  //Version del firmware [RO]
#define MAC_INFO 0x0100 //Informacion del firmware [RO]
#define MAC_RFTRANSINFO 0x0200 //Informacion del chip transceptor [RO]
#define MAC_DBG1 0x0300 //Mantiene valores de depuración para testing 1
#define MAC_DBG2 0x0400 //Mantiene valores de depuración para testing 12
#define MAC_ERROR 0x0500 //Codigo de error en firmware contemplado en macerror.h [RO]
#define MAC_LAST_ERROR 0x0600 //Copia en cache del ultimo MAC_ERROR que solo se limpia durante reset [RO]
#define MAC_STATE 0x0700 //Estado actual de la maquina de estados, util para saber si entro en estado fallo [RO]
#define MAC_XCVR_HEALTH_CHECK_FAIL_COUNT 0x0800 //Numero de vez que el health check del transceptor fallo [RO]
#define MAC_LAST_COMMAND_DURATION 0x0900 //Milisegundos desde la ejecucion del ultimo comando MAC
#define MAC_KEY 0x0A00 //Random Key Generator [RO]
#define MAC_ERROR_DIAGNOSTIC_SEL 0x0B00 //Selector del Codigo de Diagnostico de Error
#define MAC_ERROR_DIAGNOSTIC 0x0C00 //Codigos de diagnostico de un error MAC [RO]
#define MAC_FW_DEFAULT_VALUE_SOURCE 0x0D00 //Especifica si algunos valores se obtienen a partir de OEM o del firmware por defecto[RO]
#define MAC_NV_UPDATE_CONTROL 0x0E00 //Modo de actualizacion
#define MAC_BL_VER 0x0F00 //Version del bootloader [RO}
#define MAC_ACTIVE_FW 0x1000 //Indica si esta activo el firmware MAC o el bootloader [RO]
#define MAC_FW_CRC 0x1100 //CRC del MAC firmware [RO]
#define MAC_MICROPROCESSOR_ID 0x1200 //Id del microprocesador [RO]
/***** TEST BLOCK *****/
#define HST_ENGTEST_ARG0 0x0001 //El firmware mira este registro cuando se ejecuta un engineering test command
#define HST_ENGTEST_ARG1 0x0101 //El firmware mira este registro cuando se ejecuta un engineering test command
#define HST_DBG1 0x0201 //Activa diferentes mensages de depuracion por el puerto serie de depuracion
#define HST_TX_RANDOM_DATA_DURATION 0x0401 //Tiempo de transmision de datos aleatorios
#define HST_TX_RANDOM_DATA_CONTROL 0x0501 //Opciones en la transmision de datos aleatorios ej.:cont||rafaga
#define HST_TX_RANDOM_DATA_ON_TIME 0x0601 //Duracion de las rafagas en us durante periodo activo 
#define HST_TX_RANDOM_DATA_OFF_TIME 0x0701 //Duracion de las rafagas en us durante periodo inactivo
#define HST_SET_FREQUENCY_CFG 0x0801 //Configuracion del selector de frecuencia (ver pdf)
#define HST_SET_FREQUENCY_CHANNEL 0x0901 //Selecciona un canal y una region especifica
#define HST_SET_FREQUENCY_KHZ (0x0A01 //Selecciona la frecuencia exacta en kHz
#define HST_SET_FREQUENCY_PLLDIVMULT 0x0B01 //El resultado de PLLDIVMULT del ultimo comando SET_FREQUENCY [RO]
#define HST_SET_FREQUENCY_PLLDACCTL 0x0C01 //El resultado de PLLDACCTL del ultimo comando SET_FREQUENCY [RO]
#define HST_TEST_FREQUENCY_PLLDIVMULT 0x0D01 //Cambia directamente el valor de PLLDIVMULT
#define HST_TEST_FREQUENCY_PLLDACCTL 0x0E01 //Cambia directamente el valor de PLLDACCTL
#define HST_TEST_INVENTORY_CFG 0x1001 //Opciones al lanzar inventario en modos de test especiales
#define HST_ENGTEST_RESULT_SEL 0x1101 //Selector del resultado de test al que acceder
#define HST_ENGTEST_RESULT 0x1201 //Resultado de test {RO]
#define HST_TEST_ANTENNA 0x1301 //Especifica la antena a probar [1:0]
#define HST_TEST_RFPOWER 0x1401 //Especifica nivel de potencia transmitido con pasos de 0.1 dBm (default: 12C = 30 dBm) 
#define HST_INJECT_RANDOM_TX_COUNT 0x1501 //Numero de bits aleatorios en la FIFO de transmision
#define HST_TEST_MANUAL_OVERRIDE 0x1601 //Especifica el uso de hw externo
#define HST_FORMAT_OEM_CONFIGURATION 0x2001 //Cambia configuracion del OEM ej:USB/UART, FCC/ETSI/Japan...
#define HST_FORMAT_OEM_KEY_CHECK 0x2101 //Comprueba clave para formatear OEM
#define HST_CALIBRATION_CONTROL 0x2301 //Opciones de calibracion
#define HST_CAL_PA_BIAS_CONFIG 0x2401 //Configuracion del criterio de calibracion del amplificador de potencia
#define HST_CAL_PA_BIAS_TARGET_CURRENT 0x2601 //Corriente objetivo en uA
#define HST_CAL_PA_BIAS_CURRENT_PER_LSB 0x2701 //Corriente de calibracion por LSB en uA
#define HST_CAL_GROSSGAIN_CONFIG 0x2801 //Calibracion ganancia bruta, max/min
/***** PLATFORM CONTROL BLOCK *****/
#define HST_PWRMGMT 0x0002 //Manejo del modo de potencia, normal o stand-by
#define HST_CMNDIAGS 0x0102 //Habilita diferentes diagnosticos
#define HST_TRACE 0x0202 //Habilita opciones de traza
#define HST_IMPINJ_EXTENSIONS 0x0302 //Soporte para extensiones especificas de Impinj
#define HST_PWRMGMT_STATUS 0x0402 //Obtiene modo actual de potencia [RO]
#define HST_INVENTORY_PACKET_CONTROL 0x0502 //Controla el reporte de informacion de los paquetes de inventario
/***** PROTOCOL SCHEDULER BLOCK *****/
#define HST_REGULATORY_REGION 0x0003 //Region configurada 0-FCC,1-ETSI,2-Japan [RO]
#define HST_PROTSCH_LBTCFG 0x0103 //Configuracion especifica LBT
#define HST_PROTSCH_FTIME 0x0303 //Tiempo en ms para la escucha durante LBT
#define HST_PROTSCH_TXTIME_ON 0x0603 //Tiempo en ms durante el que la portadora esta activa y se ejecutan las operaciones de protocol antes de la transicion de frecuencia
#define HST_PROTSCH_ADJCW 0x0A03 //Tiempo maximo en ms transcurrido durante el ajuste de la portadora
#define HST_PROTSCH_TXTIME_ON_OVHD 0x0C03 //Tiempo en ms para compensar el tiempo de arranque de la portadora
#define HST_PROTSCH_TXTIME_OFF_OVHD 0x0C03 //Tiempo en ms para compensar el tiempo de parada de la portadora
#define HST_PROTSCH_LBTRSSI 0x0E03 //Valor umbral que determina si existe una interferencia durante LBT
/***** MAC BYPASS BLOCK *****/
#define HST_MBP_ADDR 0x0004 //Derivacion de las direcciones de los registros de 16bits para los comandos MBPRDREG y MBPWRREG 
#define HST_MBP_DATA 0x0104 //Derivacion de los datos del comando MBPWRREG
#define HST_LPROF_SEL 0x08, 0x04 //Selector de 8bits para del perfil de enlace
#define HST_LPROF_ADDR 0x0904 //Direccion del registro que sera accededo con los comandos CMD_LPROF_RDXCVRREG or CMD_LPROF_WRXCVRREG
#define HST_LPROF_DATA 0x0A04 //Datos del comando CMD_LPROF_WRXCVRREG
/***** OEM CONFIG BLOCK *****/
#define HST_OEM_ADDR 0x0005 //Direccion de OEM data
#define HST_OEM_DATA 0x0105 //Valor que sera escrito con el comando WROEM
#define HST_OEM_STRING_TYPE 0x0205 //Selector de tipo de string para lectura/escritura en el area OEM.
#define HST_OEM_STRING_LENGTH 0x0305 //Longitud de un string especifico. Durante lectura muestra la longitud. Durante escritura se require como input.
#define HST_OEM_STRING_CHAR_SEL 0x0405 //Selector de char en el OEM String
#define HST_OEM_STRING_CHAR 0x0505 //Caracter Unicode 
/***** GPIO BLOCK *****/
#define HST_GPIO_INMSK 0x0006 //Indica que GPIO se leeran en los posteriores RDGPIO
#define HST_GPIO_OUTMSK 0x0106 //Indica los GPIO que se modificaran por HST_GPIO_OUTVAL tras un comando WRGPIO
#define HST_GPIO_OUTVAL 0x0206 //Este registro será "ANDed" con la mascara anterior y escrito en los pines tras un WRGPIO
#define HST_GPIO_CFG 0x0306 //Configura Input/Ouput en los GPIO. 0-Input, 1-Output [0:3]
/***** ANTENNA BLOCK *****/
#define HST_ANT_CYCLES 0x0007 //Numero de ciclos de antena 0xFFFF ciclo indefinido
#define HST_ANT_DESC_SEL 0x0107 //Selección de la antena que queremos configurar   
#define HST_ANT_DESC_CFG 0x0207 //Indicamos que antena queremos activar
#define MAC_ANT_DESC_STAT 0x0307 //Devuelve información de la antena previamente seleccionada
#define HST_ANT_DESC_PORTDEF 0x0407 //Definición del puerto de la antena
#define HST_ANT_DESC_DWELL 0x0507 //Usado en inventario, indica el tiempo en ms de comunicacion con la antena
#define HST_ANT_DESC_RFPOWER 0x0607 //definición de potencia, máximo 33.
#define HST_ANT_DESC_INV_CNT 0x0707 //Indica el numero de "turnos de inventario" ejecutados en la antena seleccionada
/***** TAG SELECT BLOCK *****/
#define HST_TAGMSK_DESC_SEL 0x0008 //Selector de descriptor y mascara
#define HST_TAGMSK_DESC_CFG 0x0108 //Usado en operacion de inventario con autoselect, indica consignas en la seleccion
#define HST_TAGMSK_BANK 0x0208 //Selecciona tipo de tag: 0x0 - Reserved 0x1 - EPC 0x2 - TID 0x3 - USER
#define HST_TAGMSK_PTR 0x03, 0x08 //Offset que se usa con la mascara
#define HST_TAGMSK_LEN 0x0408 //Numero de bits validos
#define HST_TAGMSK_0_3 0x0508 //Mascara
#define HST_TAGMSK_4_7 0x0608
#define HST_TAGMSK_8_11 0x0708
#define HST_TAGMSK_12_15 0x0808
#define HST_TAGMSK_16_19 0x0908
#define HST_TAGMSK_20_23 0x0A08
#define HST_TAGMSK_24_27 0x0B08
#define HST_TAGMSK_28_31 0x0C08
/***** INVENTORY BLOCK *****/
#define HST_QUERY_CFG 0x0009 //Registro de configuracion de Query
#define HST_INV_CFG 0x0109 //Registro de configuracion de Inventario
#define HST_INV_SEL 0x0209 //Selector de algoritmo
#define HST_INV_ALG_PARM_0 0x0309 //Parametros de configuracion de algoritmo
#define HST_INV_ALG_PARM_1 0x0409
#define HST_INV_ALG_PARM_2 0x0509
#define HST_INV_ALG_PARM_3 0x0609
#define HST_INV_RSSI_FILTERING_CONFIG 0x0709 //Configura filtrado por RSSI
#define HST_INV_RSSI_FILTERING_THRESHOLD 0x0809 //Umbral RSSI de filtrado
#define HST_INV_RSSI_FILTERING_COUNT 0x0909 //Numero de paquetes de inventario descartados tras ejecutar el comando de inventario
#define HST_INV_EPC_MATCH_CFG 0x1109 //Habilita el matching con EPCs para descartar los que no coincidan
#define HST_INV_EPCDAT_0_3 0x1209 //EPC deseado
#define HST_INV_EPCDAT_4_7 0x1309
#define HST_INV_EPCDAT_8_11 0x1409
#define HST_INV_EPCDAT_12_15 0x1509
#define HST_INV_EPCDAT_16_19 0x1609
#define HST_INV_EPCDAT_20_23 0x1709
#define HST_INV_EPCDAT_24_27 0x1809
#define HST_INV_EPCDAT_28_31 0x1909
#define HST_INV_EPCDAT_32_35 0x1A09
#define HST_INV_EPCDAT_36_39 0x1B09
#define HST_INV_EPCDAT_40_43 0x1C09
#define HST_INV_EPCDAT_44_47 0x1D09
#define HST_INV_EPCDAT_48_51 0x1E09
#define HST_INV_EPCDAT_52_55 0x1F09
#define HST_INV_EPCDAT_56_59 0x2009
#define HST_INV_EPCDAT_60_63 0x2109 //En este ultimo solo [0:15]
#define HST_INV_STATS_DURATION 0x3009 //Tiempo en ms del ultimo inventario [RO]
#define HST_INV_STATS_QUERY 0x3109 //Numero de consultas del ultimo inventario [RO]
#define HST_INV_STATS_RN16RCV 0x3209 //Numero de RN16s recibidios en el ultimo inventario [RO]
#define HST_INV_STATS_RN16TO 0x3309 //Numero de RN16 timeouts en el ultimo inventario [RO]
#define HST_INV_STATS_EPCTO 0x3409 //Numero de EPC timeouts en el ultimo inventario [RO]
#define HST_INV_STATS_TAGREADS 0x3509 //Numero de tag leidos en el ultimo inventario [RO]
#define HST_INV_STATS_EPCCRC 0x3609 //Numero de CRCs de EPCs en el ultimo inventario [RO]
#define HST_LBT_STATS_INTF_DURATION 0x3709 //Tiempo (en ms) de bloqueo por interferencia durante un LBT [RO]
#define HST_LBT_STATS_INTF_COUNT 0x3809 //Numero de bloqueos por interferencia durante un LBT [RO]
/***** TAG ACCESS BLOCK *****/
#define HST_TAGACC_DESC_CFG 0x010A //Numero de reintentos de comando de acceso si falla [1:3]
#define HST_TAGACC_BANK 0x020A //Especifica la zona de memoria durante las operaciones de acceso. 0-Reserved,1-EPC,2-TID,3-USER
#define HST_TAGACC_PTR 0x030A //Offset en tag memory for tag accesses
#define HST_TAGACC_CNT 0x040A //Numero de palabras de 16bits que seran accedidas
#define HST_TAGACC_LOCKCFG 0x050A //Bloqueo de accion y mascara
#define HST_TAGACC_ACCPWD 0x060A //Password para comandos de acceso. Dos palabras de 16 bits. [WO]
#define HST_TAGACC_KILLPWD 0x070A //Contraseña deseada antes de ejecutar 18K6CKILL [WO]
#define HST_TAGWRDAT_SEL 0x080A //Selecciona a que parte del buffer de escritura del tag se accede
#define HST_TAGWRDAT_0 0x090A //Datos de escritura del tag
#define HST_TAGWRDAT_1 0x0A0A
#define HST_TAGWRDAT_2 0x0B0A
#define HST_TAGWRDAT_3 0x0C0A
#define HST_TAGWRDAT_4 0x0D0A
#define HST_TAGWRDAT_5 0x0E0A
#define HST_TAGWRDAT_6 0x0F0A
#define HST_TAGWRDAT_7 0x100A
#define HST_TAGWRDAT_8 0x110A
#define HST_TAGWRDAT_9 0x120A
#define HST_TAGWRDAT_10 0x130A
#define HST_TAGWRDAT_11 0x140A
#define HST_TAGWRDAT_12 0x150A
#define HST_TAGWRDAT_13 0x160A
#define HST_TAGWRDAT_14 0x170A
#define HST_TAGWRDAT_15 0x180A
#define HST_TAGQTDAT 0x190A //Configuracion de QT
/***** RFTC BLOCK *****/
#define MAC_RFTC_PAPWRLEV 0x000B //Potencia de salida del PA [0.1dB/div] [RO]
#define HST_RFTC_PAPWRCTL_PGAIN 0x010B //Configuracion del proporcional en el algoritmo PI del PA
#define HST_RFTC_PAPWRCTL_IGAIN 0x020B //Configuracion del integral en el algoritmo PI del PA
#define MAC_RFTC_REVPWRLEV 0x040B //Medida de la potencia reflejada [RO]
#define HST_RFTC_REVPWRTHRSH 0x050B //Umbral para la diferencia entre la potencia directa y reflejada
#define MAC_RFTC_AMBIENTTEMP 0x060B //Medida de la temperatura ambiente [RO]
#define HST_RFTC_AMBIENTTEMPTHRSH 0x070B //Umbral para la temperatura ambiente en ºC
#define MAC_RFTC_XCVRTEMP 0x080B // (este creo que no lo tenemos) Medida de la temperatura del circuito integrado cerca transceptor RFID [RO]
#define HST_RFTC_XCVRTEMPTHRESH 0x090B // (este creo que no lo tenemos) Umbral para la temperatura del integrado en 1C
#define MAC_RFTC_PATEMP 0x0A0B //Medida de temperatura del PA [RO]
#define HST_RFTC_PATEMPTHRSH 0x0B0B //Umbral de temperatura del PA
#define HST_RFTC_PAPWRCTL_AIWDELAY 0x0D0B //Numero de iteraciones del sistema de control antes de integral la componente de error
#define MAC_RFTC_PAPWRCTL_STAT0 0x0E0B //Estadisticos de funcionamiento 
#define MAC_RFTC_PAPWRCTL_STAT1 0x0F0B
#define MAC_RFTC_PAPWRCTL_STAT2 0x100B
#define MAC_RFTC_PAPWRCTL_STAT3 0x110B
#define HST_RFTC_ANTSENSRESTHRSH 0x120B //Umbral de la resistencia de antena en ohm por debajo del cual se considera circuito abierto
#define HST_RFTC_IFLNAAGCRANGE 0x130B //Rango de ganancias en la consigna del AGC
#define MAC_RFTC_LAST_ANARXGAINNORM 0x140B //Configuracion de ganancia de cada una de las etapas: LNA IF and RF, AGC
#define HST_RFTC_OPENLOOPPWRCTRL 0x150B //Comportamiento de las etapas cuando la portadora esta habilitada
#define HST_RFTC_SJC_CFG 0x160B //Configuracion del cancelador de interferencia propia
#define HST_RFTC_DC_OFFSET_COEFF 0x1A0B //Control de offset para eliminar rizado de la senal RF
#define HST_RFTC_CAL_PA_BIAS_DAC 0x1B0B //Voltage de polarizacion del PA que permite optimizar consumo
#define HST_RFTC_GROSSGAIN_CONFIG 0x1C0B //Rango de ganancia bruta [RO]
#define HST_RFTC_CAL_GROSSGAIN_SEL 0x1D0B //Selecciona valores de ganancia bruta
#define HST_RFTC_CAL_GROSSGAIN_VALUE 0x1E0B //Calibracion de la ganancia bruta para un indice de ganancia especifico [RO]
#define HST_RFTC_CAL_GGNEG7_X 0x200B //Obsoleto, no se utiliza [RO]
#define HST_RFTC_CAL_GGNEG5_X 0x210B //Obsoleto, no se utiliza [RO]
#define HST_RFTC_CAL_GGNEG3_X 0x220B //Obsoleto, no se utiliza [RO]
#define HST_RFTC_CAL_GGNEG1_X 0x230B //Obsoleto, no se utiliza [RO]
#define HST_RFTC_CAL_GGPLUS1_X 0x240B //Obsoleto, no se utiliza [RO]
#define HST_RFTC_CAL_GGPLUS3_X 0x250B //Obsoleto, no se utiliza [RO]
#define HST_RFTC_CAL_GGPLUS5_X 0x260B //Obsoleto, no se utiliza [RO]
#define HST_RFTC_CAL_GGPLUS7_X 0x270B //Obsoleto, no se utiliza [RO]
#define HST_RFTC_CAL_RFFWDPWR_A2 0x290B //Coeficiente de segundo orden de la curva de deteccion de la potencia directa
#define HST_RFTC_CAL_RFFWDPWR_A1 0x2A0B //Coeficiente de primer orden de la curva de deteccion de la potencia directa
#define HST_RFTC_CAL_RFFWDPWR_A0 0x2B0B //Termino independiente de la curva de deteccion de la potencia directa
#define HST_RFTC_FWDPWRTHRSH 0x2C0B //Umbral de diferencia entre potencia transmitida deseada y medida 
#define HST_RFTC_CLKDBLR_CFG 0x300B //Configuracion del reloj doble
#define HST_RFTC_CLKDBLR_SEL 0x310B //
#define HST_RFTC_CLKDBLR_LUTENTRY 0x320B//NA
#define HST_RFTC_FRQHOPMODE 0x400B//NA
#define HST_RFTC_FRQHOPENTRYCNT 0x410B //NA
#define HST_RFTC_FRQHOPTABLEINDEX 0x420B
#define MAC_RFTC_HOPCNT 0x430B //NA
#define HST_RFTC_MINHOPDUR 0x440B //NA
#define HST_RFTC_MAXHOPDUR 0x450B //NA
#define HST_RFTC_FRQHOPRANDSEED 0x460B //NA
#define MAC_RFTC_FRQHOPSHFTREGVAL 0x470B //NA
#define MAC_RFTC_FRQHOPRANDNUMCNT 0x480B //NA
#define HST_RFTC_FRQCHINDEX 0x490B //NA
#define HST_RFTC_PLLLOCKTIMEOUT 0x4A0B //Timeout de espera por el PLL
#define HST_RFTC_BERREADDELAY 0x4E0B //BER timeout
#define MAC_RFTC_FWDRFPWRRAWADC 0x500B //Valor medio del ADC del detector de potencia RF transmitida
#define MAC_RFTC_REVRFPWRRAWADC 0x510B //Valor medio del ADC conectado al detector de resistencia de antena
#define MAC_RFTC_AMBTEMPRAWADC 0x530B ///Valor medio del ADC conectado al sensor de temperatura ambiente
#define MAC_RFTC_PATEMPRAWADC 0x540B //Valor medio del ADC conectado al sensor de temperatura del PA
#define MAC_RFTC_XCVRTEMPRAWADC 0x550B ///Valor medio del ADC conectado al sensor de temperatura del transceptor (nolotenemos)
#define MAC_RFTC_PACURRENT 0x560B //Medida del detector de corriente del PA [RO]
#define MAC_RFTC_PACURRENTADC 0x570B //Valor medio del ADC de la medida de corriente del PA
#define HST_RFTC_ACTIVE_PROFILE 0x5F0B //Perfil de corriente activo [RO]
#define HST_RFTC_CURRENT_PROFILE 0x600B //Perfil esperado
#define HST_RFTC_PROF_SEL 0x610B //Selector de perfil
#define MAC_RFTC_PROF_CFG 0x620B //Configuracion del perfil seleccionado
#define MAC_RFTC_PROF_ID_HIGH 0x630B //Identificador high de perfil 
#define MAC_RFTC_PROF_ID_LOW 0x640B //Identificador low de perfil
#define MAC_RFTC_PROF_IDVER 0x650B //Version del perfil
#define MAC_RFTC_PROF_PROTOCOL 0x660B //Reporte del protocol usado en el perfil seleccionado (0 indicates ISO 18000-6C)
#define MAC_RFTC_PROF_R2TMODTYPE 0x670B //Indica el tipo de modulacion 0=DSB-ASK, 1=SSB-ASK, 2=PR-ASK
#define MAC_RFTC_PROF_TARI 0x680B //Duracion de Tari en ns
#define MAC_RFTC_PROF_X 0x690B //Duracion de ISO 18000-6C parametro X (0 means X=0.5, 1 means X=1)
#define MAC_RFTC_PROF_PW 0x6A0B //Duracion de ISO 18000-6C parametro PW en ns
#define MAC_RFTC_PROF_RTCAL 0x6B0B //Duracion de ISO 18000-6C parametro PW en ns
#define MAC_RFTC_PROF_TRCAL 0x6C0B //Duracion de ISO 18000-6C parametro RTCal en ns
#define MAC_RFTC_PROF_DIVIDERATIO 0x6D0B //Parametro DR usado en Query
#define MAC_RFTC_PROF_MILLERNUM 0x6E0B //Numero de miller
#define MAC_RFTC_PROF_T2RLINKFREQ 0x6F0B //Frecuencia de enlace en tag-to-interrogator
#define MAC_RFTC_PROF_VART2DELAY 0x700B //Retardo anadido a la cadena de procesado
#define MAC_RFTC_PROF_RXDELAY 0x710B //Retardo (ciclos de 24 MHz) al final de la transmision justo antes de que el receptor se active
#define MAC_RFTC_PROF_MINTOTT2DELAY 0x720B //Tiempo minimo en us antes de empezar a transmitir
#define MAC_RFTC_PROF_TXPROPDELAY 0x730B //Retardo en us de propagacion en la cadena TX
#define MAC_RFTC_PROF_RSSIAVECFG 0x740B //Numero de muestras en el calculo promedio del RSSI del perfil actual
#define MAC_RFTC_PROF_PREAMCMD 0x750B //Indica al transceptor que forma de onda debe usar para generar el preambulo C1G2,R2T
#define MAC_RFTC_PROF_FSYNCCMD 0x760B //Indica al transceptor que forma de onda debe usar para generar el sync C1G2,R2T
#define MAC_RFTC_PROF_T2WAITCMD 0x77,00xB //Indica al transceptor que forma de onda debe usar para generar delays programados en la FIFO de transmision
#define HST_RFTC_CAL_RFREVPWR_A2 0x800B //Coeficiente de segundo orden del detector de potencia reflejada en formato Q7.24
#define HST_RFTC_CAL_RFREVPWR_A1 0x810B //Coeficiente de primer orden del detector de potencia reflejada en formato Q.24
#define HST_RFTC_CAL_RFREVPWR_A0 0x820B //Termino independiente del detector de potencia reflejada en formato Q7.24
#define HST_RFTC_CAL_AMBIENT_TEMP_A2 0x830B//Lo mismo para el detector de temperatura ambiental
#define HST_RFTC_CAL_AMBIENT_TEMP_A1 0x840B
#define HST_RFTC_CAL_AMBIENT_TEMP_A0 0x850B
#define HST_RFTC_CAL_XCVR_TEMP_A2 0x860B //Este no lo tenemos
#define HST_RFTC_CAL_XCVR_TEMP_A1 0x870B
#define HST_RFTC_CAL_XCVR_TEMP_A0 0x880B
#define HST_RFTC_CAL_ANT_SENSE_A2 0x890B //Detector de antena
#define HST_RFTC_CAL_ANT_SENSE_A1 0x8A0B
#define HST_RFTC_CAL_ANT_SENSE_A0 0x8B0B
#define HST_RFTC_SJC_EXTERNALLOTHRSH 0x8C0B //Permite la comprobacion de oscilador local externo
#define HST_RFTC_PA_CURRENT_TRIM 0x8D0B //Recorte de corriente del PA
#define HST_RFTC_CAL_PA_TEMP_A2 0x8E0B //Temperatura del PA
#define HST_RFTC_CAL_PA_TEMP_A1 0x8F0B
#define HST_RFTC_CAL_PA_TEMP_A0 0x900B
#define HST_RFTC_CAL_PA_CURRENT_A2 0x910B //Corriente de PA
#define HST_RFTC_CAL_PA_CURRENT_A1 0x920B
#define HST_RFTC_CAL_PA_CURRENT_A0 0x930B
#define HST_RFTC_CAL_EPC_RSSI 0x940B //Calibracion del RSSI de EPC en decimas de dBm
/***** FREQUENCY BLOCK *****/
#define HST_RFTC_FRQCH_SEL 0x010C //Selector de canal de frecuencia de 0 a 50
#define HST_RFTC_FRQCH_CFG 0x020C //Configuracion del canal (Enable/Disable)
#define HST_RFTC_FRQCH_DESC_PLLDIVMULT 0x030C //Ratios del PLL
#define HST_RFTC_FRQCH_DESC_PLLDACCTL 0x040C //
#define MAC_RFTC_FRQCH_DESC_PLLLOCKSTAT0 0x050C //datos del PLL
#define MAC_RFTC_FRQCH_DESC_PLLLOCKSTAT1 0x060C //Duracion del lazo cerrado del PLL
#define HST_RFTC_FRQCH_CMDSTART 0x070C //Frecuencia de comienzo
#define HST_RFTC_PLL_LAST_LOCK_FREQ 0x080C //Ultima frecuencia conseguida en el PLL
/***** RESERVED CUSTOMER BLOCK *****/
#define RESERVED_CUSTOMER 0x000F //Para usuarios
/***** HOST COMMAND BLOCK *****/
#define HST_CMD 0x00F0 //Comando a ejecutar

typedef struct mac_reg
{
         u_int16_t address;
         u_int8_t value [4];
} macReg; 
#endif