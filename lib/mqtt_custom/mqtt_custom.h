#ifndef __MQTT_CUSTOM_H__
#define __MQTT_CUSTOM_H__

#define __________LIB_INCLUDE__________
#include "common.h"
#include <ESP8266WiFi.h>
#include "PubSubClient.h"

#define __________MACRO_DEFINE__________
#define MQTT_STRING_MAX_LENGTH	(50U)

#define MQTT_BROKER_DOMAIN 	"broker.emqx.io" 
#define MQTT_SERVER_PORT		(1883U)
#define MQTT_TOPIC_PUB "DATN.datalogger/test"
#define MQTT_TOPIC_SUB "DATN.datalogger/test"
#define MQTT_USERNAME "esp8266"
#define MQTT_USERPASSWORD "123456"

#define __________CLASS_DEFINE__________

class MQTT_custom
{
private:
	char strWifiSSID[MQTT_STRING_MAX_LENGTH];
	char strWifiPassword[MQTT_STRING_MAX_LENGTH];
	char strMQTTBrokerDomain[MQTT_STRING_MAX_LENGTH];
	uint32_t nMQTTPort;
	char strMQTTTopicPub[MQTT_STRING_MAX_LENGTH];
	char strMQTTTopicSub[MQTT_STRING_MAX_LENGTH];
	char strMQTTCurrentPubMessage[MQTT_STRING_MAX_LENGTH];
	char strMQTTCurrentSubMessage[MQTT_STRING_MAX_LENGTH];

public:
	WiFiClient cWifiClient;
	PubSubClient cMQTTClient;

	MQTT_custom();
	MQTT_custom(char* _wifiSSID, char* _wifiPassword);
	MQTT_custom(char* _wifiSSID, char* _wifiPassword, char* _MQTTBrokerDomain, uint32_t _MQTTPort);

	//getter, setter
	char*			getWifiSSID(void);
	char*			getWifiPassword(void);
	void			setupWifi(char* _wifiSSID, char* _wifiPassword);
	char*			getMQTTBrokerDomain(void);
	uint32_t	getMQTTPort(void);
	void			setupMQTT(char* _MQTTBrokerDomain, uint32_t _MQTTPort);
	char*			getMQTTTopicPub(void);
	void			setMQTTTopicPub(char* _MQTTTopicPub);
	char*			getMQTTTopicSub(void);
	void			setMQTTTopicSub(char* _MQTTTopicSub);
	char*			getCurrentPubMessage(void);
	void			setCurrentPubMessage(char* _MQTTPubMessage);
	char*			getCurrentSubMessage(void);
	void			setCurrentSubMessage(void);

	void	Init();
	void	DeInit();
	void	Run();

	void	connectWifi();
	void	connectWifi(char* _wifiSSID, char* _wifiPassword);
	void	keepConnectMQTTBroker();
	void	stopConnectMQTTBroker();
	void	publishMessage(char* _MQTTPubMessage);

};

#endif