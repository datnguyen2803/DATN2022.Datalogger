#define _____LIB_INCLUDE_____

// #include <ESP8266WiFi.h>
// #include "PubSubClient.h"
#include "common.h"
#include "gpio_custom.h"
#include "mqtt_custom.h"

#define _____MACRO_DEFINE_____

#define LED_PIN LED_BUILTIN
#define WIFI_SSID "DATCHAOS"
#define WIFI_PASSWORD "88888888"

#define MQTT_BROKER_DOMAIN 	"broker.emqx.io" 
#define MQTT_BROKER_PORT		(1883U)
#define MQTT_TOPIC_PUB "DATN.datalogger/test"
#define MQTT_TOPIC_SUB "DATN.datalogger/test"
#define MQTT_USERNAME "esp8266"
#define MQTT_USERPASSWORD "123456"

// GPIO_Custom testLed(LED_PIN, (GPIO_MODE_e)eGPIO_MODE_OUTPUT, (GPIO_STATE_e)eGPIO_STATE_LOW);


MQTT_custom sensor;

// void setup_wifi(void);
void callback(char*, byte*, unsigned int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
	delay(2000);
	pinMode(LED_PIN, OUTPUT);

	sensor.connectWifi(WIFI_SSID, WIFI_PASSWORD);
	sensor.setupMQTT(MQTT_BROKER_DOMAIN, MQTT_BROKER_PORT);
  sensor.cMQTTClient.setCallback(callback);

	sensor.setMQTTTopicPub(MQTT_TOPIC_PUB);
	sensor.setMQTTTopicSub(MQTT_TOPIC_SUB);
}


void callback(char* topic, byte* payload, unsigned int length) 
{
	char tempMessage[length];
  for (unsigned int i = 0; i < length; i++) 
	{
    tempMessage[i] = (char)payload[i];
  }

	sensor.setCurrentSubMessage(tempMessage);

	Serial.printf("Message arrived [%s]: %s\n\n", sensor.getMQTTTopicSub(), sensor.getCurrentSubMessage());

	if(strncmp(tempMessage, "led off", sizeof(tempMessage)) == 0)
	{
		digitalWrite(LED_PIN, 1);
	}
	else	if(strncmp(tempMessage, "led on", sizeof(tempMessage)) == 0)
	{
		digitalWrite(LED_PIN, 0);
	}
}

// void reconnect() {
//   // Chờ tới khi kết nối
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     // Thực hiện kết nối với mqtt user và pass
//     if (client.connect("ESP8266Client")) 
// 		{
//       Serial.println("connected");
//       // Khi kết nối sẽ publish thông báo
//       client.publish(MQTT_TOPIC_PUB, "test OK");
//       // ... và nhận lại thông tin này
//       client.subscribe(MQTT_TOPIC_SUB);
//     } 
// 		else
// 		{
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5 seconds");
//       // Đợi 5s
//       delay(5000);
//     }
// 		yield();
//   }
// }

void loop() {
  // if (!client.connected()) {
  //   reconnect();
  // }
  // client.loop();

	// value++;
	// snprintf (msg, (uint8_t)sizeof(msg), "hello world #%d", value);
	// Serial.print("Publish message: ");
	// Serial.println(msg);
	// client.publish(MQTT_TOPIC_SUB, msg);

	// yield();

	// delay(2000);

	sensor.keepListenFromMQTTBroker();
	// sensor.publishMessage("led toggle");
	delay(2000);

}
