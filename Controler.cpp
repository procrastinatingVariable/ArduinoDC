#include "Controler.h"

Controler::Controler() {
	leftButton = BUTTON_RELEASED;
	rightButton = BUTTON_RELEASED;
  upButton = BUTTON_RELEASED;
	downButton = BUTTON_RELEASED;
	actionButton = BUTTON_RELEASED;
}

Controler::Controler (int leftButtonPin, int rightButtonPin,
					            int upButtonPin, int downButtonPin,
											int actionButtonPin) : Controler(){

	this->leftButtonPin = leftButtonPin;
	this->rightButtonPin = rightButtonPin;
	this->upButtonPin = upButtonPin;
	this->downButtonPin = downButtonPin;
	this->actionButtonPin = actionButtonPin;

	pinMode(leftButtonPin, INPUT_PULLUP);
	pinMode(rightButtonPin, INPUT_PULLUP);
	pinMode(upButtonPin, INPUT_PULLUP);
	pinMode(downButtonPin, INPUT_PULLUP);
	pinMode(actionButtonPin, INPUT_PULLUP);
}


bool Controler::getLeftState() {
	return leftButton;
}

bool Controler::getRightState() {
	return rightButton;
}

bool Controler::getUpState() {
	return upButton;
}

bool Controler::getDownState() {
	return downButton;
}

bool Controler::getActionState() {
	return actionButton;
}

void Controler::readButtons() {
		bool leftReadValue = readButtonState(leftButtonPin);
		bool rightReadValue = readButtonState(rightButtonPin);
		bool upReadValue = readButtonState(upButtonPin);
		bool downReadValue = readButtonState(downButtonPin);
		bool actionReadValue = readButtonState(actionButtonPin);

		delay(15);
		
		if (validate(leftReadValue, leftButtonPin)) {
			leftButton = leftReadValue;
		}

		if (validate(rightReadValue, rightButtonPin)) {
			rightButton = rightReadValue;
		}

		if (validate(upReadValue, upButtonPin)) {
			upButton = upReadValue;
		}
		
		if (validate(downReadValue, downButtonPin)) {
			downButton = downReadValue;
		}

		if (validate(actionReadValue, actionButtonPin)) {
			actionButton = actionReadValue;
		}
}


bool Controler::readButtonState (int buttonPin) {
    bool readValue = !digitalRead(buttonPin);
    return readValue;
}

bool Controler::validate (bool initialButtonValue, int buttonPin) {
    int newValue = readButtonState(buttonPin);
    return newValue == initialButtonValue;
}
