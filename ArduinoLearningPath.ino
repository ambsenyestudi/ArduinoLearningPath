//type definition
#define BUTTON 5
typedef enum
{
	READY, PUSHED, RELEASED
}BUTTON_STATE;
//fields
BUTTON_STATE myButtonState = READY;
void setup()
{
	//Use default led
	pinMode(LED_BUILTIN, OUTPUT);
	//Use dthis this pin for button
	pinMode(BUTTON, INPUT_PULLUP);
	//SetUp Seriall port at 9600 bitrate
	Serial.begin(9600);
}

void loop()
{
	int btn1val = digitalRead(BUTTON);
	//button state change
	switch (myButtonState)
	{
		case READY:
			if (btn1val == HIGH)
			{
				myButtonState = PUSHED;
			}
			break;
		case PUSHED:
			if (btn1val == LOW)
			{
				myButtonState = RELEASED;
			}
			break;
		case RELEASED:
			myButtonState = READY;
			Serial.println("Button Released ");
			break;
		default:
		break;
	}
	//button pushed 
	if (btn1val == 1)
	{
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else
	{
		digitalWrite(LED_BUILTIN, LOW);
	}
	
}
