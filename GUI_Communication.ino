//defining the maximum length of the array
#define MaxLength 32
//Declaring a char array
char command[MaxLength];  //stores the command
//Char variable
char readChar;
byte index = 0;
int i;
//static variable for reading in the delaytime
static int delayTime = 0;
//Flag to check whether the robot is moving or not
bool Moving = false;
unsigned long startTime = 0;
unsigned long dur = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//Initiating the serial communication
  delay(1000);
}
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    for (i = 0; i < 31; i++) {
      command[i] = '\0';
    }
    //Last character is initialized with null
    index = 0;
  
  while (Serial.available() > 0) {
    if (index < (MaxLength - 1)) {
      readChar = Serial.read();
      command[index] = readChar;
      index++;
      command[index] = '\0';
    }
    delay(100);
    String myString(command);
    String stringValue = "";
    int intValue = 0;
    int spaceIndex = myString.indexOf(' ');
    if (spaceIndex != -1)
    {
      stringValue = myString.substring(0, spaceIndex);    
      Serial.print("String : "+stringValue);    // Extract the string part
      intValue = myString.substring(spaceIndex + 1).toInt();
      Serial.print("Int value = "+(String)intValue);  // Extract the integer part
    }
    if (stringValue == "Right" || stringValue == "right") {
      //If Moving is false then the rover turns right
      if (!Moving) 
      {
        //delayTime = intValue * 1000;
        move_right(intValue);
        Moving = true;
        startTime = millis();
      }
    }
      if (stringValue == "Left" || stringValue == "left") {
        if (!Moving) 
        {
          delayTime = intValue * 1000;
          move_left(delayTime);
          Moving = true;
          startTime = millis();
        }
      }
      if(stringValue=="Forward"||stringValue=="forward")
      {
        if (!Moving) 
        {
          delayTime = intValue * 1000;
          move_Forward(delayTime);
          Moving = true;
          startTime = millis();
        }
      }
if(stringValue=="Backward" || stringValue=="backward")
  {
    if(!Moving)
    {
     delayTime=intValue*1000;
     move_Backward(delayTime);
     Moving=true;
     startTime=millis();
    }
  }
  if(stringValue=="Stop"||stringValue=="stop")
  {
    stop();
  }
  if (Moving && millis() - startTime >= delayTime) {
          delay(100);
          Moving = false;
        }
  }
  }
}

  void move_right(int duration) {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    delay(duration*1000);
    Serial.println("Right Duration"+ (String)duration);
    Serial.println("Moving");
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  void move_left(int duration) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);

    delay(duration);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  void move_Forward(int duration)
{
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  delay(duration);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}
void move_Backward(int duration)
{
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  delay(duration);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}
  void stop() {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
