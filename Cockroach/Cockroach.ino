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

struct w {
  int theta;
  int CMDist;
};

struct boxcar {
  int vals[NoAverageDataSets];
  int index;
  int delta;
};

struct motors {
  int leftspeed;
  int rightspeed;
};

//global variables
int boxcar[MovingAverageWidth * NoAverageDataSets];
int boxcar_index[NoAverageDataSets];

int  ldrPins[] = {ldrPin1, ldrPin2, ldrPin3};
int calibrateHigh[] = {0, 0, 0}; //these arrays store the high and low values for sensor calibration
int calibrateLow[] = {0, 0, 0};

int priority = 0;
int driveVal = 0;

struct boxcar pings[4];
struct w  walls[2];


void setup() {

  Driveleft.attach(Dleft);
  Driveleft.write(DleftStop);
  Driveright.attach(Dright);
  Driveright.write(DrightStop);
  // Turret.attach(turret);
  // Turret.write(TurretCenter);

  pinMode(LDRLeft, INPUT);
  pinMode(LDRCenter, INPUT);
  pinMode(LDRRight, INPUT);
  pinMode(LDRTop, INPUT);
  pinMode(PB1, INPUT);

  pinMode(SharpIrEnable, OUTPUT);
  pinMode(LEDRed, OUTPUT);

  Serial.begin(9600);

  //ini the moving average array
  for (int i = 0; i < MovingAverageWidth; i++) {
    boxcar_addValue(analogRead(LDRTop), BrightnessTop);
    delay(2);
  }
  //ini the moving average for sonars
  for (int p = 1; p <= 4; p++) {
    for (int i = 0; i < MovingAverageWidth; i++) {
      readSonar(p);
      delay(2);
    }
  }
}


void loop() {
  driveVal = 0;
  priority = 0;
  //Serial.println("BOOP LOOP");
  boxcar_addValue(analogRead(LDRTop), BrightnessTop);
  readSonar(1);
  readSonar(2);
  readSonar(3);
  readSonar(4);
  //Serial.print("LDRTop = ");
  //Serial.println(boxcarGetAverage(BrightnessTop));
  //Serial.print("sonar 3 says ");
  //Serial.println(boxcarGetAverage(3));
  //Serial.println(sonar1.ping());
  //Serial.println("avoid");
  avoider();
  //Serial.println("sense");
  sensitivity();
  //Serial.println("follow");
  //followWall();

  Serial.print(priority);
  Serial.println(driveVal);
  motor_basic(driveVal);
  delay(500);
  motor_basic(1);
  delay(500);
}


void followWall() {
  int range = (boxcarGetAverage(&pings[3]));
  if ( range <= 7) {
    motor_queue(2, 3);
  } else if (range >= 7) {
    motor_queue(2, 2);
  }
}


void avoider() {
  //int leftRange = boxcarGetAverage(2);
  //int rightRange = boxcarGetAverage(3);
  if (boxcarGetAverage(&pings[0]) <= 5 || boxcarGetAverage(&pings[1]) <= 5 || boxcarGetAverage(&pings[2]) <= 5 || boxcarGetAverage(&pings[3]) <= 5) {
    motor_queue(3, 3);
    //delay(500);
  }
}


void sensitivity() {
  int brightness = boxcarGetAverage(BrightnessTop);
  if ( brightness < Dark) {
    motor_queue(4, 0);
  } else if (brightness > Light) {
    //motor_basic(2);
  } else {
    motor_queue(0, 1);
  }
}


void readSonar(int pingNo) {
  int range = 0;
  switch (pingNo) {
    case 1:

      boxcar_addValue(sonar1.ping_cm(), &pings[0]);

      break;
    case 2:
      boxcar_addValue(sonar2.ping_cm(), &pings[1]);
      break;
    case 3:
      boxcar_addValue(sonar3.ping_cm(), &pings[2]);
      break;
    case 4:
      boxcar_addValue(sonar4.ping_cm(), &pings[3]);
      break;
  }
  //Serial.println(pings[1]);
  //Serial.println(pings[3]+" " + pings[2]);
  //boxcar_addValue(range,pingNo);
}


void remote(int val) {
  switch (val) {
    case Forward:
      //move forward
      motor_basic(1);
      break;
    case Backward:
      //move backwards
      motor_basic(1);
      break;
    case Turret_Left:
      //move turret left
      break;
    case Turret_Right:
      //move Turret right
      break;
    case Pivot_Left:
      //pivot robot left
      motor_basic(2);
      break;
    case Pivot_Right:
      //pivot robot right
      motor_basic(3);
      break;
    case Stop:
      //stop robot
      motor_basic(0);
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

void motor_queue(int pri, int mot) {
  if (pri > priority) {
    priority = pri;
    driveVal = mot;
  }
}


void motor_basic(int dir) {
  switch (dir) {
    case 0:
      //Stop motors
      Driveleft.write(DleftStop );
      Driveright.write(DrightStop);
      break;
    case 1:
      //Drive forwards
      Driveleft.write(DleftStop + Speed);
      Driveright.write(DrightStop - Speed);
      break;
    case 2:
      //Pivot left
      Driveleft.write(DleftStop + Speed);
      Driveright.write(DrightStop + Speed);
      break;
    case 3:
      //Pivot right
      Driveleft.write(DleftStop - Speed);
      Driveright.write(DrightStop - Speed);
      break;
    case -1:
      //do something when var equals 1
      Driveleft.write(DleftStop - Speed);
      Driveright.write(DrightStop + Speed);
      break;
    default:
      break;
  }
}


void boxcar_addValue(int add, struct boxcar *data) {

  if (data-> index == MovingAverageWidth) {
    data-> index = 0;
    data->vals[data-> index] = add;
  } else {
    data-> index++;
    data->vals[data-> index] = add;
  }
}


int boxcarGetAverage(struct boxcar *data) {
  int mean = 0;
  for (int i = 0; i < MovingAverageWidth; i++) {
    mean = mean + data->vals[i];
  }
  return mean;
}

struct w calculateWall(int xnaught, int xone,  struct w wall) {
  double alpha = xone * sin(sweepangle);
  double beta  = ((xnaught + xone * cos(sweepangle)) / alpha);
  double angle =  atan(beta);
  wall.theta = (90 - sweepangle) + ((angle * 4068) / 71);
  wall.CMDist = xone * sin(angle);
  return wall;
}



