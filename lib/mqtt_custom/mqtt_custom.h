#ifndef __MQTT_CUSTOM_H__
#define __MQTT_CUSTOM_H__

#define __________LIB_INCLUDE__________
#include "common.h"
#include <ESP8266WiFi.h>
#include "PubSubClient.h"

#define __________MACRO_DEFINE__________
#define MQTT_STRING_MAX_LENGTH		(50U)

typedef struct
{
	char* strWifiSSID[MQTT_STRING_MAX_LENGTH];
	char* strWifiPassword[MQTT_STRING_MAX_LENGTH];
}WIFI_INFO_t;

#define __________CLASS_DEFINE__________

class MQTT_custom
{
private:
	char* strWifiSSID;
	char* strWifiPassword;
	wl_status_t eWifiConnectionStatus;

	char* strMQTTBrokerDomain;
	uint32_t nMQTTPort;


	char* strMQTTTopicPub;
	char* strMQTTTopicSub;
	char* strMQTTCurrentPubMessage;
	char* strMQTTCurrentSubMessage;

public:
	WiFiClient cWifiClient;
	PubSubClient cMQTTClient;

	MQTT_custom();
	MQTT_custom(char* _wifiSSID, char* _wifiPassword);
	MQTT_custom(char* _wifiSSID, char* _wifiPassword, char* _MQTTBrokerDomain, uint32_t _MQTTPort);

	//getter, setter
	char*			getWifiSSID(void);
	char*			getWifiPassword(void);
	wl_status_t	getWifiConnectionStatus(void);
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

	void			Init();
	void			DeInit();
	void			Run();
	void			resetAllData();
	void			deleteAllData();

	wl_status_t			connectWifi();
	wl_status_t			connectWifi(char* _wifiSSID, char* _wifiPassword);
	bool			disconnectWifi();
	void			keepConnectMQTTBroker();
	void			stopConnectMQTTBroker();
	void			publishMessage(char* _MQTTPubMessage);

};

#endif