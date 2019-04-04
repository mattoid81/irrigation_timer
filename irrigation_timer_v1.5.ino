/* Configuration */
#define SOLENOID_PIN 1 // solenoid is connected to digital pin 1
#define WATER_ON_MINUTES 10 // input the number of minutes to turn the solenoid on
#define WATER_OFF_HOURS 48 // input the number of hours for the cycle time

/* Millisecond conversion */
#define WATER_ON_MILLIS (60000 * WATER_ON_MINUTES)
#define WATER_OFF_MILLIS (3600000 * WATER_OFF_HOURS - WATER_ON_MILLIS)

/* Type Definition */
typedef unsigned long time_t; //

/* Declaration to check if SOLENOID_PIN is currently on */
bool watering = false; // Are we currently watering or not? Sets value to off by default
time_t lastEvent; // When did we last turn off or on? Sets value to zero by default

void setup() {                          // Setup code (runs once only)
  digitalWrite(SOLENOID_PIN, LOW) // Ensure the solenoid is off before engaging the output
  pinMode(SOLENOID_PIN, OUTPUT); // sets the pin to output
}

void loop() {                         // Loop code (runs continuously)
  time_t now = millis(); // a unique identifier for this moment in time
  time_t elapsed = now - lastEvent; // how much time has elapsed since the last event

  if (watering && elapsed > WATER_ON_MILLIS) { // If the water is on and has been on for longer than WATER_ON_MILLIS
    watering = false; // toggle the watering state
    lastEvent = now; // record when the water was switched off
    digitalWrite(SOLENOID_PIN, LOW); // turn off the solenoid
  }

  else if (!watering && elapsed > WATER_OFF_MILLIS) {// If the water is off and has been off for longer than WATER_OFF_MILLIS
    watering = true; // toggle the watering state
    lastEvent = now; // record when the water was switched on
    digitalWrite(SOLENOID_PIN, HIGH); // turn on the solenoid
  }
}
