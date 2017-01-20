#include "Arduino.h"
#include "Button.h"

Button::Button(int pin, int IOMode)
{
	pinMode(pin, IOMode);
	_pin = pin;
	_state = BUTTON_STATE::READY;
}
void Button::updateState()
{
	int newval = digitalRead(_pin);
}

void Button::storeNewState(int newValue)
{
	//To do generalize so button can work on pullup mode or on input mode
	switch (_state)
	{
		case BUTTON_STATE::READY:
			if (newValue == 0)
			{
				_state = BUTTON_STATE::PUSHED;
			}
			break;
		case BUTTON_STATE::PUSHED:
			_state = BUTTON_STATE::DOWN;
			break;
		case BUTTON_STATE::DOWN:
			if (newValue == 1)
			{
				_state = BUTTON_STATE::DOWN;
			}
			break;
		case BUTTON_STATE::RELEASED:
			_state = BUTTON_STATE::READY;
			break;
		default:
			break;
	}
}
//Getters
BUTTON_STATE Button::getState()
{
	return _state;
}

