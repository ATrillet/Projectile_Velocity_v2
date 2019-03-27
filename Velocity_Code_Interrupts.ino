const int pin1 = 2;
const int pin2 = 3;
unsigned long time1 = NULL;
unsigned long time2 = NULL;
float dist = 101600; //4 inches converted to micro meters

//Because micros() returns a long variable type, we had to convert
//4 inches to micrometers in order to do the velocity calculation
void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(pin1), timer1, RISING); //Setup both interupt pins
  attachInterrupt(digitalPinToInterrupt(pin2), timer2, RISING);
}

void timer1() {
  time1 = micros();     //Set when sensor 1 was broken
}

/*
 * Because interupts run at all times if a projectile bounces back
 * into either of our sensors time1 or time2 would be reset to a new
 * value.  So be have this interupt function outputing the velocity
 * as soon as sensor 2 is broken.  This allows for immediete results
 * and if the projectile passes in front of either sensor again, we 
 * already have good data ouput to the monitor.
 */
void timer2() {
  time2 = micros();     //Set when sensor 2 was broken

  /*
   * Arduino interupts operate somewhat strange.  It seems they don't process in order
   * so sensor 1 might trigger its timer function before sensor 2, but sensor 2 will get
   * a value before sensor 1.  This will cause time1-time2 to give a negative value.
   * So this if statement orders the subtraction correctly.
   * 
   * This could be looked into more, this is only a hypothesis, but results were found
   * to be wrong under this premisis
   */
  if (time1 > time2) {
         Serial.print(time1-time2);
         Serial.print("us\n");
         Serial.print(dist/(time1-time2), 4);  //Display the velocity
      } else {
         Serial.print(time2-time1);
         Serial.print("s\n");
         Serial.print(dist/(time2-time1), 4);  //Display the velocity
      }
      Serial.print("m/s\n");
}

void loop()
{
  delay(5000);//Wait 5 seconds to allow for allignment checks

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
  delay(5000);

  if (time1 == NULL) {
      Serial.print("Sensor 1 was not triggered\n");
  } 
  if (time2 == NULL) {
      Serial.print("Sensor 2 was not triggered\n");
  } 
  
//  if (time2 != NULL && time1 != NULL) {
//      Serial.print("Time1: ");
//      Serial.print(time1, 4);  //Display the velocity
//      Serial.println();
//
//      Serial.print("Time2: ");
//      Serial.print(time2, 4);  //Display the velocity
//      Serial.println();
//      if (time1 > time2) {
//         Serial.print(time1-time2);
//         Serial.print("us\n");
//         Serial.print(dist/(time1-time2), 4);  //Display the velocity
//      } else {
//         Serial.print(time2-time1);
//         Serial.print("s\n");
//         Serial.print(dist/(time2-time1), 4);  //Display the velocity
//      }
//      Serial.print("m/s\n");
//  }
  time2 = NULL;
  time1 = NULL;
}
