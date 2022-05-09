extern volatile unsigned long currentTime_millis;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
        currentTime_millis = millis();
        
        noInterrupts ();
        currentTime_millis = 0;
        interrupts ();
}
