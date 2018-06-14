#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <MeMCore.h>

class TrUltrasonicSensor{

	public:
		UtrasonicSensor(){};

		virtual double distanceCm(uint16_t maxCm);
};

class TrMeUltrasonicSensor : public TrUltrasonicSensor {

	public:
		TrMeUltrasonicSensor(uint8_t port) 
		: TrUltrasonicSensor() {
			m_sensor = MeUltrasonicSensor(port);
		}

		double distanceCm(uint16_t maxCm){
			return m_sensor.distanceCm(maxCm);	
		}

	private:
		MeUltrasonicSensor m_sensor;
};

class TrKjUltrasonicSensor : public TrUltrasonicSensor {

	public:
		TrKjUltrasonicSensor(uint8_t trigPin, uint8_t echoPin) 
		: TrUltrasonicSensor() { 
			m_trigPin = trigPin;
			m_echoPin = echoPin;
		  	pinMode(m_trigPin, OUTPUT);
  			pinMode(m_echoPin, INPUT);
		};

		double distanceCm(uint16_t maxCm){
      		long duration;
      		digitalWrite(m_trigPin, LOW); 
		  	delayMicroseconds(2);
		  	digitalWrite(m_trigPin, HIGH);
		  	delayMicroseconds(10); 
		  	digitalWrite(m_trigPin, LOW);
		  	duration = pulseIn(m_echoPin, HIGH);

		  	double depth = duration / 58.;
		  	return min(maxCm, depth);
		};

	private:
		uint8_t m_trigPin;
		uint8_t m_echoPin;
};

#endif
