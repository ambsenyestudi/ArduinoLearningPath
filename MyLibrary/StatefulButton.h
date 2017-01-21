#pragma once
#ifndef StatefulButton_h
#define StatefulButton_h

#include "Arduino.h"
enum class BUTTON_STATE {
	ST_READY, ST_PUSHED, ST_DOWN, ST_RELEASED
};

class StatefulButton
{
public:
	StatefulButton(int pin, int IOMode);
	void updateState();
	BUTTON_STATE getState();
	int getLastValue();
private:
	int _pin;
	int _lastValue;
	BUTTON_STATE _state;
	void storeNewState(int newValue);
};
#endif
