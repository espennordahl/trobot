#ifndef MOTOR_H
#define MOTOR_H

class TrKjMotor {

  public:
    TrKjMotor(uint8_t channel) { 
        if (channel == 0){
          m_directionPin = 12;
          m_speedPin = 3;
          m_brakePin = 9;
        } else {
          m_directionPin = 13;
          m_speedPin = 11;
          m_brakePin = 8;
        }
        pinMode(m_directionPin, OUTPUT);
    };

  void run(int speed){
    if (speed == 0){
      digitalWrite(m_brakePin, HIGH);
      return;
    }
    digitalWrite(m_brakePin, LOW);
    if (speed > 0){
      digitalWrite(m_directionPin, HIGH);
    } else {
      digitalWrite(m_directionPin, LOW);
    }
    analogWrite(m_speedPin, abs(speed));
  }

  void brake(){
    digitalWrite(m_brakePin, HIGH);
  }

  private:
    uint8_t m_directionPin;
    uint8_t m_speedPin;
    uint8_t m_brakePin;
};

#endif 
