#define _____LIB_INCLUDE_____

#include <ESP8266WiFi.h>
#include "PubSubClient.h"
#include "common.h"
#include "gpio_custom.h"

#define _____MACRO_DEFINE_____

#define LED_PIN LED_BUILTIN
#define WIFI_SSID "VNPT T2"
#define WIFI_PASSWORD "18061996"

#define MQTT_BROKER_DOMAIN 	"broker.emqx.io" 
#define MQTT_SERVER_PORT		(1883U)
#define MQTT_TOPIC_PUB "DATN.datalogger/test"
#define MQTT_TOPIC_SUB "DATN.datalogger/test"
#define MQTT_USERNAME "esp8266"
#define MQTT_USERPASSWORD "123456"

// GPIO_Custom testLed(LED_PIN, (GPIO_MODE_e)eGPIO_MODE_OUTPUT, (GPIO_STATE_e)eGPIO_STATE_LOW);
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi(void);
void callback(char*, byte*, unsigned int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
	delay(2000);
	setup_wifi();
	client.setServer(MQTT_BROKER_DOMAIN, MQTT_SERVER_PORT); 
  client.setCallback(callback);
}

void setup_wifi(void) {
  delay(5000);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
		yield();
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) 
	{
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Chờ tới khi kết nối
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Thực hiện kết nối với mqtt user và pass
    if (client.connect("ESP8266Client")) 
		{
      Serial.println("connected");
      // Khi kết nối sẽ publish thông báo
      client.publish(MQTT_TOPIC_PUB, "test OK");
      // ... và nhận lại thông tin này
      client.subscribe(MQTT_TOPIC_SUB);
    } 
		else
		{
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Đợi 5s
      delay(5000);
    }
		yield();
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

	value++;
	snprintf (msg, (uint8_t)sizeof(msg), "hello world #%d", value);
	Serial.print("Publish message: ");
	Serial.println(msg);
	client.publish(MQTT_TOPIC_SUB, msg);

	yield();

	delay(2000);

}
