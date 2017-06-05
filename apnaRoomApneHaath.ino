// Input pins
#define PIR_DIGITAL_INPUT    7

// Output pins
#define FAN_SWITCH_OUTPUT    5
#define LIGHT_SWITCH_OUTPUT  3

// Status LED
#define HEART_BEAT          13

// Power pins (5V/3.3V/GND)
#define JDVCC_5V_POWER      11
#define RELAY_5V_POWER       4

// Time it takes before it sleeps
#define TIME_DURATION     3000

// Global Variables
long int time_counter = 0;

void setup() {
  // Serial init
  Serial.begin(9600);

  // Input pins init
  pinMode(PIR_DIGITAL_INPUT, INPUT);
  
  // Output pins init
  pinMode(FAN_SWITCH_OUTPUT, OUTPUT);
  pinMode(LIGHT_SWITCH_OUTPUT, OUTPUT);

  // Power supply Init
  pinMode(RELAY_5V_POWER, OUTPUT);
  pinMode(JDVCC_5V_POWER, OUTPUT);
  pinMode(HEART_BEAT, OUTPUT);
  
  // Default pin settings
  digitalWrite(JDVCC_5V_POWER, HIGH);
  digitalWrite(RELAY_5V_POWER, HIGH);
}

/*
 * Testing use only
 * Serial.println(insideCount);
*/

/*
 * This function turns ON/OFF the digital 
 * switch of Fan and Light.
 * INPUT: bool response
*/
void fan_light_switch(bool response)
{
  digitalWrite(LIGHT_SWITCH_OUTPUT, response);
  digitalWrite(FAN_SWITCH_OUTPUT, response);
  digitalWrite(HEART_BEAT, response);
}

void loop() {
  int pir_sensor_read = digitalRead(PIR_DIGITAL_INPUT);

  // Turn on the system
  if(pir_sensor_read) {
    time_counter = 0;
    fan_light_switch(HIGH);
  }
  else
    time_counter++;

  // Turn off the system
  if(time_counter >= TIME_DURATION) 
  {
    time_counter = 0;
    fan_light_switch(LOW);
  }
  // Delay of .1 sec
  delay(100);  
}

