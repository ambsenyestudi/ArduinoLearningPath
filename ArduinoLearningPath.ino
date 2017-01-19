/*
Now code has becomed awfully long and we have some problems of sync with serial output
It's time for funtions this is an abstraction that lets you isolate code and repete it multiple times
*/

//type definition
#define BUTTON 5
//we need buton pushed and button released so we will implement a inbetween state
typedef enum
{
	READY, PUSHED, DOWN, RELEASED
}BUTTON_STATE;
typedef enum
{
	WELCOMING, SAMPLING, STARTING_PLAY, PLAYING, RESET
}APPLICATION_STATE;
//constants
const int totalPushCount = 10;
const int pushIntevalLenght = totalPushCount * 2;
//fields
BUTTON_STATE myButtonState = READY;
APPLICATION_STATE myAppState = WELCOMING;
int locutionCounter = 0;
//locutions
String welcomingLocutions[]={
	"Welcome to our button tracking simulator.",
	"We will take a number of samples.",
	"Please push your button " + String(totalPushCount) + " times.",
	"Push the button whenever you are ready to start."
};
String samplingLocutions[] = {
	"Well done only ",
	" remaining"
};
String startPlayingLocution = "Now we have collected all needed that and we'll start playing the secuence";
String resetLocution = "Please if at any point you would like to reestart the program, simply push the button";
String recordingLocution = "Good button push recording has started";
int pushedSoFar = 0;
unsigned long current_time = 0;
int pushIntevalCount = 0;
unsigned long pushIntervals[pushIntevalLenght];
bool isLoop = true;
bool isButtonStateVerbose = false;
// if you declare your functions here the you can consume theme with no order problem through out the code
/*function declarataion*/
void welcome();
void evaluateButtonState(int buttonVal);
void applicaitonFlow();
void startPlaying();
void playSequence();
void sampling();
void recordInterval();
void resetCounters();
void resetApplication();
void toggleLed();
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
	//first check input
	evaluateButtonState(btn1val);
	//then execute aplication flow
	applicaitonFlow();
	
	
}
void applicaitonFlow()
{
	switch (myAppState)
	{
	case WELCOMING:
		welcome();
		break;
	case SAMPLING:
		sampling();
		break;
	case STARTING_PLAY:
		startPlaying();
		break;
	case PLAYING:
		playSequence();
		break;
	case RESET:
		resetApplication();
		break;
	default:
		break;
	}
}
void evaluateButtonState(int buttonVal)
{
	//button state change
	switch (myButtonState)
	{
	case READY:
		if (buttonVal == 0)
		{
			myButtonState = PUSHED;
			if (isButtonStateVerbose)
			{
				Serial.println("Button Pushed ");
			}
		}
		break;
	case PUSHED:
		myButtonState = DOWN;
		break;
	case DOWN:
		if (buttonVal == 1)
		{
			myButtonState = RELEASED;
		}
		break;
	case RELEASED:
		myButtonState = READY;
		if (isButtonStateVerbose)
		{
			Serial.println("Button Released ");
		}
		break;
	default:
		break;
	}
}
void playSequence()
{
	if (myButtonState == RELEASED)
	{
		myAppState = RESET;
	}
	//resets counter to start loop over
	if (isLoop && !(pushIntevalCount < pushIntevalLenght))
	{
		pushIntevalCount = 0;
	}

	if ((millis() - current_time) > pushIntervals[pushIntevalCount])
	{
		toggleLed();
		pushIntevalCount++;
		current_time = millis();
	}
}
void resetApplication()
{
	Serial.println("");
	Serial.println("Reseting application ...");
	Serial.println("-----------------------------------");
	Serial.println("");
	myAppState = WELCOMING;
	resetCounters();
}
void toggleLed()
{
	bool previousState = digitalRead(LED_BUILTIN);
	digitalWrite(LED_BUILTIN, !previousState);
}
void sampling()
{
	if (pushedSoFar <=totalPushCount)
	{
		if (myButtonState == PUSHED)
		{
			digitalWrite(LED_BUILTIN, HIGH);
			recordInterval();
		}
		if (myButtonState == RELEASED)
		{
			
			Serial.print(samplingLocutions[0]);
			Serial.print(totalPushCount-pushedSoFar);
			Serial.println(samplingLocutions[1]);
			recordInterval();
			pushedSoFar++;
			digitalWrite(LED_BUILTIN, LOW);
		}
	}
	else
	{
		myAppState = STARTING_PLAY;
	}
}
void recordInterval()
{
	if (pushIntevalCount < pushIntevalLenght)
	{
		pushIntervals[pushIntevalCount] = millis() - current_time;
		pushIntevalCount++;
	}
	current_time = millis();
}
void startPlaying()
{
	//Just tu ensure results are full
	Serial.println("Results are:");
	Serial.print("[");
	for (int i = 0; i < pushIntevalLenght; i++)
	{
		Serial.print(pushIntervals[i]);
		if (i < pushIntevalLenght - 1)
		{
			Serial.print(",");
		}
	}
	Serial.println("]");
	Serial.println(startPlayingLocution);
	resetCounters();
	Serial.println("");
	Serial.println("");
	Serial.println(resetLocution);
	myAppState = PLAYING;
}
void resetCounters()
{
	pushIntevalCount = 0;
	locutionCounter = 0;
	pushedSoFar = 0;
	current_time = millis();
}
void welcome()
{
	//this is for now the number of locutions in the array
	//if (locutionCounter < sizeof(welcomingLocutions))
	if (locutionCounter < 4)
	{
		Serial.println(welcomingLocutions[locutionCounter]);
		locutionCounter++;
	}
	else if (myButtonState == RELEASED) 
	{
		current_time = millis();
		myAppState = SAMPLING;
		Serial.println("");
		Serial.println(recordingLocution);
	}

}

