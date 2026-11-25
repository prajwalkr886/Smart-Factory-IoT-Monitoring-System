#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <DHT.h>

#include "config.h"
#include "SensorManager.h"
#include "actuator.h"
#include "network.h"
#include "telemetry.h"
#include "rpc.h"

static char sharedBuf[200];

static EthernetClient ethClient;
static PubSubClient mqttClient(ethClient);

unsigned long lastTelemetry = 0;


void onConnected()
{
  Serial.println("MQTT Connected");
}

void setup() 
{
  Serial.begin(9600);
  Serial.print("Node1 is booting... ");

  
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  Ethernet.begin(mac);
  delay(1000);

  // init sensors
  sensor_begin();

  // init actuators
  actuators_begin();

  telemetry_init(sharedBuf, sizeof(sharedBuf));
  rpc_init(&mqttClient,sharedBuf, sizeof(sharedBuf));

  mqttClient.setCallback(rpc_mqttCallback);
  network_begin(&mqttClient, onConnected);
 

  digitalWrite(PIN_LED_RED, LOW);
}

void loop() 
{
  network_maintain();

  SensorData data;
  sensors_read(&data);

  if (network_isConnected())
  {
    unsigned long now = millis();

    if (now - lastTelemetry >= TELEMETRY_INTERVAL)
    {
      lastTelemetry = now;
      telemetry_publishTelemetry(&data, actuators_getRelayState);
    }
  }
  actuators_updateStatusLEDs(network_isConnected(), data.sensorError);
  
}















