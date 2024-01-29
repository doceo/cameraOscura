/* @file EventSerialKeypad.pde
 || @version 1.0
 || @author Alexander Brevig
 || @contact alexanderbrevig@gmail.com
 ||
 || @description
 || | Demonstrates using the KeypadEvent.
 || #
 */
#include <Keypad.h>
#include <ctype.h>
#include <time.h>

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

void setup(){
    Serial.begin(9600);
    

}

void loop(){
    char key = keypad.getKey();

    if (key){

      if(isalnum(key)){
        //Serial.print("key principale: ");
        //Serial.println(key);
        //Serial.println(int(key)-48);
        
        //Serial.print("tempo: ");
        //Serial.println(tempo);

        tempo = tempo * 10;
        //Serial.print("moltiplico per 10: ");
        //Serial.println(tempo);
        
        tempo = tempo + int(key)-48;
        //Serial.print("tempo provvisorio: ");
        //Serial.println(tempo);
    

      }else{
        for(int i=0; i<tempo; i++){
          delay(1000);
          Serial.println(i);
        }
        
        tempo=0;

      }
       
      }

      
    }
