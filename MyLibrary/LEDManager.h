#pragma once

#ifndef LEDManager_h
#define LEDManager_h
#include "Arduino.h"
class LEDManager
{
public:
	LEDManager(int pin);
	void toggle();
	void On();
	void Off();
private:
	int _pin;
};
#endif
