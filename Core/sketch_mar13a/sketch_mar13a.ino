/*
Author:    William Hogg
Description:
            This is a program to emulate a cockroach that will follow walls and react to light.

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
#define DleftStop       84
#define TurretCenter    84
#define AmbiantLight    670
#define Light           900
#define Dark            300

//other deffinitions
#define BrightnessTop      0
#define MovingAverageWidth 5
#define NoAverageDataSets  5
#define Speed              10
#define sweepangle 45


//app control deffinition
#define Forward         48
#define Backward  49
#define Turret_Left 50
#define Turret_Right  51
#define Pivot_Left  52
#define Pivot_Right 53
#define Stop          54
#define Function_1  55
#define Function_2  56
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

typedef struct bc {
  int vals[3];
  int index;
  int delta;
} boxcar;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int one = Serial.parseInt();
    int two = Serial.parseInt();
    
    Serial.println();
  }
}


void boxcar_addValue(int add,int set, bc average){
    int offset = set*MovingAverageWidth;
    if(boxcar_index[set] == MovingAverageWidth+offset){
        boxcar_index[set] = 0;
        boxcar[boxcar_index[set]+offset] = add/MovingAverageWidth;
    } else{
        boxcar_index[set]++;
        boxcar[boxcar_index[set]+offset] = add/MovingAverageWidth;
    }    
}
        

int boxcarGetAverage(int set) {
    int mean = 0;
    int offset = set*MovingAverageWidth;
    for (int i =0; i < MovingAverageWidth; i++){
        mean = mean + boxcar[i+offset];       
    }    
    return mean;
}

void readSonar(int pingNo){
    int range = 0;
    switch (pingNo) {
        case 1:
            pings[0] = sonar1.ping_cm();
             
            break;
        case 2:
            pings[1] = sonar2.ping_cm();
            break;
        case 3:
            pings[2] = sonar3.ping_cm();
            break;
        case 4:
            pings[3] = sonar4.ping_cm();
            break;
    } 
      //Serial.println(pings[1]);
      //Serial.println(pings[3]+" " + pings[2]);
    //boxcar_addValue(range,pingNo);
}




