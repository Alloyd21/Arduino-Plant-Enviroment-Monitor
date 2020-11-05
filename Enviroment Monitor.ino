#include <Wire.h> //4 Wire Driver for display
#include <LiquidCrystal_I2C.h> //LCD Display Library
#include <dht11.h> //Temp Sensor Library
#include <RGBLED.h> //RGB Library
#define DHT11PIN 0 //Binding Sensor to pin 0
int soilsensorPin = A0; //Binding Soil Sensor to pin A0
int soilsensorValue; 
const int LDR = A1; //LDR to pin A1
int LDR_val = 0; 
LiquidCrystal_I2C lcd(0x27, 20, 4);
byte customChar[8] = {0b00000,0b00100,0b01010,0b10001,0b10001,0b10001,0b01110,0b00000};
byte customChar1[8] = {0b00100,0b01010,0b01010,0b01010,0b10001,0b10001,0b10001,0b01110};
byte customChar2[8] = {0b00000,0b10101,0b01110,0b11111,0b11111,0b01110,0b10101,0b00000};
RGBLED tempLED(9,8,7,COMMON_ANODE); //Assigning RGB Pins
RGBLED soilLED(12,11,10,COMMON_ANODE);
RGBLED lightLED(6,5,4,COMMON_ANODE);

dht11 DHT11;

void setup()
{
 lcd.begin(); // initialize the LCD

   
  Serial.begin(9600); // 
 
  lcd.backlight();  // Turn on the blacklight and print a message.
  lcd.createChar(0, customChar);
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
}

void loop()
{
  Serial.println(); //Print Blank Line
  int chk = DHT11.read(DHT11PIN); //Read value from DHT11 Sensor
  //Check and print Values of sensor
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  lcd.setCursor(4,0);
  lcd.print("Bradbury Club");
  
  lcd.setCursor(1,1);
  lcd.print("Sustainable Garden");
  
  lcd.setCursor(0,3);
  lcd.write((uint8_t)0); //Icon
  lcd.setCursor(1,3);
  lcd.print((float)DHT11.humidity, 2);


  Serial.print("Temperature (C): ");
  Serial.println((float)DHT11.temperature - 3.00, 2);
  
  lcd.setCursor(8,3);
  lcd.write((uint8_t)1); //Icon
  lcd.setCursor(9,3);
  lcd.print((float)DHT11.temperature - 3.00, 2);

  
  soilsensorValue = analogRead(soilsensorPin); 
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilsensorValue);

  LDR_val = analogRead(LDR);
  Serial.print("LDR Value is: ");
  Serial.println(LDR_val);
  
  lcd.setCursor(16,3);
  lcd.write((uint8_t)2); //Icon
  lcd.setCursor(17,3);
  lcd.print(LDR_val);
  
if(soilsensorValue < 350.00 )
  {soilLED.writeRGB(0,0,255);} //If sensor less than 350 then turn on blue LED
  else if (soilsensorValue > 351.00 && soilsensorValue < 450.00)
  {soilLED.writeRGB(0,255,0);} //If sensor more than 351 and less than 450 turn on green LED
  else 
  {soilLED.writeRGB(255,0,0);} //Otherwise turn on Red LED

  if(LDR_val < 500.00 )
  {lightLED.writeRGB(0,255,0);}
  else if (LDR_val > 501.00 && LDR_val < 620.00)
  {lightLED.writeRGB(255,0,0);}
  else 
  {lightLED.writeRGB(0,0,255);}

  if(DHT11.temperature < 18.00 )
  {tempLED.writeRGB(0,255,0);}
  else if (DHT11.temperature > 19.00 && DHT11.temperature < 24.00)
  {tempLED.writeRGB(0,0,255);}
  else 
  {tempLED.writeRGB(255,0,0);}
  //Turn on LEDs based on status.

  
 
  delay(2000); //Update every 2 seconds

}
