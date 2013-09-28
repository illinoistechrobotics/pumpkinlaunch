#define A_INT 0
#define Z_INT 1
/*
Control Bits:
0: Fire command issued
1: ISR_A registration confirmed
2: Release enable
3: Release mechanism triggered

*/
uint8_t control_bits;
uint16_t ticks=0,releasetick;
uint8_t getControlBit(uint8_t i){
  return (control_bits >> i)&0x01;
}
void setControlBit(uint8_t i){
  control_bits |= (1<<(i&0x01));
}
void clearControlBit(uint8_t i){
control_bits &= ~(1<<(i&0x01));
}
void ISR_Z(){
  //We have a fire command! Attach the A_Interrupt!
  if(getControlBit(0)&&(!getControlBit(1))){
    attachInterrupt(A_INT,ISR_A,RISING);
  }
}
void ISR_A(){
  ticks++;
  if(ticks >= releasetick){
    fire();
    setControlBit(3);
  }
}
void fire(){
 //stuff to actually fire goes here 
}
void setup(){
  attachInterrupt(Z_INT,ISR_Z,RISING);
}
void loop(){
  //Detatch interrupt if fire command bit is cleared
  if(!getControlBit(0)){
         detachInterrupt(A_INT);
  }
}
  
  
