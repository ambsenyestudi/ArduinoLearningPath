#include "LEDManager.h"
#include "Arduino.h"


LEDManager::LEDManager(int pin)
{
	_pin = pin;
	pinMode(pin, OUTPUT);
}


void LEDManager::toggle()
{
	digitalWrite(_pin, !digitalRead(_pin));
}

void LEDManager::On()
{
	digitalWrite(_pin, HIGH);
}

void LEDManager::Off()
{
	digitalWrite(_pin, LOW);
}
