#ifndef ACTION_H
#define ACTION_H

#include "State.h"

#define DIR_FORWARD 0
#define DIR_LEFT 1
#define DIR_RIGHT 2

#define ACTIONTIME 100,state->moveSpeed()*3



class Action{
  public:
    Action(MeDCMotor *motorL, MeDCMotor *motorR){
      m_motorL = motorL;
      m_motorR = motorR;
    }

    int pdf(){
      return m_pdf;
    }

    virtual short direction(){};

    virtual void perform(State *state){};

    virtual void updatePdf(State *state){};

  protected:
    MeDCMotor *m_motorL;
    MeDCMotor *m_motorR;
    int m_pdf;
};


class ActionForward : public Action{
  public:
    ActionForward(MeDCMotor *motorL, MeDCMotor *motorR)
    : Action(motorL, motorR) { 
          Serial.println("Initializing ActionForward");
      };
      
    void perform(State *state){
      m_motorL->run(-state->moveSpeed());
      m_motorR->run(state->moveSpeed());
      delay(random(ACTIONTIME));
    }

    void updatePdf(State *state){
      m_pdf = remap(state->centerDepth(), 10, 100, 5, 100);
      Serial.println("Forward pdf: ");
      Serial.println(m_pdf);
    }

    short direction(){
      return DIR_FORWARD;
    }
};

class ActionBackward : public Action{
  public:
    ActionBackward(MeDCMotor *motorL, MeDCMotor *motorR)
    : Action(motorL, motorR) { 
          Serial.println("Initializing ActionBackward");
      };
      
    void perform(State *state){
      m_motorL->run(state->moveSpeed());
      m_motorR->run(-state->moveSpeed());
      delay(random(ACTIONTIME));
    }

    void updatePdf(State *state){
      m_pdf = remap(state->centerDepth(), 50, 0, 1, 50);
      Serial.println("Backward pdf: ");
      Serial.println(m_pdf);
    }

    short direction(){
      return DIR_FORWARD;
    }
};

class ActionRotateLeft : public Action{
  public:
    ActionRotateLeft(MeDCMotor *motorL, MeDCMotor *motorR)
    : Action(motorL, motorR) { 
      Serial.println("Initializing ActionRotateLeft");
    };

    void perform(State *state){
      m_motorL->run(state->moveSpeed());
      m_motorR->run(state->moveSpeed());
      delay(random(ACTIONTIME));
    }

    void updatePdf(State *state){
      if (state->previousAction() && state->previousAction()->direction() == DIR_RIGHT){
        m_pdf = 1;
      } else {
        m_pdf = remap(state->centerDepth(), 50, 0, 5, 100) + remap(state->rightDepth(), 50, 0, 5, 30);
      }
      Serial.println("Left pdf: ");
      Serial.println(m_pdf);
    }

    short direction(){
      return DIR_LEFT;
    }

};

class ActionRotateRight : public Action{
  public:
      ActionRotateRight(MeDCMotor *motorL, MeDCMotor *motorR)
    : Action(motorL, motorR) { 
      Serial.println("Initializing ActionRotateRight");
      };

    void perform(State *state){
      m_motorL->run(-state->moveSpeed());
      m_motorR->run(-state->moveSpeed());
      delay(random(ACTIONTIME));
    }

    void updatePdf(State *state){
      if (state->previousAction() && state->previousAction()->direction() == DIR_LEFT){
        m_pdf = 1;
      } else {
        m_pdf = remap(state->centerDepth(), 50, 0, 5, 100) + remap(state->leftDepth(), 50, 0, 5, 30);
      }
      Serial.println("Right pdf: ");
      Serial.println(m_pdf);
    }

    short direction(){
      return DIR_RIGHT;
    }
};

#endif
