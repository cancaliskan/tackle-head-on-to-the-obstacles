#include <LiquidCrystal.h>

#define rightMotorEnable 7 //enable pin of right motor
#define rightBackMotor 6 //determines the direction of the right motor, goes back
#define rightForwardMotor 5 //determines the direction of the right motor, goes forward
#define leftMotorEnable 2 //enable pin of left motor
#define leftForwardMotor 4 //determines the direction of the left motor, goes forward
#define leftBackMotor 3 //determines the direction of the left motor, goes back

#define frontTrig 29 // TRIG pin 
#define frontEcho 28  // ECHO pin 

#define backTrig 27 // TRIG pin
#define backEcho 26  // ECHO pin

#define led 36

long frontValue, frontCm;
long backValue, backCm;

LiquidCrystal lcd(42, 43, 44, 45, 46, 47); // The pins to which the lcd is connected are identified.

char btData; // To keep the data from bluetooth.

void StopMotors()
{
        digitalWrite(rightMotorEnable, HIGH); //enable right motor
        analogWrite(rightForwardMotor, 0); //reset the rotation speed
        analogWrite(rightBackMotor, 0);  //reset the rotation speed
        digitalWrite(leftMotorEnable, HIGH);//enable left motor
        analogWrite(leftForwardMotor, 0); //reset the rotation speed
        analogWrite(leftBackMotor, 0);  //reset the rotation speed
        delay(0.01); //the motors stop for 1 second to allow them to go back in sudden motion when driving forward.
}

void PrintDistance()
{
    digitalWrite(frontTrig, LOW);
    digitalWrite(frontTrig, HIGH);
    digitalWrite(frontTrig, LOW);
    frontValue = pulseIn(frontEcho, HIGH);
    frontCm = frontValue * 0.034 / 2; //By dividing the measured time in two directions, we only measure the speed of travel. Then, we find the distance by dividing by the speed of sound.
    
    digitalWrite(backTrig, LOW);
    digitalWrite(backTrig, HIGH);
    digitalWrite(backTrig, LOW);
    backValue = pulseIn(backEcho, HIGH);
    backCm = backValue * 0.034 / 2; //By dividing the measured time in two directions, we only measure the speed of travel. Then, we find the distance by dividing by the speed of sound.

    lcd.clear();
    
    lcd.setCursor(0,0); //move the cursor back to the first column of the second row
    lcd.print("Front: ");
    lcd.setCursor(7,0); //move the cursor to column 7 because the distance is at the beginning of the line.
    lcd.print(frontCm); //print distance
    lcd.print(" cm"); //print the unit of measure
    
    lcd.setCursor(0,1); //move the cursor back to the first column of the second row
    lcd.print("Back: ");
    lcd.setCursor(6,1); //move the cursor to column 7
    lcd.print(backCm); //print distance
    lcd.print(" cm"); //print the unit of measure
    
    delay(0.01); //wait 250 millisecond
}

void setup()
{
    lcd.begin(16,2);

    pinMode(led,OUTPUT);
    
    pinMode(frontTrig, OUTPUT);
    pinMode(frontEcho,INPUT);
      
    pinMode(backTrig, OUTPUT);
    pinMode(backEcho,INPUT);
 
    delay(500); 
	// The serial port for reading data from bluetooth is opened 9600 baud used for communication.
    //It refers to the number of bits sent per second.
    Serial.begin(9600);
    delay(1000); 
    pinMode(leftMotorEnable, OUTPUT);
    pinMode(leftForwardMotor, OUTPUT);
    pinMode(leftBackMotor, OUTPUT); 
    pinMode(rightMotorEnable, OUTPUT);
    pinMode(rightForwardMotor, OUTPUT);
    pinMode(rightBackMotor, OUTPUT);
}

void loop()
{   
    PrintDistance();
    btData = (char) Serial.read(); // read data from bluetooth

    if( frontCm <=40 && (btData == 'F' || btData == 'G' || btData == 'I' || btData == 'L' || btData == 'R') )
    {
      
      digitalWrite(led,HIGH);
      StopMotors();
    }
    else
    {
          digitalWrite(led,LOW);
           
          if ( btData == 'F' ) //move forward
          {             
                    StopMotors();
                    //gave the command to move the robot.
                    digitalWrite(rightMotorEnable, HIGH);     //right
                    analogWrite(rightForwardMotor, 100);
                    digitalWrite(leftMotorEnable, HIGH);     //left
                    analogWrite(leftForwardMotor, 100);
          }
          else if (btData == 'G') // move left forward
          {
                    StopMotors();
                    //gave the command to move the robot.
                    digitalWrite(rightMotorEnable, HIGH);     //right
                    analogWrite(rightForwardMotor, 120);
                    digitalWrite(leftMotorEnable, HIGH);     //left
                    analogWrite(leftForwardMotor, 75);
          }   
          else if (btData == 'I') // move right forward
          {
                    StopMotors();
                    //gave the command to move the robot.
                    digitalWrite(rightMotorEnable, HIGH);     //right
                    analogWrite(rightForwardMotor, 75);
                    digitalWrite(leftMotorEnable, HIGH);     //left
                    analogWrite(leftForwardMotor, 120);
          }
          else if (btData == 'L') // move left
          {
                    StopMotors();
                    //gave the command to move the robot.
                    digitalWrite(rightMotorEnable, HIGH);     //right
                    analogWrite(rightForwardMotor, 150);
                    digitalWrite(leftMotorEnable, HIGH);     //left
                    analogWrite(leftForwardMotor, 0);
          }
          else if (btData == 'R') // move right
          {
                    StopMotors();
                    //gave the command to move the robot.
                    digitalWrite(rightMotorEnable, HIGH);     //right
                    analogWrite(rightForwardMotor, 0);
                    digitalWrite(leftMotorEnable, HIGH);     //left
                    analogWrite(leftForwardMotor, 150);
          }
    }
	
    if (btData == 'S') // for stop motors
    {
          StopMotors();
    }
    
    if( backCm <= 40 && (btData == 'B' || btData == 'H' || btData == 'J' ) )
    {
         digitalWrite(led,HIGH);
         StopMotors();
    } 
    else
    { 
                digitalWrite(led,LOW);
                
                if (btData == 'B') // move back
                {
                      StopMotors();
                      //gave the command to move the robot.
                      digitalWrite(rightMotorEnable, HIGH);     //right
                      analogWrite(rightBackMotor, 100);
                      digitalWrite(leftMotorEnable, HIGH);     //left
                      analogWrite(leftBackMotor, 100);
                }
                else if (btData == 'H') // move back left
                {
                      StopMotors();
                      //gave the command to move the robot.
                      digitalWrite(rightMotorEnable, HIGH);     //right
                      analogWrite(rightBackMotor, 120);
                      digitalWrite(leftMotorEnable, HIGH);     //left
                      analogWrite(leftBackMotor, 75);
                }
                else if (btData == 'J') // move back right
                {
                      StopMotors();
                      //gave the command to move the robot.
                      digitalWrite(rightMotorEnable, HIGH);     //right
                      analogWrite(rightBackMotor, 75);
                      digitalWrite(leftMotorEnable, HIGH);     //left
                      analogWrite(leftBackMotor, 120);
                }
    }       
}
