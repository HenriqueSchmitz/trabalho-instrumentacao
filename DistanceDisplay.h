#ifndef DistanceDisplay_h
#define DistanceDisplay_h

#include <TFT_eSPI.h>
#include <SPI.h>

class DistanceDisplay {
  public:
    DistanceDisplay();
    void updateDistance(int distance);
  private:
    TFT_eSPI *tft;
    int previousDistance;
    char displayText[6];
};

DistanceDisplay::DistanceDisplay() {
  this->tft = new TFT_eSPI();
  this->tft->init();
  this->tft->setRotation(1);
  this->tft->setTextSize(3);
  this->tft->setTextColor(TFT_WHITE);
}

void DistanceDisplay::updateDistance(int distance) {
  if(distance != this->previousDistance){
    this->previousDistance = distance;
    if(distance < 10){
      sprintf(this->displayText, "0%d cm", distance);
    } else {
      sprintf(this->displayText, "%d cm", distance);
    }
    this->tft->fillScreen(TFT_BLACK);
    this->tft->drawString(this->displayText, 10, 32, 4);
  }
}

#endif
