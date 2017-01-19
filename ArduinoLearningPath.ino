//type definition
#define BUTTON 5
typedef enum
{
	READY, PUSHED, RELEASED
}BUTTON_STATE;
typedef enum
{
	WELCOMING, SAMPLING, PLAYING, RESET
}APPLICATION_STATE;
//fields
BUTTON_STATE myButtonState = READY;
APPLICATION_STATE myAppState = WELCOMING;
const  int nPuhses = 10;
int lastUpdate = 0;
//array of String 
String locutions[]={
	"Welcome to our button tracking simulator.",
	"We will take a number of samples.",
	"Please push your button ", 
	" times"
};
void setup()
{
	//Use default led
	pinMode(LED_BUILTIN, OUTPUT);
	//Use dthis this pin for button
	//Since we are using a protoboard button now and pullup using the internal arduino resistors, the values excange
	pinMode(BUTTON, INPUT_PULLUP);
	//SetUp Seriall port at 9600 bitrate
	Serial.begin(9600);
}

void loop()
{
	//Now down is 1 and up is 0
	int btn1val = digitalRead(BUTTON);
	//button state change
	switch (myButtonState)
	{
		case READY:
			if (btn1val == 0)
			{
				myButtonState = PUSHED;
			}
			break;
		case PUSHED:
			if (btn1val == 1)
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
	switch (myAppState)
	{
		case WELCOMING:
			Serial.println(locutions[0]);
			Serial.println(locutions[1]);
			Serial.print(locutions[2]);
			Serial.print(nPuhses);
			Serial.println(locutions[3]);
			myAppState = SAMPLING;
			//on state change store time
			lastUpdate = millis();
			break;
		case SAMPLING:
			break;
		case PLAYING:
			break;
		case RESET:
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
