#include <Servo.h>

char buf[128];
long safetime=millis();
int pwr=0;
char startb = '@';
char endb = '#';
int startloc=-1;
int endloc=-1;
boolean cmdcomplete=false;
Servo vic;
int y=0;
int i;
char in[32];
int length;
char nb=NULL;
char out[32];
void setup(){
  Serial1.begin(57600);
  //Serial.begin(57600);
  vic.attach(11);
}
void xbee_read() {
  while(Serial1.available() > 0){
    buf[y]=Serial1.read();
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
    pwr=atoi(out);
    if(pwr>0){
      pwr+=40;
    }
    constrain(pwr,0,500);
    memset(out,nb,32);
  }
  else {
    out[0] = nb;
}
}
void loop(){
    xbee_read();
    // Gotta have a failsafe :)
    if(millis()-safetime<200){
      //Serial.println(pwr);
      vic.writeMicroseconds(1500+pwr);
    } else {
      //Serial.println("safe");
      vic.writeMicroseconds(1500);
    }
    //delay(5);
 // }
}
