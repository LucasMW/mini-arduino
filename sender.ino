#include <IRremote.h>

IRsend irsend;

#define BTON          6
#define BTVOLUP       7
#define BTVOLDOWN     8
#define BT4           9
#define BTCHANGE      10
#define LED           13
#define IRS           12
#define MIN_INTERVAL  250
#define TOTAL_BUTTONS 4
#define TOTAL_PROFILES 2

typedef struct{
  long int code;
  int signaltype;
  int numbits;
} botao;

botao botoes[3][4];

//sky, lg, SONY
//long int signals[][4] = {{0x61F458A7, 0x61F448B7, 0x61F4D827, 0x61F46897}, {0x20DF10EF, 0x20DF40BF, 0x20DFC03F, 0x20DF28D7}, {0xA90, 0x490, 0xC90, 0xC10}};
//{0xF4BA2988, 0x68733A46, 0x83B19366, 0xF5999288}
long int buttons[] = {BTON, BTVOLUP, BTVOLDOWN, BT4};
int profile = 0;

boolean lightState = false;
unsigned long last = millis();

void setup() {
  pinMode(BTON, INPUT);
  pinMode(BTVOLUP, INPUT);
  pinMode(BTVOLDOWN, INPUT);
  pinMode(BT4, INPUT);
  pinMode(BTCHANGE, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED, lightState);

  //botões da sky
  botoes[0][0].code = 0x61F458A7;
  botoes[0][0].signaltype = 1; //NEC
  botoes[0][0].numbits = 32;
  
  botoes[0][1].code = 0x61F448B7;
  botoes[0][1].signaltype = 1; //NEC
  botoes[0][1].numbits = 32;
  
  botoes[0][2].code = 0x61F4D827;
  botoes[0][2].signaltype = 1; //NEC
  botoes[0][2].numbits = 32;
  
  botoes[0][3].code = 0x61F46897;
  botoes[0][3].signaltype = 1; //NEC
  botoes[0][3].numbits = 32;

  //botões da sony
  botoes[1][0].code = 0xA90;
  botoes[1][0].signaltype = 2; //SONY
  botoes[1][0].numbits = 12;
  
  botoes[1][1].code = 0x490;
  botoes[1][1].signaltype = 2; //SONY
  botoes[1][1].numbits = 12;
  
  botoes[1][2].code = 0xC90;
  botoes[1][2].signaltype = 2; //SONY
  botoes[1][2].numbits = 12;
  
  botoes[1][3].code = 0xC10;
  botoes[1][3].signaltype = 2; //SONY
  botoes[1][3].numbits = 12;

  //botões da LG
  botoes[2][0].code = 0x20DF10EF;
  botoes[2][0].signaltype = 1; //NEC
  botoes[2][0].numbits = 32;
  
  botoes[2][1].code = 0x20DF40BF;
  botoes[2][1].signaltype = 1; //NEC
  botoes[2][1].numbits = 32;
 
  botoes[2][2].code = 0x20DFC03F;
  botoes[2][2].signaltype = 1; //NEC
  botoes[2][2].numbits = 32;
  
  botoes[2][3].code = 0x20DF28D7;
  botoes[2][3].signaltype = 1; //NEC
  botoes[2][3].numbits = 32;
}

void loop() {
  int i;
  for(i = 0; i < TOTAL_BUTTONS; i++){
    int button = digitalRead(buttons[i]);
    if(button == HIGH){
      //has it been 1/4 sec since last message
      if (millis() - last > 250) 
      {
        botao button = botoes[profile][i];
        //toggle the LED
        digitalWrite(LED, 1);
        //Serial.println(signals[profile][i]);
        //irsend.sendNEC(signals[profile][i], 32);
        Serial.println(button.code);
        
        switch(button.signaltype){
          case 1:{
            irsend.sendNEC(button.code, button.numbits);
            break; 
          }
          case 2:{
            irsend.sendSony(button.code, button.numbits);
            break; 
          }
        }
      }
      last = millis();
      //toggle the LED
      digitalWrite(LED, 0);
    } 

    int change = digitalRead(BTCHANGE);
    if(change == HIGH){
      if (millis() - last > 250){
        digitalWrite(LED, 1);
        profile = (profile+1)%TOTAL_PROFILES;
        Serial.print("mudando para perfil ");
        Serial.print(profile);
        Serial.println("");
        last = millis();
        //toggle the LED
        digitalWrite(LED, 0);
      }
    }
  }
}
