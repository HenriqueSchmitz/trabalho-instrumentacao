#ifndef WifiManager_h
#define WifiManager_h

#include <WiFi.h>

class WifiManager {
  public:
    void startConnection();
    String getMacAddress();
  private:
    const char *ssid = "Ap 403";
    const char *password = "35945963";
    const int connectionTimeout = 20000;
    long connectionStartTime;
};

void WifiManager::startConnection() {
  WiFi.begin(this->ssid, this->password);
  this->connectionStartTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
      if(millis() > (this->connectionStartTime + connectionTimeout)){
        Serial.println("Unable to connect. Restaring...");
        delay(1500);
        ESP.restart();
      }
      Serial.println("Connecting to WiFi..");
      delay(500);
  }
}

String WifiManager::getMacAddress(){
  return String(WiFi.macAddress());
}

#endif
