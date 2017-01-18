int btn1 = 5;
void setup()
{
	//Use default led
	pinMode(LED_BUILTIN, OUTPUT);
	//Use dthis this pin for button
	pinMode(btn1, INPUT_PULLUP);
	//SetUp Seriall port at 9600 bitrate
	Serial.begin(9600);
}

void loop()
{
	int btn1val = digitalRead(btn1);
	//button pushed 
	if (btn1val == 1)
	{
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else
	{
		digitalWrite(LED_BUILTIN, LOW);
	}
	Serial.print("Button state ");
	Serial.println(btn1val);
}
