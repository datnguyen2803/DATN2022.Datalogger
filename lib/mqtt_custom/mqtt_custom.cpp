#include "mqtt_custom.h"

MQTT_custom::MQTT_custom()
{
	memset(strWifiSSID, 0, sizeof(strWifiSSID));
		char strMQTTBrokerDomain[MQTT_STRING_MAX_LENGTH];
	uint32_t nMQTTPort;
	char strMQTTTopicPub[MQTT_STRING_MAX_LENGTH];
	char strMQTTTopicSub[MQTT_STRING_MAX_LENGTH];
	char strMQTTCurrentPubMessage[MQTT_STRING_MAX_LENGTH];
	char strMQTTCurrentSubMessage[MQTT_STRING_MAX_LENGTH];
}