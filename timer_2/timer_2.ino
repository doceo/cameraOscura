#include <Keypad.h>
#include <ctype.h>
#include <time.h>

#include <Wire.h>

#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 10
#define DIO 11

const uint8_t SEG_DONE[] = {
	SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_C | SEG_E | SEG_G,                           // n
	SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
	};

TM1637Display display(CLK, DIO);

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte rowPins[ROWS] =  {9, 8, 7, 6};//connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int tempo = 0;
int pinLuce = 12;
int memTempo = 0;
bool luceLCD = 0;


void avvioTimer(int temp){
    display.clear();
    display.setBrightness(2, true);  // Turn off

    digitalWrite(pinLuce, LOW);
    
    for(int i=1; i<=temp; i++){
      delay(1000);      
      display.showNumberDec(i, false); // Expect: ___1
    
    }

  display.clear();
  display.setBrightness(4, true);  // Turn off
  
  digitalWrite(pinLuce, HIGH);

}

void setup(){
//    Serial.begin(9600);
    pinMode(pinLuce, OUTPUT);
    digitalWrite(pinLuce, HIGH);

    display.setBrightness(4, true);  // Turn off

    display.clear();


}

void loop(){

    char key = keypad.getKey();

    if (key){
 //     Serial.println(key);
      if(key == '*') {

        memTempo = tempo;

        avvioTimer(tempo);
        
        tempo=0;

      }else if (key == 'A'){
        
        avvioTimer(memTempo);
        
        tempo=0;

      }else if (key == 'C'){
        
        tempo=0;
        display.clear(); // Expect: ___1

      }
      
      else{

        tempo = tempo * 10;
        //Serial.print("moltiplico per 10: ");
        //Serial.println(tempo);

        tempo = tempo + int(key)-48;
        //Serial.print("tempo provvisorio: ");
        //Serial.println(tempo);
        display.showNumberDec(tempo, false); // Expect: ___1

      }

    }

  }
