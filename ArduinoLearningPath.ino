#include <Button.h>

//type definition
Button button(5, INPUT_PULLUP);
typedef enum
{
	WELCOMING, SAMPLING, STARTING_PLAY, PLAYING, RESET
}APPLICATION_STATE;
//constants
const int totalPushCount = 10;
const int pushIntevalLenght = totalPushCount * 2;
//fields
APPLICATION_STATE myAppState = WELCOMING;
int locutionCounter = 0;

//locutions
String welcomingLocutions[]={
	"Welcome to our button tracking simulator.",
	"We will take a number of samples.",
	"Please push your button " + String(totalPushCount) + " times.",
	"Push the button whenever you are ready to start."
};
int welcomingLocutionsLength = sizeof(welcomingLocutions)/ sizeof(String);
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
	//SetUp Seriall port at 9600 bitrate
	Serial.begin(9600);
}


void loop()
{
	button.updateState();
	
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

void playSequence()
{
	if (button.getState() == BUTTON_STATE::RELEASED)
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
		if (button.getState() == BUTTON_STATE::PUSHED)
		{
			digitalWrite(LED_BUILTIN, HIGH);
			recordInterval();
		}
		if (button.getState() == BUTTON_STATE::RELEASED)
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
	if (locutionCounter < welcomingLocutionsLength)
	{
		Serial.println(welcomingLocutions[locutionCounter]);
		locutionCounter++;
	}
	else if (button.getState() == BUTTON_STATE::RELEASED)
	{
		current_time = millis();
		myAppState = SAMPLING;
		Serial.println("");
		Serial.println(recordingLocution);
	}

}

