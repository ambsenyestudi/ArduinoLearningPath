
const int INITIALINTERVAL = 500;
int interval = 0;
int timer = 0;
//This is an example of how to avoid using delay()
void setup()
{
	//Use default led
	pinMode(LED_BUILTIN, OUTPUT);
	interval = INITIALINTERVAL;
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
			interval = INITIALINTERVAL;
		}
		else
		{
			//spends half of lit time
			digitalWrite(LED_BUILTIN, LOW);
			interval = INITIALINTERVAL/2;
		}
		//Now timer is updated at this very time
		timer = millis();
	}

}
