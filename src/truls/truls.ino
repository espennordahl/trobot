#include <MeMCore.h>

#include "utility.h"
#include "Action.h"
#include "Brain.h"
#include "State.h"

MeRGBLed rgb(0,16);
MeBuzzer buzzer;
MeIR ir;
#define sensorPortCenter PORT_4
#define trigPinLeft A2
#define echoPinLeft A3
#define trigPinRight 9
#define echoPinRight 10

State *state;
Brain *brain;

void setup() {
  // Pin stuff TODO: wtf is half this stuff...?
  pinMode(13,OUTPUT);
  pinMode(7,INPUT);
  digitalWrite(13,HIGH);
  delay(300);
  digitalWrite(13,LOW);
  rgb.setpin(13);
  ir.begin(); 
  Serial.begin(115200);

  MeDCMotor *motorL = new MeDCMotor(M1);
  MeDCMotor *motorR = new MeDCMotor(M2);

  brain = new Brain(motorL, motorR);

  state = new State(new TrMeUltrasonicSensor(sensorPortCenter), 
  					new TrKjUltrasonicSensor(trigPinLeft, echoPinLeft),
  					new TrKjUltrasonicSensor(trigPinLeft, echoPinLeft));

  // Blink and play sounds to show we're alive
  rgb.setColor(0,0,0);
  rgb.show();
  rgb.setColor(10, 0, 0);
  rgb.show();
  buzzer.tone(350, 300); 
  delay(300);
  rgb.setColor(0, 10, 0);
  rgb.show();
  buzzer.tone(294, 300);
  delay(300);
  rgb.setColor(0, 0, 10);
  rgb.show();
  buzzer.tone(350, 300);
  delay(300);
  rgb.setColor(10,10,10);
  rgb.show();
  buzzer.noTone();
}

void readIR(){
      uint32_t value = ir.value;
    switch (value >> 16 & 0xff)
    {
      case IR_BUTTON_3:
        rgb.setColor(10,0,0);
        break;
      case IR_BUTTON_2:
        rgb.setColor(0,10,0);
        break;
      case IR_BUTTON_1:
        rgb.setColor(0,0,10);
        break;
      case IR_BUTTON_PLUS:
	  	state->speedUp();
        break;
      case IR_BUTTON_MINUS:
	  	state->slowDown();
        break;
    }
}

void loop() {
  Serial.println("New loop iter");
  if (ir.decode())
  {
    Serial.println("reading IR");
    readIR();
  }
  //delay(200); // not sure why I need this, but ir sensor doesn't seem to like reading too frequently

  Serial.println("updating state");
  state->update();
  Serial.println("picking action");
  state->setNextAction(brain->pickAction(state));
  Serial.println("performing action");
  state->nextAction()->perform(state);
  Serial.println("Action performed");
  state->setPreviousAction(state->nextAction());
}
