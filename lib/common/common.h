#ifndef __COMMON_H__
#define __COMMON_H__

#define _____LIB_INCLUDE_____
#include <Arduino.h>

#define _____ENUM_DEFINE_____

typedef enum
{
	eTRACE_LEVEL_LOG = 0,
	eTRACE_LEVEL_ERROR
}TRACE_LEVEL_e;

typedef enum
{
	eGPIO_STATE_LOW = 0,
	eGPIO_STATE_HIGH
}GPIO_STATE_e;

typedef enum
{
	eGPIO_MODE_INPUT = INPUT,
	eGPIO_MODE_INPUT_PULLUP = INPUT_PULLUP,
	eGPIO_MODE_INPUT_PULLDOWN_16 = INPUT_PULLDOWN_16,
	eGPIO_MODE_OUTPUT = OUTPUT,
	eGPIO_MODE_OUTPUT_OPEN_DRAIN = OUTPUT_OPEN_DRAIN,
	eGPIO_MODE_WAKEUP_PULLUP = WAKEUP_PULLUP,
	eGPIO_MODE_WAKEUP_PULLDOWN = WAKEUP_PULLDOWN,
	eGPIO_MODE_SPECIAL = SPECIAL,
	eGPIO_MODE_FUNCTION_0 = FUNCTION_0,
	eGPIO_MODE_FUNCTION_1 = FUNCTION_1,
	eGPIO_MODE_FUNCTION_2 = FUNCTION_2,
	eGPIO_MODE_FUNCTION_3 = FUNCTION_3,
	eGPIO_MODE_FUNCTION_4 = FUNCTION_4
}GPIO_MODE_e;



typedef enum
{
	eERROR_TYPE_OK = 0,
	eERROR_TYPE_HAPPEN
}ERROR_TYPE_e;

#define _____FUNCTION_PROTOTYPE_____
void TRACE_PRINT(TRACE_LEVEL_e _level, char* _output, ...);
void TRACE_LOG(char* _output, ...);
void TRACE_ERROR(char* _output, ...);
String getGPIOModeName(GPIO_MODE_e _mode);

#endif