/*

Lab 4 - Analog Input
This code is supposed to link a photoresitor to a lcd screen and print out the time since reset and light value.
I assumed the photoresitor would be somewhat sensitive to light
  Light Values:
    dark - touching touching photoresitor with fingers
    partially dark - almost touching photoresitor with finger
    medium - hovering over photoresitor with finger
    fully lit - nothing
    brightly lit - shining flashlight onto photoresistor
I used the Circuit Basics website to learn about the photoresistor and get starter code.
https://www.circuitbasics.com/how-to-use-photoresistors-to-detect-light-on-an-arduino/

Lab results:                                        touching photo resistor         hovering over photoresistor        nothing         flaslight far away        flashlight close
3 10k ohm resistors in parallel (3333 ohm):               210                               340                          675                 790                         920
2 10k ohm resistors in parallel (5000 ohm):               280                               580                          762                 820                         987
1 10k ohm resistor (10000 ohm):                           374                               727                          871                 916                         1008
2 10k ohm resistors in series (20000 ohm):                473                               832                          937                 954                         1015
1 220 ohm reseistor (220 ohm):                            12                                54                           120                 179                         650

Graded by Hanel
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int photoPin = A0;
unsigned long time;
unsigned long curr;

void setup() {
  //setup lcd to 16 columns, 2 rows
  lcd.begin(16, 2);
  //start output for testing
  Serial.begin(9600);
}

void loop() {
  //read data from pin a0
  int light = analogRead(photoPin);
  //print light data to console
  Serial.println(light);

  //start time
  time = millis();
  //set cursor to start
  lcd.setCursor(0, 0);
  //print time to lcd
  lcd.print(time);

  //update every half second
  if(time - curr >=500){
    //clear last string
    lcd.clear();
    //set cursor to second row
    lcd.setCursor(0, 1);
    curr = time;
    //check for light level and print corresponding string
    if(light < 200){
      lcd.print("dark");
    } else if(light < 400){
      lcd.print("partially dark");
    } else if(light < 600){
      lcd.print("medium");
    } else if(light < 900){
      lcd.print("fully lit");
    } else if(light <= 1000){
      lcd.print("brightly lit");
    } else {
      //just to catch any weird outliers
      lcd.print("light unknown");
    }
  }

}
