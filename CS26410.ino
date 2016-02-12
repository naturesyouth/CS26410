#include <SharpIR.h>
#include <NewPing.h>
#include <Servo.h>

#define LDRLeft A0
#define LDRCenter A1
#define LDRRight A2
#define LDRTop A4
#define SharpIr A3

#define SerialRx 0
#define SerialTx 1
#define IrRx 2
#define IrTx 3
#define PB1 4
#define Dright 5
#define Dleft 6
#define LEDRed 7
#define Ping1 8
#define Ping2 9
#define Ping3 10
#define Ping4 11
#define SharpIrEnable 12
#define turret 13

#define DrightStop 68
#define DleftStop 84
#define TurretCenter 84


Servo Driveleft;
Servo Driveright;
Servo Turret;
SharpIR IRRangeFinder(SharpIr, 25, 93, 20150);
NewPing sonar1(Ping1, Ping1, 200);
NewPing sonar2(Ping2, Ping2, 200);
NewPing sonar3(Ping3, Ping3, 200);
NewPing sonar4(Ping4, Ping4, 200);

void setup() {
  
  Driveleft.attach(Dleft);
  Driveleft.write(DleftStop);
  Driveright.attach(Dright);
  Driveright.write(DrightStop);
  Turret.attach(turret);
  Turret.write(TurretCenter);

  
  pinMode(LDRLeft, INPUT);
  pinMode(LDRCenter, INPUT);
  pinMode(LDRRight, INPUT);
  pinMode(LDRTop, INPUT);
  pinMode(PB1,INPUT);
  
  pinMode(SharpIrEnable, OUTPUT);
  pinMode(LEDRed, OUTPUT);
  
  
  
}

void loop(){
delay(10);
}
