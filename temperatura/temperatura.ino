
// librerie per il funzionamento del sensore
#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// библиотека для работы с датчиками серии DHT
#include <TroykaDHT.h>
// создаём объект класса DHT
// передаём номер пина к которому подключён датчик и тип датчика
// типы сенсоров: DHT11, DHT21, DHT22
DHT dht(4, DHT11);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);


#define ONE_WIRE_BUS 2 // Pin Arduino a cui colleghiamo il pin DQ del sensore
const int pinLed = LED_BUILTIN; // Utilizzo del LED su scheda 

int resistenza = 12;
const int soglia = 21; // Accende il LED su scheda se si superano i 25°C

OneWire oneWire(ONE_WIRE_BUS); // Imposta la connessione OneWire

DallasTemperature sensore(&oneWire); // Dichiarazione dell'oggetto sensore

void setup(void)
{
  Serial.begin(9600);       // Inizializzazione della serial monitor
  sensore.begin();          // Inizializzazione del sensore
  
  pinMode(pinLed, OUTPUT);  // pinLed definito come OUTPUT
  pinMode(resistenza, OUTPUT);
  digitalWrite(resistenza, HIGH);

  dht.begin();

  delay(1000);
  lcd.init();
  lcd.backlight();
  delay(250);
  lcd.noBacklight();
  delay(1000);
  lcd.backlight();
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Temp. Aria: ");
  lcd.setCursor(0, 1);
  lcd.print("Umidita': ");
  lcd.setCursor(0, 2);
  lcd.print("Temp. Liquido: ");

}

void loop()
{
  sensore.requestTemperatures(); // richiesta lettura temperatura
  dht.read();

switch(dht.getState()) {
    // всё OK
    case DHT_OK:
      // выводим показания влажности и температуры
      float temperature = dht.getTemperatureC(); 
      lcd.setCursor(12, 0);
      lcd.print(temperature);

      Serial.print(temperature);

      float humidity = dht.getHumidity(); 
      lcd.setCursor(10, 1);
      lcd.print(humidity);

      Serial.print(humidity);

      // Restituzione della temperatura letta
      // in gradi Celsius

      break;
    // ошибка контрольной суммы
    case DHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    // превышение времени ожидания
    case DHT_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    // данных нет, датчик не реагирует или отсутствует
    case DHT_ERROR_NO_REPLY:
      Serial.println("Sensor not connected");
      break;
  }


  // temperatura in Celsius
  float celsius = sensore.getTempCByIndex(0);
  lcd.setCursor(15, 2);
  lcd.print(celsius);

 if (celsius<soglia){
    digitalWrite(resistenza, LOW);

 }else{
    digitalWrite(resistenza, HIGH);

 }

  // stampe delle temperature ogni secondo
  delay(1000);

}