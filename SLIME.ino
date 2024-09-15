#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"
#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"
#include <SoftwareSerial.h>
#define ARDUINO_RX 4
//tx to 4
#define ARDUINO_TX 3
//rx to 3
SoftwareSerial myMP3(ARDUINO_RX,ARDUINO_TX);    

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

TMRpcm tmrpcm;

MyData data;

byte sendBuffer[6];

void selectTFCard(){
  sendBuffer[0] = 0x7E;
  sendBuffer[1] = 0x03;
  sendBuffer[2] = 0x35;
  sendBuffer[3] = 0x01;
  sendBuffer[4] = 0xEF;
  sendUARTCommand();
}

void playSound(byte songNumber){
  sendBuffer[0] = 0x7E;
  sendBuffer[1] = 0x04;
  sendBuffer[2] = 0x41;
  sendBuffer[3] = 0x00;
  sendBuffer[4] = songNumber;
  sendBuffer[5] = 0xEF;
  sendUARTCommand();
}

void stopSound(){
  sendBuffer[0] = 0x7E;
  sendBuffer[1] = 0x02;
  sendBuffer[2] = 0x0E;
  sendBuffer[3] = 0xEF;
  sendUARTCommand();
}

void setplayVolume(byte volum){
  sendBuffer[0] = 0x7E;
  sendBuffer[1] = 0x03;
  sendBuffer[2] = 0x31;
  sendBuffer[3] = volum;
  sendBuffer[4] = 0xEF;
  sendUARTCommand();  
}

void sendUARTCommand(){
  int q;
  for(q=0;q<sendBuffer[1] + 2;q++){
    myMP3.write(sendBuffer[q]);
  }
  Serial.println("command Sent");
  for(q=0;q<sendBuffer[1] + 2;q++){
    Serial.println(sendBuffer[q],HEX);
  }
  delay(25);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("UARTserialV2");
  myMP3.begin(9600);
  delay(500);
  selectTFCard();
  setplayVolume(30);
  Wire.begin();
  mpu.initialize();


  
}

void loop()
{
  int telunjuk = analogRead(A3);
  int manis = analogRead(A0);
  int kelingking = analogRead(A2);
  int tengah = analogRead(A1);
  int jempol = analogRead(A6);

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 
  0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255); 
  data.Z = map(az, -17000, 17000, 0, 255);  // Y axis data
  delay(100);
  
  Serial.print("x = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Y = ");
  Serial.print(data.Y);
  Serial.print("  ");
  Serial.print("z  = ");
  Serial.println(data.Z);
  Serial.print("  ");
  
 /*
  Serial.print("jempol = ");
  Serial.print(jempol);
  Serial.print(" ");
  
  Serial.print("telunjuk = ");
  Serial.print(telunjuk);
  Serial.print(" ");

  Serial.print("tengah = ");
  Serial.print(tengah);
  Serial.print(" ");
 
  Serial.print("manis = ");
  Serial.print(manis);
  Serial.print(" ");

  Serial.print("kelingking = ");
  Serial.print(kelingking);
  Serial.println(" ");

  delay(1);*/

  int thumb = 0;
  int index = 0;
  int middle = 0;
  int ring = 0;
  int pinkie = 1;

  if (jempol >= 750){
    thumb = 1;
  }
  if (telunjuk >= 600){
    index = 1;
  }
  if (tengah <= 920){
    middle = 1;
  }
  if (manis <= 220){
    ring = 1;
  }
  if (kelingking >= 600){
    pinkie = 0;
  }

  Serial.print(thumb);
  Serial.print(" ");
  Serial.print(index);
  Serial.print(" ");
  Serial.print(middle);
  Serial.print(" ");
  Serial.print(ring);
  Serial.print(" ");
  Serial.print(pinkie);
  Serial.println(" ");

  if (data.X > 200 && data.Z > 150){
    if (thumb == 0 && middle == 1 && ring == 0 && pinkie == 0){
      Serial.println("I love You");
      playSound(1);
      delay(2000);
    }
    if (thumb == 0 && middle == 0 && ring == 0 && pinkie == 0){
      Serial.println("Hello");
      playSound(3);
      delay(2000);
    }
  }
  if (data.X < 200 && data.Z > 190){
    if (thumb == 0 && middle == 0 && ring == 0 && pinkie == 0){
      Serial.println("Thank You");
      playSound(2);
      delay(2000);
    }
    if (thumb < 200 && middle == 0 && ring == g
  }
  
}
