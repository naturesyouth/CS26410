/*
Author:    William Hogg
Description:
            This is a core proram for features that span all instances
            of my robot control work on the CS26410 robot

*/
//included librarys
#include <SharpIR.h>
#include <NewPing.h>
#include <Servo.h>

//analog pin definitions
#define LDRLeft         A0
#define LDRCenter       A1
#define LDRRight        A2
#define LDRTop          A4
#define SharpIr         A3

//digital pin definitions
#define SerialRx        0
#define SerialTx        1
#define IrRx            2
#define IrTx            3
#define PB1             4
#define Dright          5
#define Dleft           6
#define LEDRed          7
#define Ping1           8
#define Ping2           9
#define Ping3           10
#define Ping4           11
#define SharpIrEnable   12
#define turret          13

//calibration values
#define DrightStop      67
#define DleftStop       83
#define TurretCenter    84

//app control deffinition
#define Forward         48
#define Backward	49
#define Turret_Left	50
#define Turret_Right	51
#define Pivot_Left	52
#define Pivot_Right	53
#define Stop	        54
#define Function_1	55
#define Function_2	56
#define Function_3      57

//object instantition 
Servo Driveleft;
Servo Driveright;
Servo Turret;
SharpIR IRRangeFinder(SharpIr, 25, 93, 20150);
NewPing sonar1(Ping1, Ping1, 200);
NewPing sonar2(Ping2, Ping2, 200);
NewPing sonar3(Ping3, Ping3, 200);
NewPing sonar4(Ping4, Ping4, 200);
SharpIR dist_sensor(SharpIr, 25, 93, 20150);

/*
void remote(int val) {
  switch (val) {
      case Forward:
          //move forward
          motorBasic(1);
          break;
      case Backward:
          //move backwards
          motorBasic(1);
          break;
      case Turret_Left:
          //move turret left
          break;
      case Turret_Right:
          //move Turret right
          break;
      case Pivot_Left:
          //pivot robot left
          motorBasic(2);
          break;
      case Pivot_Right:
          //pivot robot right
          motorBasic(3);
          break;
      case Stop:
          //stop robot
          motorBasic(0);
          break;
      case Function_1:
          //implement function 1
          break;
      case Function_2:
          //implement function 2
          break;
      case Function_3:
          //implement function 2
          break;
      default:
          //stuff perhaps
          break;
  }
}
*/
   
void motorBasic(int dir, int drive) {
    if(dir != 0){
        Driveleft.attach(Dleft);
        Driveright.attach(Dright);
    }
  switch (dir) {
    case -1:
      //do something when var equals 1
      Driveleft.write(DleftStop - 40);
      Driveright.write(DrightStop + 40);
      break;
    case 0:
      //do something when var equals 2
      Driveleft.write(DleftStop );
      Driveright.write(DrightStop);
      break;
    case 1:
      //do something when var equals 2
      Driveleft.write(DleftStop + 40);
      Driveright.write(DrightStop - 40);
      break;
    case 2:
      //do something when var equals 2
      Driveleft.write(DleftStop);
      Driveright.write(DrightStop + 40);
      break;
    case 3:
      //do something when var equals 2
      Driveleft.write(DleftStop - 40);
      Driveright.write(DrightStop);
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
      delay(drive);
      if(dir != 0){
        Driveleft.detach();
        Driveright.detach();
    }
  }
}   

int turret_range(int deg){
    Turret.attach(turret);
    Turret.write(deg);
    digitalWrite(SharpIrEnable, LOW);
    delay(500);
    int turret_dist = dist_sensor.distance();
    digitalWrite(SharpIrEnable, HIGH);
    Turret.detach();
    return(turret_dist);
}
    
  

void setup() {
  
  
  Driveleft.write(DleftStop);
  
  Driveright.write(DrightStop);
  Turret.attach(turret);
  Turret.write(TurretCenter);
  
  pinMode(LDRLeft, INPUT);
  pinMode(LDRCenter, INPUT);
  pinMode(LDRRight, INPUT);
  pinMode(LDRTop, INPUT);
  pinMode(PB1,INPUT);
  
  pinMode(SharpIrEnable, OUTPUT);
  digitalWrite(SharpIrEnable, HIGH);
  pinMode(LEDRed, OUTPUT);
  
  Serial.begin(9600);
  
   
  
  
}

void loop(){
    Serial.println("starting loop");
    
    for(int i=0; i < 180; i=i+10){
        Serial.println(turret_range(i));
    }
    
delay(250);
}




