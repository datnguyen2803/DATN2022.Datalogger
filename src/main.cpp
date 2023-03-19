#define _____LIB_INCLUDE_____

// #include <ESP8266WiFi.h>
// #include "PubSubClient.h"
#include "common.h"
#include "gpio_custom.h"
#include "mqtt_custom.h"

#define _____MACRO_DEFINE_____

#define LED_POWER LED_BUILTIN
#define WIFI_SSID "VNPT T2"
#define WIFI_PASSWORD "18061996"
#define PUMP_0 D8
#define PUMP_1 D7
#define PUMP_2 D6
#define PUMP_3 D5

#define LED_0 D4
#define LED_1 D3
#define LED_2 D2
#define LED_3 D1

#define ANALOG_PIN A0

#define DATALOG_DELAY (15000U)

#define MQTT_BROKER_DOMAIN 	"broker.emqx.io" 
#define MQTT_BROKER_PORT		(1883U)
#define MQTT_TOPIC_PUB "DATN.Pumpmonitor/Pump"
#define MQTT_TOPIC_SUB "DATN.Pumpmonitor/Pump"
#define MQTT_USERNAME "esp8266"
#define MQTT_USERPASSWORD "123456"

MQTT_custom pumpClient;

GPIO_Custom pump0x = GPIO_Custom(PUMP_0, (GPIO_MODE_e)eGPIO_MODE_INPUT);
GPIO_Custom pump1x = GPIO_Custom(PUMP_1, (GPIO_MODE_e)eGPIO_MODE_INPUT);
GPIO_Custom pump2x = GPIO_Custom(PUMP_2, (GPIO_MODE_e)eGPIO_MODE_INPUT);
GPIO_Custom pump3x = GPIO_Custom(PUMP_3, (GPIO_MODE_e)eGPIO_MODE_INPUT);

// turn off by default
GPIO_Custom led0x = GPIO_Custom(LED_0, (GPIO_MODE_e)eGPIO_MODE_OUTPUT);
GPIO_Custom led1x = GPIO_Custom(LED_1, (GPIO_MODE_e)eGPIO_MODE_OUTPUT);
GPIO_Custom led2x = GPIO_Custom(LED_2, (GPIO_MODE_e)eGPIO_MODE_OUTPUT);
GPIO_Custom led3x = GPIO_Custom(LED_3, (GPIO_MODE_e)eGPIO_MODE_OUTPUT);

// void setup_wifi(void);
void callback(char*, byte*, unsigned int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setDebugOutput(true);
	delay(2000);


	// blink to indicate starting
	led0x.setState((GPIO_STATE_e)eGPIO_STATE_HIGH);
	led1x.setState((GPIO_STATE_e)eGPIO_STATE_HIGH);
	led2x.setState((GPIO_STATE_e)eGPIO_STATE_HIGH);
	led3x.setState((GPIO_STATE_e)eGPIO_STATE_HIGH);
	delay(200);
	led0x.setState((GPIO_STATE_e)eGPIO_STATE_LOW);
	led1x.setState((GPIO_STATE_e)eGPIO_STATE_LOW);
	led2x.setState((GPIO_STATE_e)eGPIO_STATE_LOW);
	led3x.setState((GPIO_STATE_e)eGPIO_STATE_LOW);

	// end blink

	pumpClient.connectWifi(WIFI_SSID, WIFI_PASSWORD);
	pumpClient.setupMQTT(MQTT_BROKER_DOMAIN, MQTT_BROKER_PORT);
  	pumpClient.cMQTTClient.setCallback(callback);

	pumpClient.setMQTTTopicPub(MQTT_TOPIC_PUB);
	pumpClient.setMQTTTopicSub(MQTT_TOPIC_SUB);
}


void callback(char* topic, byte* payload, unsigned int length) 
{
	char tempMessage[length];
  for (unsigned int i = 0; i < length; i++) 
	{
    tempMessage[i] = (char)payload[i];
  }

	pumpClient.setCurrentSubMessage(tempMessage);

	Serial.printf("Message arrived [%s]: %s\n", pumpClient.getMQTTTopicSub(), pumpClient.getCurrentSubMessage());

}

void loop() {

	char myString[100];

	pumpClient.keepListenFromMQTTBroker();


	Serial.println("===== STATE OF PUMPS =====");
	memset(myString, 0, 100);
	sprintf(myString, "pump_A_01_%d", (uint8_t)pump0x.getState());
	pumpClient.publishMessage(myString);
	if(pump0x.getState() == (GPIO_STATE_e)eGPIO_STATE_HIGH)
	{
		// turn on
		led0x.setState((GPIO_STATE_e)eGPIO_STATE_HIGH);
		// digitalWrite(LED_0, 1);
	}
	else
	{
		// turn off
		led0x.setState((GPIO_STATE_e)eGPIO_STATE_LOW);
		// digitalWrite(LED_0, 0);
	}
	Serial.println(pumpClient.getCurrentPubMessage());
	delay(DATALOG_DELAY);

	memset(myString, 0, 100);
	sprintf(myString, "pump_A_02_%d", (uint8_t)pump1x.getState());
	pumpClient.publishMessage(myString);
	if(pump1x.getState() == (GPIO_STATE_e)eGPIO_STATE_HIGH)
	{
		// turn on
		led1x.setState((GPIO_STATE_e)eGPIO_STATE_HIGH);
	}
	else
	{
		// turn off
		led1x.setState((GPIO_STATE_e)eGPIO_STATE_LOW);
	}
	Serial.println(pumpClient.getCurrentPubMessage());
	delay(DATALOG_DELAY);

	memset(myString, 0, 100);
	sprintf(myString, "pump_A_03_%d", (uint8_t)pump2x.getState());
	pumpClient.publishMessage(myString);
	if(pump2x.getState() == (GPIO_STATE_e)eGPIO_STATE_HIGH)
	{
		// turn on
		led2x.setState((GPIO_STATE_e)eGPIO_STATE_HIGH);
	}
	else
	{
		// turn off
		led2x.setState((GPIO_STATE_e)eGPIO_STATE_LOW);
	}
	Serial.println(pumpClient.getCurrentPubMessage());
	delay(DATALOG_DELAY);

	memset(myString, 0, 100);
	sprintf(myString, "pump_A_04_%d", (uint8_t)pump3x.getState());
	pumpClient.publishMessage(myString);
	if(pump3x.getState() == (GPIO_STATE_e)eGPIO_STATE_HIGH)
	{
		// turn on
		led3x.setState((GPIO_STATE_e)eGPIO_STATE_HIGH);
	}
	else
	{
		// turn off
		led3x.setState((GPIO_STATE_e)eGPIO_STATE_LOW);
	}
	Serial.println(pumpClient.getCurrentPubMessage());
	delay(DATALOG_DELAY);

}
