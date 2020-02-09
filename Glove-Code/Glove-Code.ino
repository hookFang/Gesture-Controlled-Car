/*Edwin Joseph Christie , 200412864
 * 12th December 2018
 * Final Project :- Gesture controlled Car ( Code for The Glove - it transmits accelerometer values to the car)
 * Code Retrived from :- https://www.youtube.com/watch?v=RTJ33EWmTRI
 * This Code trasmits the data read from the accelrometer to the reciever in the car
 */

/*Libraries*/
#include <SPI.h>        //SPI library to communicate with the nRF24L01.
#include "RF24.h"       //The main library for nRF24L01.
#include "Wire.h"       //Used for communication between the WiFi modules.
#include "I2Cdev.h"     //Used for communication with the accelerometer ( MPU6050).
#include "MPU6050.h"    //The main library of the accelerometer ( MPU6050).


//Objects are created the reads data from accelrometer.
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

//Variable that stores the X-axis & Y-axis data
int data[2];

//Define object from RF24 library - 9 and 10 are a digital pin numbers to which signals CE and CSN are connected.
RF24 radio(9,10);

//Address is created for coomunication between the WiFi Modules.                                  
const byte pipe[6] = "00001";

void setup(void){
  Serial.begin(9600);
  Wire.begin();      //Initiates the Wire Library           
  mpu.initialize();  //Initialize the MPU Object
  radio.begin();    //Starts to send data to the reciever     
  radio.openWritingPipe(pipe);   //Sets the address of the receiver to which the apllication will send data.
  radio.setPALevel(RF24_PA_MIN); //Sets the power amplifier level to minimum 
  radio.stopListening(); //Stop listening from incoming messages.
}

void loop(){
  //The accelerometer and gyro values are taken from  the accelerometer , only the acelerometer values are used 
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  //Calculates x-axis and y-axis values    
  getData();

  //Sends data to car
  sendData();
}

/*This method reads in the x-axis and y-axis values from the accelerometer*/
void getData(){
  //X-axis (data[0]) moves the car back and forward
  //Y axis (data[1]) moves the car left and right
  data[0] = map(ax, -17000, 17000, 300, 400 ); //Stores x-axis values in an integer array 
  data[1] = map(ay, -17000, 17000, 100, 200);  //Stores y-axis values in an integer array 
}

/*This method sends the x-axis and y-axis values to the car*/
void sendData(){
  radio.write(&data, sizeof(data)); //Sends the array which stores the x-axis and y-axis values to the reciever in the car
}
