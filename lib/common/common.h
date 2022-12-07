#ifndef __COMMON_H__
#define __COMMON_H__

#define _____LIB_INCLUDE_____
#include <Arduino.h>

#define _____ENUM_DEFINE_____



typedef enum
{
	eGPIO_STATE_LOW = 0,
	eGPIO_STATE_HIGH
}GPIO_STATE_e;

typedef enum
{
	eINPUT = INPUT,
	eINPUT_PULLUP = INPUT_PULLUP,
	eINPUT_PULLDOWN_16 = INPUT_PULLDOWN_16,
	eOUTPUT = OUTPUT,
	eOUTPUT_OPEN_DRAIN = OUTPUT_OPEN_DRAIN,
	eWAKEUP_PULLUP = WAKEUP_PULLUP,
	eWAKEUP_PULLDOWN = WAKEUP_PULLDOWN,
	eSPECIAL = SPECIAL,
	eFUNCTION_0 = FUNCTION_0,
	eFUNCTION_1 = FUNCTION_1,
	eFUNCTION_2 = FUNCTION_2,
	eFUNCTION_3 = FUNCTION_3,
	eFUNCTION_4 = FUNCTION_4
}GPIO_MODE_e;

typedef enum
{
	ERR_OK = 0,
	ERR_HAPPEN
}ERR_TYPE_e;

#endif