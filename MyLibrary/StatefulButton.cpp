#include "StatefulButton.h"



StatefulButton::StatefulButton(int pin, int IOMode)
{
	pinMode(pin, IOMode);
	_pin = pin;
	_state = BUTTON_STATE::ST_READY;
}
void StatefulButton::updateState()
{
	int newval = digitalRead(_pin);
	_lastValue = digitalRead(_pin);
	storeNewState(newval);
}
void StatefulButton::storeNewState(int newValue)
{

	switch (_state)
	{
	case BUTTON_STATE::ST_READY:
		if (newValue == 0)
		{
			_state = BUTTON_STATE::ST_PUSHED;
		}
		break;
	case BUTTON_STATE::ST_PUSHED:
		_state = BUTTON_STATE::ST_DOWN;
		break;
	case BUTTON_STATE::ST_DOWN:
		if (newValue == 1)
		{
			_state = BUTTON_STATE::ST_RELEASED;
		}
		break;
	case BUTTON_STATE::ST_RELEASED:
		_state = BUTTON_STATE::ST_READY;
		break;
	default:
		break;
	}
}

int StatefulButton::getLastValue()
{
	return _lastValue;
}

BUTTON_STATE StatefulButton::getState()
{
	return _state;
}