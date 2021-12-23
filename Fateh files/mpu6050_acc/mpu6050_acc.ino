#include <SD.h>
#include <SPI.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif  
File myFile;  // class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high  
int i=1;
int pinCS = 10; //CS pin for SD card 
int scale = 16384; //divide values by MPU6050 sensitivity scale to get readings in g's (m/s^2 / 9.8)
                   //use scale = 16384 for the default I2Cdevlib sensitivity setting of +/-2  
int16_t ax, ay, az;  
#define LED_PIN 13
bool blinkState = false;  void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif      // initialize serial communication
    // serial value can be up to you depending on project
    Serial.begin(9600);      // initialize SD card
    if (SD.begin())
    {
        Serial.println("SD card is ready to use.");
    } else
    {
        Serial.println("SD card initialization failed");
        return;
    }   // initialize accel/gyro
    Serial.println("Initializing accelerometer...");
    accelgyro.initialize();
    accelgyro.setSleepEnabled(false);  // verify connection
    Serial.println("Testing accelerometer connection...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");      // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);

}
void loop() {
  
    // read raw accelerometer measurements from device
    accelgyro.getAcceleration(&ax, &ay, &az);      // display tab-separated accel x/y/z values in serial monitor
    Serial.print("acceleration:\t");
    Serial.print((float) ax / scale); Serial.print("\t");
    Serial.print((float) ay / scale); Serial.print("\t");
    Serial.println((float) az / scale); 
  
    // write the accelerometer values to SD card
    myFile = SD.open("test2.txt", FILE_WRITE);
    if (myFile) {
      myFile.print(i); myFile.print("\t");
      myFile.print("acceleration:\t");
      myFile.print((float) ax / scale); myFile.print("\t");
      myFile.print((float) ay / scale); myFile.print("\t");
      myFile.println((float) az / scale); 
      myFile.close();
    }
    i=i+1;
    // blink LED to indicate activity
    blinkState = !blinkState;//    digitalWrite(LED_PIN, blinkState);
    delay(10);
}
