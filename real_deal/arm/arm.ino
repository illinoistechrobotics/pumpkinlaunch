#define SerComm Serial1
#define TX_INT 50
#define A_INT 0
#define Z_INT 1
#define _GCB(b) (control_bits & (1 << (b)))
#define _CCB(b) (control_bits &= ~(1<<((b) & 0x01)));
#define _SCB(b) (control_bits |= (1<<((b) & 0x01)));
/*
Control Bits:
 0: Fire command issued
 1: ISR_A registration and calculations confirmed
 2: Release enable
 3: Release mechanism triggered
 
 */
uint8_t control_bits=0;
uint16_t ticks,releasetick;
long period=millis(),txtime=millis();
int rpm;
int calcTick(){
  //Calculate and return tick at which release is to occur at 

}
void fire(){
  //stuff to actually fire goes here 

}
void ISR_Z(){
  rpm=1/((millis()-period)/1000)/60;
  period=millis();
  if(_GCB(1)){
    //Launch parameters are ready! Enable Release!
    ticks=0;
    _SCB(2)
    }
    //We have a fire command! Attach the A_Interrupt!
    if(_GCB(0)&&(!_GCB(1))){
      attachInterrupt(A_INT,ISR_A,RISING);
      releasetick=calcTick();
      _SCB(1);
    }
}
void ISR_A(){
  ticks++;
  if((ticks >= releasetick) && _GCB(2)){
    fire();
    _SCB(3);
    detachInterrupt(A_INT);
    _CCB(2);
    _CCB(1);
  }
}

void setup(){
  attachInterrupt(Z_INT,ISR_Z,RISING);
#ifdef DEBUG
  SerComm.begin(57600);
#endif
}
void loop(){
  if((millis()-txtime)>TX_INT){
    SerComm.print('S');
    SerComm.write(control_bits);
    SerComm.println(rpm);
    txtime=millis();
  }
  if(SerComm.available()&&!_GCB(0)){
    if(SerComm.read()=='F'){
      _SCB(0);
    }
  }
}



