#include "thingProperties.h"

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
  pinMode(13,OUTPUT);
  pinMode(9, OUTPUT);
  // Defined in thingProperties.h
  initProperties();
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
   setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}
void loop() {
  ArduinoCloud.update();
}
/*
  Since Led is READ_WRITE variable, onLedChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLEDLIGHTChange() {
  if (lED_LIGHT) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}


/*
  Since Button is READ_WRITE variable, onButtonChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onButtonChange()  {
    if (button) {
    lED_LIGHT = !lED_LIGHT;
    button = false;  // reset button
}
}
// BUZZER
void onBuzzerOnChange() {
  if (buzzerOn) {
    tone(9, 1000);   // 1 kHz beep
  } else {
    noTone(9);       // silence
  }
}


