int duration;                                                          //Stores duration of pulse in
float distance;                                                        // Stores distance
char echo = 7;      // Pin for SRF05
char trigger = 6;
void setup(void)
{
int i;
for(i=5;i<=8;i++)
pinMode(trigger, OUTPUT);
pinMode(echo, INPUT);
Serial.begin(9600);

}
void Go()
{
  analogWrite (6,255);
digitalWrite(8,LOW);

analogWrite (5,255);
digitalWrite(7,LOW);
}


void gauche(void)
{
/*int leftspeed = 255; //255 is maximum speed
int rightspeed = 255;
*/
analogWrite (6,255);
digitalWrite(8,LOW);

analogWrite (5,255);
digitalWrite(7,HIGH);

 delay(3200);

}

void droite(void)
{
/*int leftspeed = 255; //255 is maximum speed
int rightspeed = 255;
*/
analogWrite (6,255);
digitalWrite(8,HIGH);

analogWrite (5,255);
digitalWrite(7,LOW);

delay(1000);

}
void loop(void)
{
//pinMode(sensorpin, OUTPUT);
  digitalWrite(trigger, LOW);                          // Make sure pin is low before sending a short high to trigger ranging
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);                         // Send a short 10 microsecond high burst on pin to start ranging
  delayMicroseconds(2);
  digitalWrite(trigger, LOW);                                  // Send pin low again before waiting for pulse back in

  
  duration = pulseIn(echo, HIGH);                        // Reads echo pulse in from SRF05 in micro seconds
  distance = duration/58;                                      // Dividing this by 58 gives us a distance in cm
  Serial.println(distance); // Wait before looping to do it again
 delay(100); 

 
  
  if( distance>7){
    Go();
  }
  else
  {
   droite();
  }

}    
