const int pin1 = 2;
const int pin2 = 3;
unsigned long time1 = NULL;
unsigned long time2 = NULL;
float dist = 101600; //4 inches.  Change if sensing range differs

//Because microseconds are not recorded with decimals, we had to use
//Megameters instead of meters in order to get the correct units
//for our calculations

void setup()
{
  Serial.begin(9600);
  //pinMode(pin1, INPUT);
  //pinMode(pin2, INPUT);
  //delay(5000)
  attachInterrupt(digitalPinToInterrupt(pin1), timer2, RISING);
  attachInterrupt(digitalPinToInterrupt(pin2), timer1, RISING);
  
}

void timer1() {
  time1 = micros();
}

void timer2() {
  time2 = micros();
}

void loop()
{
  delay(5000);//Wait 5 seconds in case laser and transistors are not aligned

  if(digitalRead(pin1) == HIGH)
  {
    Serial.print("pin1\n");     //Notify alignment problem
  }

  if(digitalRead(pin2) == HIGH)
  {
    Serial.print("pin2\n");
  }
  if (digitalRead(pin1) == HIGH || digitalRead(pin2) == HIGH) {
    Serial.print("Alignment is off, readjust\n");     //Notify alignment problem
    return;     //start the loop over again
  }
  Serial.print("Ready to fire\n");      //Notify user that system is ready
  Serial.print("Press y then enter when ready to fire\n");
  while('y' != Serial.read()){}
  Serial.print("Fire!\n");
  
//  while(digitalRead(pin2) == LOW){}   //Don't allow the code to continue until the first sensor is activated
//                                      //If we endlessly loop we might have missed the ball, include a return in that case
//  time1 = micros();                   //Record the time
//        
//  while(digitalRead(pin1) == LOW){}   //Don't allow the code to continue until the second sensor is activated
//  time2 = micros();                   //Record the time
//
//  if(time1 == NULL || time2 == NULL) {      //If the projectile was not detected, notify
//    Serial.print("Projectile not detected\n");
//  }
//  else {
  delay(5000);

  if (time1 == NULL) {
      Serial.print("Sensor 1 was not triggered\n");
  } 
  if (time2 == NULL) {
      Serial.print("Sensor 2 was not triggered\n");
  } 
  
  if (time2 != NULL && time1 != NULL) {
      Serial.print(dist/(time2-time1), 4);  //Display the velocity
      Serial.print("m/s\n");
  }
  time2 = NULL;
  time1 = NULL;
}
