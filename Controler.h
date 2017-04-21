#ifndef CONTROLER_INCLUDED
#define CONTROLER_INCLUDED

#include <Arduino.h>

class Controler {
	private:
		static const unsigned long int readDisableTime = 25; // millis

		bool leftButton;
		bool rightButton;
		bool upButton;
		bool downButton;
		bool actionButton;

		int leftButtonPin;
		int rightButtonPin;
		int upButtonPin;
		int downButtonPin;
		int actionButtonPin;


		bool readButtonState (int buttonPin);
		// performs a read from the given buttonPin and checks if the initial
		// value given matches with the new read
		bool validate (bool initialButtonValue, int buttonPin);

	public:
		static const bool BUTTON_PRESSED = HIGH;
		static const bool BUTTON_RELEASED = LOW;

		Controler();
		Controler(int leftButtonPin,
							int rightButtonPin,
							int upButtonPin,
							int downButtonPin,
							int actionButtonPin);

		bool getRightState();
		bool getLeftState();
		bool getUpState();
		bool getDownState();
		bool getActionState();

		void readButtons();

};

#endif
