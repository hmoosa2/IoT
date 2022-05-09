#include <SPI.h>
#include <WiFiNINA.h>


#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const unsigned long eventInterval = 5000;
unsigned long previousTime =0;

boolean daylight = true;

int colorR = 50;
int colorG = 50;
int colorB = 255;

// temperature variables
const int pinTemp = A0;      // pin of temperature sensor (A0)
const int pinAdc = A1;      // sound sensor
float temperature;
int B=3975;                  // B value of the thermistor
float resistance;
float TempF = 0; // variable to use with farenheit temperature


const int MIC = 1; //the microphone amplifier output is connected to pin A1
int adc;
int dB, PdB; //the variable that will hold the value read from the microphone each time


const int pinLed = 3;                        // pin of led define here (D3)

void setup() { 
  // put your setup code here, to run once:

Serial.begin(9600);     //Baud rate for the serial communication of Arduino
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    
    
    pinMode(A0,INPUT);      //Setting the A0 pin as input pin to take data from the temperature sensor 

    pinMode(3, OUTPUT);     //set pin 3 to OUTPUT 

    pinMode(pinLed, OUTPUT);                    // set led OUTPUT
}

void loop() {
  // put your main code here, to run repeatedly:
 unsigned long currentTime = millis();
 
if (currentTime - previousTime >= eventInterval) { //every 5 seconds
Serial.println(currentTime);                       //print in the time that has passed since the start of the program
previousTime = currentTime;                           
}
else if (currentTime <= 20000){ //when less than 20 seconds have passed since the start of the program
  digitalWrite(pinLed, HIGH);   //and then the LED comes on
  lcd.setCursor(8, 1);
lcd.print("Day");
}
else if (currentTime <= 25000){ //when less than 25 seconds have passed
  digitalWrite(pinLed, LOW);    //turn off the LED
  lcd.setCursor(8, 1);
lcd.print("Dark");
}
else{                           //after 25 seconds have passed
  digitalWrite(pinLed, HIGH);   //turn on the LED again
}

PdB = dB; //Store the previous of dB here

adc= analogRead(MIC); //Read the ADC value from amplifer/sound sensor 
//Serial.println (adc);//Print ADC for initial calculation 
dB = (adc+83.2073) / 11.003; //Convert ADC value to dB using Regression values

if (PdB!=dB)
Serial.println (dB);

if (dB>50)
{
int colorR = 255;
int colorG = 0;
int colorB = 0;
lcd.setRGB(colorR, colorG, colorB);
lcd.setCursor(0, 1);
lcd.print("N.Lvl 2");
digitalWrite(pinLed, LOW);   //turn off the LED
delay(250);
digitalWrite(pinLed, HIGH);   //turn on the LED again
}


else if (dB>40)
{
  lcd.setRGB(colorR, colorG, colorB);
int colorR = 50;
int colorG = 50;
int colorB = 255;
lcd.setCursor(0, 1);
lcd.print("N.Lvl 1");
}
else{
    lcd.setRGB(colorR, colorG, colorB);
int colorR = 50;
int colorG = 50;
int colorB = 255;
lcd.setCursor(0, 1);
lcd.print("N.Lvl 0");
}

//delay(100);

 
lcd.setCursor(13, 1);    //this code outputs the timer in seconds to the lcd screen 
lcd.print(millis()/1000);//divides the time the program has been running in milliseconds by 1000 to get the time this program has been running in seconds
delay(1000);
    
float currentTemp=getTemperature();     // currentTemp takes the value from getTemperature which reads in the temperature from the temperature sensor
    Serial.println(currentTemp);        //this will print the value of currentTemp into the serial monitor
    float currentTempF=degreeF();       // CurrentTempF links its value to degreeF's value 
    Serial.println(currentTempF);       //This prints CurrentTempF in the serial monitor
    displayTempF(currentTempF);         // DisplayTempF brings currentTempF's value to the LCD screen
    displaytemp(currentTemp);           //displaytemp brings currentTemp's value to the LCD screen
}
float degreeF(){                  // farenheit code start
  float TempF=temperature*9/5+32; //temperature to farenheit conversion on temperature, becomes TempF
  return TempF;                   //returns TempF to degreeF as a function

}
float getTemperature(){
  int val = analogRead(pinTemp);                               // get analog value
  resistance=(float)(1023-val)*10000/val;                      // get resistance
  temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;     // calc temperature
  return temperature;
}
 
void displaytemp(float tempNow){  //displays the temperature value
  // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 0);
    // print the number of seconds since reset:
    lcd.print(tempNow);
}
void displayTempF(float tempFNow){ //displays the temperature value in farenheit
 // set the cursor to column 7, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(6, 0);
    // print the number of seconds since reset:
    lcd.print(tempFNow);
}
void displayTime(float timeNow){ //displays the time in seconds since the reset
    // set the cursor to column 7, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(12, 0);
    // print the number of seconds since reset:
    lcd.print(timeNow);
}
