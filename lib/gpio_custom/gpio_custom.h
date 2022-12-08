#ifndef __GPIO_CUSTOM_H__
#define __GPIO_CUSTOM_H__

#define _____LIB_INCLUDE_____
#include "common.h"

#define _____ENUM_DEFINE_____


#define _____CLASS_DEFINE_____

class GPIO_Custom
{
private:
	uint8_t nPin;
	GPIO_MODE_e ePinMode;
	GPIO_STATE_e eState;

public:
	GPIO_Custom(uint8_t _pin, GPIO_MODE_e _pinMode);
	GPIO_Custom(uint8_t _pin, GPIO_MODE_e _pinMode, GPIO_STATE_e _state);
	
	uint8_t getPin(void);
	GPIO_MODE_e getPinMode(void);
	ERR_TYPE_e setPinMode(GPIO_MODE_e _newPinMode);
	GPIO_STATE_e getState(void);
	ERR_TYPE_e setState(GPIO_STATE_e _state);
	void setTimer(GPIO_STATE_e _startState, GPIO_STATE_e _endState, uint32_t _timeInterval);
	void stopTimer(void);

};

#endif