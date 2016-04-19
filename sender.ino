#include <IRremote.h>

IRsend irsend;

#define BTON          6
#define BTVOLUP       7
#define BTVOLDOWN     8
#define BT4           9
#define LED           13
#define IRS           12
#define MIN_INTERVAL  250
#define TOTAL_BUTTONS 4

long int signals[] = {0x61F458A7, 0x61F448B7, 0x61F4D827, 0x61F46897};
long int buttons[] = {BTON, BTVOLUP, BTVOLDOWN, BT4};

boolean lightState = false;
unsigned long last = millis();

void setup() {
  pinMode(BTON, INPUT);
  pinMode(BTVOLUP, INPUT);
  pinMode(BTVOLDOWN, INPUT);
  pinMode(BT4, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED, lightState);
}

void loop() {
  int i;
  for(i = 0; i < TOTAL_BUTTONS; i++){
    int button = digitalRead(buttons[i]);
    if(button == HIGH){
      //has it been 1/4 sec since last message
      if (millis() - last > 250) 
      {
        //toggle the LED
        digitalWrite(LED, 1);
        Serial.println(signals[i]);
        irsend.sendNEC(signals[i], 32);
      }
      last = millis();
      //toggle the LED
      digitalWrite(LED, 0);
    } 
  }
}
