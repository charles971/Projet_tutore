#define START_CMD_CHAR '*'
#define END_CMD_CHAR '#'
#define DIV_CMD_CHAR '|'
#define CMD_DIGITALWRITE 10
#define CMD_ANALOGWRITE 11
#define CMD_TEXT 12
#define CMD_READ_ARDUDROID 13
#define MAX_COMMAND 20  // max command number code. used for error checking.
#define MIN_COMMAND 10  // minimum command number code. used for error checking. 
#define IN_STRING_LENGHT 40
#define MAX_ANALOGWRITE 255
#define PIN_HIGH 3
#define PIN_LOW 2

String inText;

float distance;                                                        // Stores distance
char echo = 4;      // Pin for SRF05
char trigger = 3;
int duration;

void setup(void)
{
pinMode(trigger, OUTPUT);
pinMode(echo, INPUT);

Serial.begin(9600);
Serial.println("ArduDroid 0.12 Alpha by TechBitar (2013)");
Serial.flush();
}

// 2a) select the requested pin# for DigitalWrite action
void set_digitalwrite(int pin_num, int pin_value)
{
  switch (pin_num) {
  case 6:
    pinMode(6, OUTPUT);
    digitalWrite(6, pin_value);         
    Go();
    break;
  case 5:
    pinMode(5, OUTPUT);
    digitalWrite(5, pin_value); 
    droite();      
    break;
  case 4:
     gauche();
    break;
  case 3:
   Stop();
    break;
  case 2:
    pinMode(2, OUTPUT);
    digitalWrite(2, pin_value); 
    // add your code here       
    break;      
    // default: 
    // if nothing else matches, do the default
    // default is optional
  } 
}

void Go()
{
  analogWrite (6,255);
  digitalWrite(8,LOW);

  analogWrite (5,255);
  digitalWrite(7,LOW);
}

void Stop()
{
  analogWrite (6,0);
  digitalWrite(8,LOW);

  analogWrite (5,0);
  digitalWrite(7,LOW);
}

void ultrason()
{
  //pinMode(sensorpin, OUTPUT);
  digitalWrite(trigger, LOW);                          // Make sure pin is low before sending a short high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(trigger, HIGH);                         // Send a short 10 microsecond high burst on pin to start ranging
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);                                  // Send pin low again before waiting for pulse back in

  
  duration = pulseIn(echo, HIGH);                        // Reads echo pulse in from SRF05 in micro seconds
  distance = duration/58;                                      // Dividing this by 58 gives us a distance in cm
  Serial.println(distance); // Wait before looping to do it again
  
  delay(100); 
}




void gauche(void)
{
analogWrite (6,255);
digitalWrite(8,LOW);

analogWrite (5,255);
digitalWrite(7,HIGH);

 delay(2000);

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

delay(2000);
}

void loop(void)
{
  int rand1=1; 

  Serial.flush();
  int ard_command = 0;
  int pin_num = 0;
  int pin_value = 0;

  char get_char = ' ';  //read serial

  // wait for incoming data
  if (Serial.available() < 1) return; // if serial empty, return to loop().

  // parse incoming command start flag 
  get_char = Serial.read();
  if (get_char != START_CMD_CHAR) return; // if no command start flag, return to loop().

  // parse incoming command type
  ard_command = Serial.parseInt(); // read the command
  
  // parse incoming pin# and value  
  pin_num = Serial.parseInt(); // read the pin
  pin_value = Serial.parseInt();  // read the value

// 2) GET digitalWrite DATA FROM ARDUDROID
  if (ard_command == CMD_DIGITALWRITE){  
    if (pin_value == PIN_LOW) pin_value = LOW;
    else if (pin_value == PIN_HIGH) pin_value = HIGH;
    else return; // error in pin value. return. 
    set_digitalwrite( pin_num,  pin_value);  // Uncomment this function if you wish to use 
    return;  // return from start of loop()
  }


  ultrason();
 if( distance<10){
   Stop();
  }

}
