const int sense_pin = 6;

char sensed_high_once = false;
char should_shutdown = false;

char power_state_set_lost_time = true;
unsigned long time_power_lost = 0;

// This is the time the sense pin needs to be low before it initiates shutdown (in milliseconds)
const unsigned int time_before_shutdown = 5000;

void setup()
{

	Serial.begin(57600);
	pinMode(sense_pin, INPUT);
}

void loop()
{
	if(!sensed_high_once){
		sensed_high_once = digitalRead(sense_pin);
	}else{
		if(digitalRead(sense_pin) == LOW){
			if(power_state_set_lost_time){
				time_power_lost = millis();
				power_state_set_lost_time = false;
			}
			
			long difference = (long)(millis() - time_power_lost);
			
			if(difference >= time_before_shutdown){
				should_shutdown = true;
			}
		}else{
			should_shutdown = false;
			power_state_set_lost_time = true;
		}
	}
	
	Serial.print("Shutdown?: ");
	Serial.println(should_shutdown ? "True" : "False");
	
	delay(500);

}
