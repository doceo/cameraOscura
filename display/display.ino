#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
void setup() {
 lcd.init();
 lcd.backlight();
 delay(250);
 lcd.noBacklight();
 delay(1000);
 lcd.backlight();
 delay(1000);
}
void loop() {
 lcd.setCursor(0, 0);
 lcd.print("Anita e' una monella");
 lcd.setCursor(0, 1);
 lcd.print(millis() / 1000);
 delay(100);
}