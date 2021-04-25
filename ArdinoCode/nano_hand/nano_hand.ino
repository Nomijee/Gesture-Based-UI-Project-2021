 #include <RH_ASK.h>
 #include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"    

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
};

MyData data;
void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
         Wire.begin();
  mpu.initialize();
}

void loop()
{

 mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  // Y axis data
  //delay(500);
 // Serial.print("Axis X = ");
 // Serial.print(data.X);
  //Serial.print("  ");
  //Serial.print("Axis Y = ");
 // Serial.println(data.Y);


  
    const char *msg1 = "R";
    const char *msg2 = "L";
    const char *msg3 = "F";
    const char *msg4 = "B";
    const char *msg5 = "S";
 if (data.Y < 50) { //gesture : down 
              driver.send((uint8_t *)msg1, strlen(msg1));
 }
      if (data.Y > 200)  { //gesture : down 
              driver.send((uint8_t *)msg2, strlen(msg2));
 }        
 if (data.X > 155) { //gesture : down 
              driver.send((uint8_t *)msg3, strlen(msg3));
 }        
 if (data.X < 80){ //gesture : down 
              driver.send((uint8_t *)msg4, strlen(msg4));
 }        
 if (data.X > 100 && data.X < 170 && data.Y > 80 && data.Y < 130){ //gesture : down 
              driver.send((uint8_t *)msg5, strlen(msg5));
 }        
    driver.waitPacketSent();
    delay(50);    
}
