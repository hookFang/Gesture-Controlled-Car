/*Edwin Joseph Christie , 200412864
 * 12th December 2018
 * Final Project :- Gesture controlled Car ( Code for The Car - it recives data from the glove)
 * Code Retrived from :- https://www.youtube.com/watch?v=RTJ33EWmTRI
 * This Code recieves data that is send from the accelerometer
 */

/*Libraries*/
#include <SPI.h>      //SPI library for communicate with the nRF24L01.
#include "RF24.h"     //The main library of the nRF24L01.

//Defines enable pins of the Motors
const int enbA = 3;
const int enbB = 5;

//Defines control pins of the Motors
const int input1 = 2;    //Right Motor (-)
const int input2 = 4;    //Right Motor (+)
const int input3 = 7;    //Left Motor (+)
const int input4 = 6;    //Right Motor (-)

//Define variable for the motors speeds
//I have defined a variable for each of the two motors 
//This way you can synchronize the rotation speed difference between the two motors
int RightSpd = 130;
int LeftSpd = 150;

//Integer array recives the x-axis and y-axis values from the accelerometer
int data[2];

//Define object from RF24 library - 9 and 10 are a digital pin numbers to which signals CE and CSN are connected
RF24 radio(9,10);

//Address is created for coomunication between the WiFi Modules. 
const byte pipe[6] = "00001";

void setup(){
  pinMode(enbA, OUTPUT); //Setup enbA as Output.
  pinMode(enbB, OUTPUT); //Setup enbB as Output.
  pinMode(input1, OUTPUT); //Setup input1 as Output.
  pinMode(input2, OUTPUT); //Setup input2 as Output.
  pinMode(input3, OUTPUT); //Setup input3 as Output.
  pinMode(input4, OUTPUT); //Setup input4 as Output.
  
  Serial.begin(9600);
  radio.begin(); //Start the nRF24 communicate.            
  radio.openReadingPipe(0, pipe); //Sets the address of the transmitter to which the program will receive data.
  radio.setPALevel(RF24_PA_MIN); //Sets the power amplifier level to minimum. 
  radio.startListening(); //Start listening on the pipes opened for reading.             
}

void loop(){
  if (radio.available()) //Checks if the WiFi module is available
  { radio.read(&data, sizeof(data)); //If available it reads data from the accelerometer
        
    if(data[0] > 380) //Checks the value of data
      moveForward(); //Moves the car forward
        
    if(data[0] < 310)//Checks the value of data
      moveBackward(); // Moves the car backward
    
    if(data[1] < 110)//Checks the value of data
     moveLeft(); //Moves the car to left
    
    if(data[1] > 180)//Checks the value of data
     moveRight(); //Moves the car to right
  
    if(data[0] > 330 && data[0] < 360 && data[1] > 130 && data[1] < 160) //Checks the value of data
      stopCar(); //Stops the car
  }
}

/*This method moves the car forward */
void moveForward(){
  //Car moves forward            
  analogWrite(enbA, RightSpd); //Controls the speed of right motor
  analogWrite(enbB, LeftSpd); //Controls the speed of left motor
  digitalWrite(input1, HIGH); //Right Motor (-) is turned on
  digitalWrite(input2, LOW); //Right Motor (+) is turned off
  digitalWrite(input3, HIGH); //Left Motor (+) is turned on
  digitalWrite(input4, LOW); //Left Motor (-) is turned off
}

/*This method moves the car backward */
void moveBackward(){
  //Car Moves backward              
  analogWrite(enbA, RightSpd); //Controls the speed of right motor
  analogWrite(enbB, LeftSpd); //Controls the speed of left motor
  digitalWrite(input1, LOW); //Right Motor (-) is turned off
  digitalWrite(input2, HIGH);  //Right Motor (+) is turned on
  digitalWrite(input3, LOW); //Left Motor (+) is turned off
  digitalWrite(input4, HIGH); //Left Motor (-) is turned on
}

/*This method moves the car to left*/
void moveLeft(){
  //Car Moves left
  analogWrite(enbA, RightSpd); //Controls the speed of right motor
  analogWrite(enbB, LeftSpd); //Controls the speed of left motor
  digitalWrite(input1, HIGH); //Right Motor (-) is turned on
  digitalWrite(input2, LOW); //Right Motor (+) is turned off
  digitalWrite(input3, LOW);  //Left Motor (+) is turned off
  digitalWrite(input4, HIGH); //Left Motor (-) is turned on
} 

/*This method moves the car to right*/
void moveRight(){
  //Car Moves right
  analogWrite(enbA, RightSpd); //Controls the speed of right motor
  analogWrite(enbB, LeftSpd); //Controls the speed of left motor
  digitalWrite(input1, LOW);  //Right Motor (-) is turned off
  digitalWrite(input2, HIGH); //Right Motor (+) is turned on
  digitalWrite(input3, HIGH);  //Left Motor (+) is turned on
  digitalWrite(input4, LOW); //Left Motor (-) is turned off
}

/*This method stops the car*/
void stopCar(){
  //Stops car
  analogWrite(enbA, 0); //Speed of motor is 0
  analogWrite(enbB, 0); //Speed of motor is 0
}
