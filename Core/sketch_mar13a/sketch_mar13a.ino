#define sweepangle 45

struct w{
    int theta;
    int CMDist;
};

struct boxcar {
    int vals[3];
    int index;
    int delta;
};

 struct motors {
    int leftspeed;
    int rightspeed;
} ;

struct boxcar pings[1];
  struct w  walls[2];
    
  struct w calculateWall(int xnaught, int xone,  struct w wall){
    double alpha = xone * sin(sweepangle);
    double beta  =((xnaught + xone * cos(sweepangle))/alpha);
    double angle =  atan(beta);
    wall.theta = (90 - sweepangle) + ((angle * 4068) / 71);
    wall.CMDist = xone * sin(angle);
    return wall;
}

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);   

}

void loop() {
  // put your main code here, to run repeatedly:
    if(Serial.available() > 0) {
        int one = Serial.parseInt();
        int two = Serial.parseInt();
        walls[1] = calculateWall(one,two, walls[1]);
        Serial.println();
}
}






