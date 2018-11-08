#include "Motor.h"
#include "utility.h"
#include "Action.h"
#include "Brain.h"
#include "State.h"

#define trigPinCenter 51
#define echoPinCenter 50
#define trigPinLeft 49
#define echoPinLeft 48
#define trigPinRight 53
#define echoPinRight 52

#define MOTOR_A 0
#define MOTOR_B 1

State *state;
Brain *brain;

void setup() {
  Serial.begin(9600);

  TrKjMotor *motorL = new TrKjMotor(MOTOR_A);
  TrKjMotor *motorR = new TrKjMotor(MOTOR_B);

  brain = new Brain(motorL, motorR);

  state = new State(new TrKjUltrasonicSensor(trigPinCenter, echoPinCenter),
                    new TrKjUltrasonicSensor(trigPinLeft, echoPinLeft),
                    new TrKjUltrasonicSensor(trigPinRight, echoPinRight));
}

void loop() {
  Serial.println("New loop iter");

  Serial.println("updating state");
  state->update();
  Serial.println("picking action");
  state->setNextAction(brain->pickAction(state));
  Serial.println("performing action");
  state->nextAction()->perform(state);
  Serial.println("Action performed");
  state->setPreviousAction(state->nextAction());
}
