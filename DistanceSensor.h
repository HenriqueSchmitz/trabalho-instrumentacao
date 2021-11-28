#ifndef DistanceSensor_h
#define DistanceSensor_h

class DistanceSensor {
  public:
    DistanceSensor();
    int measureInCm();
  private:
    const int echoPin = 21;
    const int trigPin = 22;
};

DistanceSensor::DistanceSensor() {
  pinMode(this->trigPin, OUTPUT);
  pinMode(this->echoPin, INPUT);
}

int DistanceSensor::measureInCm() {
  digitalWrite(this->trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->trigPin, LOW);
  int duration = pulseIn(this->echoPin, HIGH);
  return duration * 0.034 / 2;
}

#endif
