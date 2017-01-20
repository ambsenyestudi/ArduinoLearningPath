#pragma once
#ifndef Button_h
#define Button_h

#include "Arduino.h"

enum class BUTTON_STATE {
	READY, PUSHED, DOWN, RELEASED
};

class Button
{
	public:
		Button(int pin, int IOMode);
		void updateState();
		BUTTON_STATE getState();
	private:
		int _pin;
		BUTTON_STATE _state;
		void storeNewState(int newValue);
};
#endif