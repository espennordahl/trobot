#ifndef STATE_H
#define STATE_H

#include "UltrasonicSensor.h"

class Action;

#define SENSORMAX 200

class State{
	public:
		State(TrUltrasonicSensor *centerSensor, TrUltrasonicSensor *leftSensor, TrUltrasonicSensor *rightSensor){
			m_centerSensor = centerSensor;
			m_leftSensor = leftSensor;
			m_rightSensor = rightSensor;
			m_speed = 250;
		};

  		Action *nextAction() { return m_nextAction; };
		void setNextAction(Action *action) { m_nextAction = action; };

  		Action *previousAction() { return m_previousAction; };
		void setPreviousAction(Action *action) { m_previousAction = action; };

  		long centerDepth() { return m_centerDepth; };
  		long leftDepth() { return m_leftDepth; };
  		long rightDepth() { return m_rightDepth; };

	  	void update(){
      		m_centerDepth = m_centerSensor->distanceCm(SENSORMAX);
	  		m_leftDepth = m_leftSensor->distanceCm(SENSORMAX);
	  		m_rightDepth = m_rightSensor->distanceCm(SENSORMAX);

			Serial.println("center depth:");
			Serial.println(m_centerDepth);
			Serial.println("left depth:");
			Serial.println(m_leftDepth);
			Serial.println("right depth:");
			Serial.println(m_rightDepth);
		}

		int moveSpeed(){
			return m_speed;
		}

		void speedUp(){
			if (m_speed < 250){
				m_speed += 50;
			}
		};

		void slowDown(){
			if (m_speed){
				m_speed -= 50;
			}
		};

	private:
	  	Action *m_nextAction;
  		Action *m_previousAction;

		TrUltrasonicSensor *m_centerSensor;
		TrUltrasonicSensor *m_leftSensor;
		TrUltrasonicSensor *m_rightSensor;

  		long m_centerDepth;
  		long m_leftDepth;
  		long m_rightDepth;
		int m_speed;
};

#endif
