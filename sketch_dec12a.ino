#include <Servo.h>

Servo leftX;
Servo leftY;
Servo rightX;
Servo rightY;
Servo eyelid;

int LXPos;
int LYPos;
int RXPos;
int RYPos;
int EPos;

int LXTar;
int LYTar;
int RXTar;
int RYTar;
int ETar;

int LXMin= 72;
int LXMax = 107;
int RXMin = 58;
int RXMax = 93;
int LYMin = 60;
int LYMax = 107;
int RYMin = 52;
int RYMax = 100;
int EMin= 115;
int EMax = 180;


void setup() {
  Serial.begin(115200);
  
  leftX.attach(8);
  leftY.attach(9);
  rightX.attach(10);
  rightY.attach(11);
  eyelid.attach(12);

  LXPos = LXTar = 89;
  LYPos = LYTar = 90;
  RXPos = RXTar = 85;
  RYPos = RYTar = 82;
  EPos = ETar = 180;
}

void loop() {
  leftX.write(LXPos);
  leftY.write(LYPos);
  rightX.write(RXPos);
  rightY.write(RYPos);
  eyelid.write(EPos);
  updateTarget();
  updatePosition();
  delay(15);
}

void updateTarget(){
  int percent = -1;
  int val = 0;
  char dir;
  if(Serial.available()){
    char command = Serial.read();
    switch(command){
      case 'E':
        percent = Serial.parseInt();
        percent = min(max(percent, 0), 100);
        val = EMin + (EMax - EMin) * percent / 100;
        if(val != 0){
          ETar = val;
          ETar = max(EMin, ETar);
          ETar = min(EMax, ETar);
        }
        break;
      case 'L':
        dir = Serial.read();
        switch(dir){
          case 'X':
            percent = Serial.parseInt();
            percent = min(max(percent, 0), 100);
            val = LXMin + (LXMax - LXMin) * percent / 100;
            if(val != 0){
              LXTar = val;
              LXTar = max(LXMin, LXTar);
              LXTar = min(LXMax, LXTar);
            }
            break;
          case 'Y':
            percent = Serial.parseInt();
            percent = min(max(percent, 0), 100);
            val = LYMin + (LYMax - LYMin) * percent / 100;
            if(val != 0){
              LYTar = val;
              LYTar = max(LYMin, LYTar);
              LYTar = min(LYMax, LYTar);
            }
            break;
        }
        break;
      case 'R':
        dir = Serial.read();
        switch(dir){
          case 'X':
            percent = Serial.parseInt();
            percent = min(max(percent, 0), 100);
            val = RXMin + (RXMax - RXMin) * percent / 100;
            if(val != 0){
              RXTar = val;
              RXTar = max(RXMin, RXTar);
              RXTar = min(RXMax, RXTar);
            }
            break;
          case 'Y':
            percent = Serial.parseInt();
            percent = min(max(percent, 0), 100);
            val = RYMin + (RYMax - RYMin) * percent / 100;
            if(val != 0){
              RYTar = val;
              RYTar = max(RYMin, RYTar);
              RYTar = min(RYMax, RYTar);
            }
            break;
        }
        break;
    }
  }
}

void updatePosition(){
  
  if(ETar > EPos){
    EPos++;
  }
  else{
    if(ETar < EPos){
      EPos--;
    }
  }
  
  if(LXTar > LXPos){
    LXPos++;
  }
  else{
    if(LXTar < LXPos){
      LXPos--;
    }
  }
  
  if(LYTar > LYPos){
    LYPos++;
  }
  else{
    if(LYTar < LYPos){
      LYPos--;
    }
  }
  
  if(RXTar > RXPos){
    RXPos++;
  }
  else{
    if(RXTar < RXPos){
      RXPos--;
    }
  }
  
  if(RYTar > RYPos){
    RYPos++;
  }
  else{
    if(RYTar < RYPos){
      RYPos--;
    }
  }
}
