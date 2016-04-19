/*
IR_remote_detector sketch
An IR remote receiver is connected to pin 2.
The LED on pin 13 toggles each time a button on the remote is pressed.
*/
#include <IRremote.h> //adds the library code to the sketch
const int irReceiverPin = 2; //pin the receiver is connected to
const int ledPin = 13; 
IRrecv irrecv(irReceiverPin); //create an IRrecv object
decode_results decodedSignal; //stores results from IR detector
void setup()
{
  pinMode(ledPin, OUTPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
}
boolean lightState = false;
unsigned long last = millis();
// Start the receiver object
//keep track of whether the LED is on
//remember when we last received an IR
void loop()
{

  int result = irrecv.decode(&decodedSignal);
  if (result == true) //this is true if a message has been received
  {
    if (millis() - last > 250) 
    {
      //has it been 1/4 sec since last message
      lightState = !lightState;
      //toggle the LED
      digitalWrite(ledPin, lightState);
      Serial.println(decodedSignal.value);
    }
    last = millis();
    irrecv.resume();
    // watch out for another message
  }
}
