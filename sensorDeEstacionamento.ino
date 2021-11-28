#include "DistanceDisplay.h"
#include "WifiManager.h"
#include "MqttClient.h"
#include "DistanceSensor.h"
#include "Buzzer.h"

DistanceDisplay *distanceDisplay;
WifiManager *wifiManager;
MqttClient *mqttClient;
DistanceSensor *distanceSensor;
Buzzer *buzzer;

long measureTime;
long transmitTime;
int distance;

void setup() {
  Serial.begin(115200);
  distanceSensor = new DistanceSensor();
  buzzer = new Buzzer();
  distanceDisplay = new DistanceDisplay();
  wifiManager = new WifiManager();
  wifiManager->startConnection();
  mqttClient = new MqttClient(wifiManager);
  mqttClient->startConnection();
}

void loop() {
  int currentTime = millis();
  if(currentTime > (measureTime + 100)){
    measureTime = currentTime;
    distance = distanceSensor->measureInCm();
    distanceDisplay->updateDistance(distance);
  }
  if(currentTime > (transmitTime + 1000)) {
    transmitTime = currentTime;
    mqttClient->sendDistance(distance);
  }
  if(distance < maximumDistance){
    int timeDelay = map(distance, minimumDistance, maximumDistance, 200, 1000);
    buzzer->setInterval(timeDelay);
  } else {
    buzzer->stop();
  }
  buzzer->loop();
  mqttClient->loop();
}
