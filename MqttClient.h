#ifndef MqttClient_h
#define MqttClient_h

#include <PubSubClient.h>
#include <WiFi.h>
#include "WifiManager.h"

void callback(char *topic, byte *payload, unsigned int length);
int minimumDistance = 5;
int maximumDistance = 30;

class MqttClient {
  public:
    MqttClient(WifiManager *wifiManager);
    void startConnection();
    void sendDistance(int distance);
    void loop();
    static int *minimumDistance;
    static int *maximumDistance;
    static constexpr char *setMaximumDistanceTopic = "set-maximum-distance";
    static constexpr char *setMinimumDistanceTopic = "set-minimum-distance";
  private:
    WifiManager *wifiManager;
    WiFiClient *espClient;
    PubSubClient *client;
    const char *broker = "broker.emqx.io";
    const char *distanceTopic = "measurement";
    const char *username = "emqx";
    const char *password = "public";
    const int port = 1883;
    int lastDistance;
};

MqttClient::MqttClient(WifiManager *wifiManager){
  this->wifiManager = wifiManager;
  this->espClient = new WiFiClient();
  this->client = new PubSubClient(*this->espClient);
}

void MqttClient::startConnection() {
  client->setServer(this->broker, this->port);
  client->setCallback(callback);
  while (!client->connected()) {
      String client_id = "esp32-client-";
      client_id += this->wifiManager->getMacAddress();
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
      if (client->connect(client_id.c_str(), this->username, this->password)) {
          Serial.println("Public emqx mqtt broker connected");
      } else {
          Serial.print("Failed with state ");
          Serial.print(client->state());
          delay(2000);
      }
  }
  client->subscribe(this->setMaximumDistanceTopic);
  client->subscribe(this->setMinimumDistanceTopic);
}

void::MqttClient::sendDistance(int distance) {
  if(distance != this->lastDistance){
    this->lastDistance = distance;
    char messageText[6];
    sprintf(messageText, "%d cm", distance);
    client->publish(distanceTopic, messageText);
  }
}

void MqttClient::loop(){
  client->loop();
}

void callback(char *topic, byte *payload, unsigned int length) {
 if(strcmp(topic, MqttClient::setMinimumDistanceTopic) == 0){
  minimumDistance = atoi((char*)payload);
 } else if(strcmp(topic, MqttClient::setMaximumDistanceTopic) == 0){
  maximumDistance = atoi((char*)payload);
 }
}

#endif
