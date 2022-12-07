#include "gpio_custom.h"

GPIO_Custom::GPIO_Custom(uint8_t _pin, GPIO_MODE_e _pinMode)
{
	nPin = (uint8_t)_pin;
	ePinMode = (GPIO_MODE_e)_pinMode;
	eState = (GPIO_STATE_e) eGPIO_STATE_LOW;
	pinMode(nPin, (uint8_t)ePinMode);
	
	if(eOUTPUT == ePinMode)
	{
		digitalWrite(nPin, (uint8_t)eState);
	}
	else
	{
		// do nothing
	}
}

GPIO_Custom::GPIO_Custom(uint8_t _pin, GPIO_MODE_e _pinMode, GPIO_STATE_e _state)
{
	nPin = (uint8_t)_pin;
	ePinMode = (GPIO_MODE_e)_pinMode;
	eState = (GPIO_STATE_e) _state;
	pinMode(nPin, (uint8_t)ePinMode);
	
	// TODO: add debug code here

	if(eOUTPUT == ePinMode)
	{
		digitalWrite(nPin, (uint8_t)eState);
		// TODO: add debug code here
		
	}
	else
	{
		Serial.println("Unable to write to OUTPUT pin");
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

void GPIO_Custom::setPinMode(GPIO_MODE_e _newPinMode)
{
	if(_newPinMode != ePinMode)
	{
		ePinMode = (GPIO_MODE_e)_newPinMode;
		pinMode(nPin, (uint8_t)ePinMode);
		
		if(eOUTPUT == ePinMode)
		{
			eState = (GPIO_STATE_e) eGPIO_STATE_LOW;
			digitalWrite(nPin, (uint8_t)eState);
		}
		else
		{
			// do nothing
		}
	}
	else
	{
		Serial.println("Same pin mode, no changes");
	}
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
				// do something here
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

ERR_TYPE_e GPIO_Custom::setState(GPIO_STATE_e _state)
{
	if(eOUTPUT != ePinMode)
	{
		Serial.println("Unable to set to NOT Output pin");
		return (ERR_TYPE_e)ERR_HAPPEN;
	}
	else
	{
		eState = (GPIO_STATE_e)_state;
		digitalWrite(nPin, (uint8_t)eState);
		return (ERR_TYPE_e)ERR_OK;
	}
}

void GPIO_Custom::setTimer(GPIO_STATE_e _startState, GPIO_STATE_e _endState, uint32_t _timeInterval)
{

}

void GPIO_Custom::stopTimer(void)
{

}
