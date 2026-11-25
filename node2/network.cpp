#include "network.h"
#include "config.h"
#include <Ethernet.h>
#include <PubSubClient.h>

static PubSubClient* mqtt = NULL;
static byte mac[6] = NODE_MAC;
static unsigned long lastReconnectTime = 0;
static void (*onConnectedCallback)(void) = NULL;

static void doConnect(void)
{
  if (mqtt == NULL) return;

  Serial.print("Connecting MQTT... ");

  if (mqtt->connect(CLIENT_ID, ACCESS_TOKEN, NULL))
  {
    Serial.println("OK");

    if (onConnectedCallback != NULL)
    {
      onConnectedCallback();   
    }
  }
  else
  {
    Serial.print("FAILED, rc=");
    Serial.println(mqtt->state());
  }
}

void network_begin(PubSubClient* mqttClient, void (*onConnected)(void))
{
  mqtt = mqttClient;
  onConnectedCallback = onConnected;

  Serial.println("Starting Ethernet...");

  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("DHCP failed");
    
  }

  delay(1500);

  mqtt->setServer(TB_SERVER, TB_PORT);

  doConnect();
}

void network_maintain(void)
{
  Ethernet.maintain();

  if (mqtt != NULL && mqtt->connected())
  {
    mqtt->loop();   
  }
  else
  {
    unsigned long now = millis();

    if (now - lastReconnectTime >= RECONNECT_INTERVAL)
    {
      lastReconnectTime = now;
      doConnect();
    }
  }
}

uint8_t network_isConnected(void)
{
  if (mqtt == NULL) return 0;
  return (uint8_t)mqtt->connected();
}

uint8_t network_publish(const char* topic, const char* payload, uint8_t retain)
{
  if (mqtt == NULL || !mqtt->connected()) return 0;
  return (uint8_t)mqtt->publish(topic, payload, (bool)retain);
}