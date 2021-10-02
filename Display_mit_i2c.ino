
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <HDC100X.h>

/*
Installation:
 GND zu GND
 VCC zu 3,3V
 SDA 
 SCL 
 */

#define I2C_ADDR  0x27
#define BACKLIGHT_PIN     13

// set the LCD address to 0x27 for a 16 chars and 2 line display
// older LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);  

// der Temperatur-Sensor
  HDC100X t(0x43,0xC3);

float tempval = 0.0;
float hydroval = 0.0;


void show () {

  // hole die werte  
  tempval = t.getTemp();
  hydroval = t.getHumi();
  // Print a message to the LCD.
  lcd.setCursor(1,0); //Start at character 4 on line 0
  lcd.print("Temp:");
  lcd.setCursor(1,1);
  lcd.print("Hydro:");
  
  lcd.setCursor(8,0);
  lcd.print(tempval);
  lcd.setCursor(8,1);
  lcd.print(hydroval);  
  
  lcd.setCursor(14,0);
  lcd.print("C");
  lcd.setCursor(14,1);
  lcd.print("%");

  
}

void setup()
{
  Serial.begin(9600);
  // initialize the lcd
  Serial.println("init .");  
  lcd.begin(20,4); 
  Serial.println("init ..");
  t.begin (HDC100X_TEMP_HUMI, HDC100X_11BIT, HDC100X_8BIT, DISABLE);
  Serial.println("init ...");
  // schalte die blöde LED auf dem Board aus
  pinMode ( BACKLIGHT_PIN, OUTPUT );
  digitalWrite ( BACKLIGHT_PIN, LOW );
  Serial.println("init ....");  
  for(int i = 0; i< 3; i++)
    {
      lcd.backlight();
  Serial.println("init .....");        
      delay(250);
      lcd.noBacklight();
  Serial.println("init .....");              
      delay(250);
    }
  lcd.backlight(); // finish with backlight on  
  Serial.println("init ......");              
  show ();
  Serial.println("init .......");              
  delay(1000);
}

void loop()
{
  while (true) {
  show ();
  Serial.println("run .......");
  delay (5000);
  }
}


