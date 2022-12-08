#include "common.h"

void TRACE_PRINT(TRACE_LEVEL_e _level, char* _output, ...)
{
	String levelStr = ""; 

	switch (_level)
	{
	case (TRACE_LEVEL_e)eTRACE_LEVEL_LOG:
		{
			levelStr = "[LOG]: ";
		}
		break;
	
	case (TRACE_LEVEL_e)eTRACE_LEVEL_ERROR:
		{
			levelStr = "[ERROR]: ";
		}
		break;

	default:
		break;
	}

	Serial.print(levelStr);
	Serial.printf(_output);
}

void TRACE_LOG(char* _output, ...)
{
	TRACE_PRINT(eTRACE_LEVEL_LOG, _output);
}

void TRACE_ERROR(char* _output, ...)
{
	TRACE_PRINT(eTRACE_LEVEL_ERROR, _output);
}

String getGPIOModeName(GPIO_MODE_e _mode)
{
	String modeName = "";
	switch (_mode)
	{
	case eGPIO_MODE_INPUT:
		{
			modeName = "eGPIO_MODE_INPUT";
		}
		break;
	
	case eGPIO_MODE_OUTPUT:
		{
			modeName = "eGPIO_MODE_OUTPUT";
		}
		break;

	default:
		break;
	}

	return modeName;
}