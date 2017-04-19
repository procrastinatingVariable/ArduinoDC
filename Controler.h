#ifndef CONTROLER_INCLUDED
#define CONTROLER_INCLUDED

#include <Arduino.h>

class Controler {
	private:
		bool leftButton;
		bool rightButton;
		bool upButton;
		bool downButton;

		int leftButtonPin;
		int rightButtonPin;
		int upButtonPin;
		int downButtonPin;

		static const unsigned long int readDisableTime = 25; // millis

		bool readButtonState (int buttonPin);
		bool validate (bool initialButtonValue, int buttonPin);

	public:
		static const bool BUTTON_PRESSED = HIGH;
		static const bool BUTTON_RELEASED = LOW;

		Controler();
		Controler(int leftButtonPin,
							int rightButtonPin,
							int upButtonPin,
							int downButtonPin);

		bool getRightState();
		bool getLeftState();
		bool getUpState();
		bool getDownState();

		void readButtons();

};

#endif
