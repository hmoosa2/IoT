const unsigned long eventInterval = 5000;
const unsigned long daytime = 10000;
const unsigned long nighttime = 30000;
unsigned long previousTime =0;
unsigned long daytimepassed =0;
unsigned long nighttimepassed =0;
bool morning;
const int pinLed = 3;  // pin of led define here (D3)
 extern volatile unsigned long timer0_millis;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//unsigned long currentTime = millis();

//if (currentTime - previousTime >= eventInterval) {
//Serial.println(currentTime);

//previousTime = currentTime;



//if (currentTime - daytimepassed >= daytime) {
//daytimepassed = currentTime;
//Serial.println("day is over");
//morning = false;
//}
//if (morning = false){
//digitalWrite (pinLed, LOW); //turn off the LED
//}
//else{

//}
//if (currentTime - nighttimepassed >= nighttime) {
//nighttimepassed = currentTime;
//Serial.println("night is over");
//}
if (millis() >= 30000){
  noInterrupts ();
        timer0_millis = 0;
        interrupts ();
}
}
