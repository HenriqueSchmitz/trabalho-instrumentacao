#ifndef Buzzer_h
#define Buzzer_h

class Buzzer {
  public:
    Buzzer();
    void loop();
    void setInterval(int interval);
    void stop();
  private:
    const int buzzerFrequency = 300;
    const int beepDuration = 200;
    const int buzzerPwmChannel = 0;
    const int buzzerPin = 26;
    long onTime;
    bool isPlaying;
    bool isPlayingContinuously;
    int interval;
};

Buzzer::Buzzer() {
  ledcAttachPin(this->buzzerPin, this->buzzerPwmChannel);
  this->isPlaying = false;
  this->isPlayingContinuously = false;
  this->onTime = 0;
}

void Buzzer::loop() {
  if(this->isPlaying){
    if(this->interval <= this->beepDuration) {
      if(!this->isPlayingContinuously) {
        this->isPlayingContinuously = true;
        ledcWriteTone(this->buzzerPwmChannel, this->buzzerFrequency);
      }
    } else {
      long currentTime = millis();
      this->isPlayingContinuously = false;
      if(currentTime > (this->onTime + this->interval)) {
        ledcWriteTone(this->buzzerPwmChannel, this->buzzerFrequency);
        this->onTime = currentTime;
      } else if(currentTime > (this->onTime + this->beepDuration)) {
        ledcWriteTone(this->buzzerPwmChannel, 0);
      }
    }
  } else {
    ledcWriteTone(this->buzzerPwmChannel, 0);
  }
}

void Buzzer::setInterval(int interval) {
  this->interval = interval;
  this->isPlaying = true;
}

void Buzzer::stop() {
  this->isPlaying = false;
  this->isPlayingContinuously = false;
}

#endif
