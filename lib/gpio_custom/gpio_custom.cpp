#include "gpio_custom.h"

GPIO_Custom::GPIO_Custom(uint8_t _pin, GPIO_MODE_e _pinMode)
{
	nPin = (uint8_t)_pin;
	ePinMode = (GPIO_MODE_e)_pinMode;
	eState = (GPIO_STATE_e) eGPIO_STATE_LOW;
	pinMode(nPin, (uint8_t)ePinMode);
	
	// TRACE_LOG("=== Construct: Pin %d, mode %d", nPin, ePinMode);
	if(eGPIO_MODE_OUTPUT == ePinMode)
	{
		digitalWrite(nPin, (uint8_t)eState);
		// TRACE_LOG(", state default %s ===\n", getGPIOModeName((GPIO_MODE_e)eState));
	}
	else
	{
		// do nothing
		// TRACE_LOG(" ===\n");
	}
}

GPIO_Custom::GPIO_Custom(uint8_t _pin, GPIO_MODE_e _pinMode, GPIO_STATE_e _state)
{
	nPin = (uint8_t)_pin;
	ePinMode = (GPIO_MODE_e)_pinMode;
	eState = (GPIO_STATE_e) _state;
	pinMode(nPin, (uint8_t)ePinMode);
	
	// TODO: add debug code here
	// TRACE_LOG("=== Construct: Pin %d, mode %d", nPin, ePinMode);
	if(eGPIO_MODE_OUTPUT == ePinMode)
	{
		digitalWrite(nPin, (uint8_t)eState);
		// TODO: add debug code here
		// TRACE_LOG(", state %s ===\n", getGPIOModeName((GPIO_MODE_e)eState));
	}
	else
	{
		// do nothing
		// TRACE_LOG(" ===\n");
	}
}

uint8_t GPIO_Custom::getPin(void)
{
	return (uint8_t)nPin;
}

GPIO_MODE_e GPIO_Custom::getPinMode(void)
{
	return (GPIO_MODE_e)ePinMode;
}

ERROR_TYPE_e GPIO_Custom::setPinMode(GPIO_MODE_e _newPinMode)
{
	ERROR_TYPE_e retVal = eERROR_TYPE_OK;

	if(_newPinMode != ePinMode)
	{
		ePinMode = (GPIO_MODE_e)_newPinMode;
		pinMode(nPin, (uint8_t)ePinMode);
		
		if(eGPIO_MODE_OUTPUT == ePinMode)
		{
			eState = (GPIO_STATE_e) eGPIO_STATE_LOW;
			digitalWrite(nPin, (uint8_t)eState);
		}
		else
		{
			// do nothing
		}
		retVal = eERROR_TYPE_OK;
	}
	else
	{
		// TRACE_ERROR("Same mode, no change");
		retVal = eERROR_TYPE_HAPPEN;
	}

	return (ERROR_TYPE_e)retVal;
}

GPIO_STATE_e GPIO_Custom::getState(void)
{
	GPIO_STATE_e eRetState = eGPIO_STATE_LOW;

	switch(ePinMode)
	{
		case (GPIO_MODE_e) OUTPUT:
			{
				eRetState = eState;
			}
			break;
		
		case (GPIO_MODE_e) INPUT:
			{
				eRetState = (GPIO_STATE_e)digitalRead(nPin);
			}
			break;
		
		default:
			{
				eRetState = eState;
			}
			break;
	}

	return (GPIO_STATE_e)eRetState;
}

ERROR_TYPE_e GPIO_Custom::setState(GPIO_STATE_e _state)
{
	if(eGPIO_MODE_OUTPUT != ePinMode)
	{
		Serial.println("Unable to set to NOT Output pin");
		return (ERROR_TYPE_e)eERROR_TYPE_HAPPEN;
	}
	else
	{
		eState = (GPIO_STATE_e)_state;
		digitalWrite(nPin, (uint8_t)eState);
		return (ERROR_TYPE_e)eERROR_TYPE_OK;
	}
}

void GPIO_Custom::setTimer(GPIO_STATE_e _startState, GPIO_STATE_e _endState, uint32_t _timeInterval)
{

}

void GPIO_Custom::stopTimer(void)
{

}
