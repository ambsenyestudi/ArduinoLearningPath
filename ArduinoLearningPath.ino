
int interval = 300;
int timer = 0;
//This is an example of how to avoid using delay()
void setup()
{
	//Use default led
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
	//millis() returns ellapsed time in millisecons
	int currTime = millis() - timer;
	if (currTime > interval)
	{
		//digitalRead Gets if the pin is on or of
		if (digitalRead(LED_BUILTIN) == LOW)
		{
			digitalWrite(LED_BUILTIN, HIGH);
		}
		else
		{
			digitalWrite(LED_BUILTIN, LOW);
		}
		//Now timer is updated at this very time
		timer = millis();
	}

}
