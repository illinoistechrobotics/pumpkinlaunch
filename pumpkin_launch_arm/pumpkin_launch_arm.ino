#include <Servo.h>
#define LAUNCH_ANGLE_RADIANS 3.141
char buf[128];
long safetime=millis();
boolean trip=false;
int pwr=0;
float omega=0;
char startb = '@';
char endb = '#';
int startloc=-1;
int endloc=-1;
boolean cmdcomplete=false;
boolean fire=false, hold=true;
Servo vic;
int y=0;
int i;
char in[32];
int length;
char fireseq[] = "$$$";
char nb=NULL;
char out[32];
long breaktime=millis();

void setup(){
  Serial.begin(57600);
  //Serial.begin(57600);
  vic.attach(10);
  vic.writeMicroseconds(1500);
}
void xbee_read() {
  while(Serial.available() > 0){
    buf[y]=Serial.read();
    y++;
  }
  if(startloc==-1){
  for(i=0;i<y;i++){
    if(buf[i]==startb){
  //    Serial.println("START");
      startloc=i;
      break;
    }
  }
  }
  else{
  for(i=startloc;i<y;i++){
    if(buf[i]==endb){
   //   Serial.println("END");
      endloc=i;
      cmdcomplete=true;
      break;
    }
  }
  }
  if(cmdcomplete){
    length=(endloc-startloc)-1;
   //Serial.println(length);
   memcpy(&out[0],&buf[startloc+1],length);
   //memset(buf,nb,128);
     out[length+1]=nb;
    startloc=-1;
    endloc=-1;
    cmdcomplete=false;
    safetime=millis();
    y=0;
   // Serial.println(out);
   if(length == 3 && strcmp(out,fireseq) == 0){
     fire=true;
   }
    memset(out,nb,32);
  }
  else {
    out[0] = nb;
}
}
float calc_rps(){
 float rps;
 rps = (1000 / (millis()-breaktime))*2*PI; // 1 over period x 2PI
 breaktime=millis();
 return rps; 
}
void fire_action() {
  // Serial.println("Fire Success");
       vic.writeMicroseconds(2000);
       delay(500);
       vic.writeMicroseconds(1500);
       hold=false;
       fire=false;
}
void loop(){
  if(analogRead(A7)>230 && !trip){
  omega=calc_rps();
  trip = true;
  }
  if(analogRead(A7)<200){
    trip=false;
  }
  if(hold){
   vic.writeMicroseconds(1300); 
  }
    xbee_read();
    // Gotta have a failsafe :)
    if(fire){
     // Serial.println("Firing attempt");
     // Attempt to fire
     if(analogRead(A7)>230){
      
     }
    }
    //delay(5);
 // }
}
