#include "mqtt_custom.h"

MQTT_custom::MQTT_custom()
{
	cWifiClient = WiFiClient();
	cMQTTClient = PubSubClient(cWifiClient);

	strWifiSSID = new char[MQTT_STRING_MAX_LENGTH];
	strWifiPassword = new char[MQTT_STRING_MAX_LENGTH];
	eWifiConnectionStatus = (wl_status_t)WL_IDLE_STATUS;

	strMQTTBrokerDomain = new char[MQTT_STRING_MAX_LENGTH];
	nMQTTPort = 0;
	eMQTTConnectionStatus = eMQTT_CONNECTION_NOT_OK;
	eWifiConnectionStatus = (wl_status_t)WL_IDLE_STATUS;
	strMQTTTopicPub = new char[MQTT_STRING_MAX_LENGTH];
	strMQTTTopicSub = new char[MQTT_STRING_MAX_LENGTH];
	strMQTTCurrentPubMessage = new char[MQTT_STRING_MAX_LENGTH];
	strMQTTCurrentSubMessage = new char[MQTT_STRING_MAX_LENGTH];
	resetAllData();
}

MQTT_custom::MQTT_custom(char *_wifiSSID, char *_wifiPassword)
{
	cWifiClient = WiFiClient();
	cMQTTClient = PubSubClient(cWifiClient);

	strWifiSSID = new char[MQTT_STRING_MAX_LENGTH];
	strWifiPassword = new char[MQTT_STRING_MAX_LENGTH];
	eWifiConnectionStatus = (wl_status_t)WL_IDLE_STATUS;

	strMQTTBrokerDomain = new char[MQTT_STRING_MAX_LENGTH];
	nMQTTPort = 0;
	strMQTTTopicPub = new char[MQTT_STRING_MAX_LENGTH];
	strMQTTTopicSub = new char[MQTT_STRING_MAX_LENGTH];
	strMQTTCurrentPubMessage = new char[MQTT_STRING_MAX_LENGTH];
	strMQTTCurrentSubMessage = new char[MQTT_STRING_MAX_LENGTH];

	resetAllData();

	if ((_wifiSSID != NULL) && (_wifiPassword != NULL))
	{
		strncpy(strWifiSSID, _wifiSSID, MQTT_STRING_MAX_LENGTH);
		strncpy(strWifiPassword, _wifiPassword, MQTT_STRING_MAX_LENGTH);
		connectWifi();
	}
	else
	{
		TRACE_ERROR("Wifi SSID or password is empty");
	}
}

MQTT_custom::MQTT_custom(char *_wifiSSID, char *_wifiPassword, char *_MQTTBrokerDomain, uint32_t _MQTTPort)
{
	cWifiClient = WiFiClient();
	cMQTTClient = PubSubClient(cWifiClient);

	strWifiSSID = new char[MQTT_STRING_MAX_LENGTH];
	strWifiPassword = new char[MQTT_STRING_MAX_LENGTH];
	eWifiConnectionStatus = (wl_status_t)WL_IDLE_STATUS;

	strMQTTBrokerDomain = new char[MQTT_STRING_MAX_LENGTH];
	nMQTTPort = 0;
	strMQTTTopicPub = new char[MQTT_STRING_MAX_LENGTH];
	strMQTTTopicSub = new char[MQTT_STRING_MAX_LENGTH];
	strMQTTCurrentPubMessage = new char[MQTT_STRING_MAX_LENGTH];
	strMQTTCurrentSubMessage = new char[MQTT_STRING_MAX_LENGTH];

	resetAllData();

	if ((_wifiSSID != NULL) && (_wifiPassword != NULL))
	{
		strncpy(strWifiSSID, _wifiSSID, MQTT_STRING_MAX_LENGTH);
		strncpy(strWifiPassword, _wifiPassword, MQTT_STRING_MAX_LENGTH);
		connectWifi();
	}
	else
	{
		TRACE_ERROR("Wifi SSID or password is empty");
	}

	if ((_MQTTBrokerDomain != NULL) && (_MQTTPort != 0))
	{
		strncpy(strMQTTBrokerDomain, _MQTTBrokerDomain, MQTT_STRING_MAX_LENGTH);
		nMQTTPort = _MQTTPort;
		connectWifi();
	}
	else
	{
		TRACE_ERROR("MQTT Broker domain or port is empty");
	}
}

MQTT_custom::~MQTT_custom()
{
	disconnectWifi();
	deleteAllData();
}

void MQTT_custom::resetAllData()
{
	memset(strWifiSSID, 0, MQTT_STRING_MAX_LENGTH);
	memset(strWifiPassword, 0, MQTT_STRING_MAX_LENGTH);
	eWifiConnectionStatus = (wl_status_t)WL_IDLE_STATUS;

	memset(strMQTTBrokerDomain, 0, MQTT_STRING_MAX_LENGTH);
	nMQTTPort = 0;
	memset(strMQTTTopicPub, 0, MQTT_STRING_MAX_LENGTH);
	memset(strMQTTTopicSub, 0, MQTT_STRING_MAX_LENGTH);
	memset(strMQTTCurrentPubMessage, 0, MQTT_STRING_MAX_LENGTH);
	memset(strMQTTCurrentSubMessage, 0, MQTT_STRING_MAX_LENGTH);
}

void MQTT_custom::deleteAllData()
{
	delete[] strWifiSSID;
	delete[] strWifiPassword;

	delete[] strMQTTBrokerDomain;
	delete[] strMQTTTopicPub;
	delete[] strMQTTTopicSub;
	delete[] strMQTTCurrentPubMessage;
	delete[] strMQTTCurrentSubMessage;
}

wl_status_t MQTT_custom::connectWifi()
{
	uint8_t _tryTimes = 0;

	if ((strWifiSSID == NULL) || (strWifiPassword == NULL))
	{
		TRACE_ERROR("Wifi SSID or password is empty\n");
		eWifiConnectionStatus = (wl_status_t)WL_IDLE_STATUS;
	}

	TRACE_LOG("Connecting to %s", strWifiSSID);
	WiFi.begin(strWifiSSID, strWifiPassword);

	// try connecting max 10 times
	for (_tryTimes = 0; (_tryTimes < 10) && (eWifiConnectionStatus != (wl_status_t)WL_CONNECTED); _tryTimes++)
	{
		eWifiConnectionStatus = (wl_status_t)WiFi.status();
		TRACE_LOG(".");
		delay(500);
	}

	if (eWifiConnectionStatus == (wl_status_t)WL_CONNECTED)
	{
		TRACE_LOG("\n Wifi connected. IP address: %s", WiFi.localIP());
	}
	else
	{
		TRACE_ERROR("\n Wifi connect failed\n");
	}

	return (wl_status_t)eWifiConnectionStatus;
}

wl_status_t MQTT_custom::connectWifi(char *_wifiSSID, char *_wifiPassword)
{
	if ((_wifiSSID == NULL) || (_wifiPassword == NULL))
	{
		TRACE_ERROR("Input Wifi SSID or password is empty\n");
		eWifiConnectionStatus = (wl_status_t)WL_IDLE_STATUS;

		return (wl_status_t)eWifiConnectionStatus;
	}

	strncpy(strWifiSSID, _wifiSSID, MQTT_STRING_MAX_LENGTH);
	strncpy(strWifiPassword, _wifiPassword, MQTT_STRING_MAX_LENGTH);

	return (wl_status_t)connectWifi();
}

bool MQTT_custom::disconnectWifi()
{
	return (bool)WiFi.disconnect();
}

void MQTT_custom::keepListenFromMQTTBroker()
{
	eMQTTConnectionStatus = (MQTT_CONNECTION_STATE_e)cMQTTClient.connect("ESP8266Client");
	while ((MQTT_CONNECTION_STATE_e)eMQTT_CONNECTION_NOT_OK == eMQTTConnectionStatus)
	{
		TRACE_LOG("Attempting MQTT connection...");
		eMQTTConnectionStatus = (MQTT_CONNECTION_STATE_e)cMQTTClient.connect("ESP8266Client");

		// Thực hiện kết nối với mqtt user và pass
		if (eMQTT_CONNECTION_OK == eMQTTConnectionStatus)
		{
			TRACE_LOG("connected\n");
			cMQTTClient.subscribe(strMQTTTopicSub);
		}
		else
		{
			TRACE_ERROR("failed, rc=%d. Try again in 5 seconds\n", eMQTTConnectionStatus);

			// Đợi 5s
			delay(5000);
		}
		yield();
	}
	cMQTTClient.loop();
}

void MQTT_custom::stopConnectMQTTBroker()
{
	TRACE_LOG("Disconnecting MQTT...");
	cMQTTClient.disconnect();
	TRACE_LOG("Successfully\n");
}

void MQTT_custom::publishMessage(char *_MQTTPubMessage)
{
	if (_MQTTPubMessage == NULL)
	{
		TRACE_ERROR("Publish message is empty. Can not publish\n");
		return;
	}
	strncpy(strMQTTCurrentPubMessage, _MQTTPubMessage, MQTT_STRING_MAX_LENGTH);

	if (strMQTTTopicPub == NULL)
	{
		TRACE_ERROR("Topic is not valid. Can not publish\n");
		return;
	}

	cMQTTClient.publish(strMQTTTopicPub, strMQTTCurrentPubMessage);
	// TRACE_LOG("Publish message %s success\n", strMQTTCurrentPubMessage);
}

char *MQTT_custom::getWifiSSID(void)
{
	return strWifiSSID;
}

char *MQTT_custom::getWifiPassword(void)
{
	return strWifiPassword;
}

wl_status_t MQTT_custom::getWifiConnectionStatus(void)
{
	return (wl_status_t)eWifiConnectionStatus;
}

char *MQTT_custom::getMQTTBrokerDomain(void)
{
	return strMQTTBrokerDomain;
}

uint32_t MQTT_custom::getMQTTPort(void)
{
	return nMQTTPort;
}

void MQTT_custom::setupMQTT(char *_MQTTBrokerDomain, uint32_t _MQTTPort)
{
	if ((_MQTTBrokerDomain == NULL) || (_MQTTPort == 0))
	{
		TRACE_ERROR("Input MQTT broker domain or port is empty\n");
		return;
	}

	strncpy(strMQTTBrokerDomain, _MQTTBrokerDomain, MQTT_STRING_MAX_LENGTH);
	nMQTTPort = _MQTTPort;

	cMQTTClient.setServer(strMQTTBrokerDomain, nMQTTPort);
}

char *MQTT_custom::getMQTTTopicPub(void)
{
	return strMQTTTopicPub;
}

void MQTT_custom::setMQTTTopicPub(char *_MQTTTopicPub)
{
	strncpy(strMQTTTopicPub, _MQTTTopicPub, MQTT_STRING_MAX_LENGTH);
}

char *MQTT_custom::getMQTTTopicSub(void)
{
	return strMQTTTopicSub;
}

void MQTT_custom::setMQTTTopicSub(char *_MQTTTopicSub)
{
	strncpy(strMQTTTopicSub, _MQTTTopicSub, MQTT_STRING_MAX_LENGTH);
	cMQTTClient.subscribe(strMQTTTopicSub);
}

char *MQTT_custom::getCurrentPubMessage(void)
{
	return strMQTTCurrentPubMessage;
}

void MQTT_custom::setCurrentPubMessage(char *_MQTTPubMessage)
{
	strncpy(strMQTTCurrentPubMessage, _MQTTPubMessage, MQTT_STRING_MAX_LENGTH);
}

char *MQTT_custom::getCurrentSubMessage(void)
{
	return strMQTTCurrentSubMessage;
}

void MQTT_custom::setCurrentSubMessage(char *_MQTTSubMessage)
{
	strncpy(strMQTTCurrentSubMessage, _MQTTSubMessage, MQTT_STRING_MAX_LENGTH);
}
