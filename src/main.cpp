#define _____LIB_INCLUDE_____

#include "common.h"
#include "gpio_custom.h"

#define _____MACRO_DEFINE_____

#define LED_PIN LED_BUILTIN

GPIO_Custom testLed(LED_PIN, (GPIO_MODE_e)eOUTPUT, (GPIO_STATE_e)eGPIO_STATE_LOW);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  testLed.setState((GPIO_STATE_e)eGPIO_STATE_LOW);
  TRACE_LOG("Led state: %d", (uint8_t)testLed.getState());
  delay(1000);
  testLed.setState((GPIO_STATE_e)eGPIO_STATE_HIGH);
  // Serial.println("LED off");
	TRACE_LOG("Led state: %d", (uint8_t)testLed.getState());
  delay(1000);
}
