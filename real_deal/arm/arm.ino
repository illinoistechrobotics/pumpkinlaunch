#define SerComm Serial
#define TX_INT 100
#define A_INT 0
#define Z_INT 1
#define FIRE_PIN 5
#define _GET_CONTROL_BIT(b) (control_bits & (1 << (b)))
#define _CLEAR_CONTROL_BIT(b) (control_bits &= ~(1<<(b)));
#define _SET_CONTROL_BIT(b) (control_bits |= (1<<(b)));
#define FIRE_COMMAND_ISSUED 0
#define ISR_SET_AND_CALCULATED 1
#define RELEASE_ENABLE 2
#define RELEASE_TRIGGERED 3
//In case a tick is missed, still launch accurately
#define ENCODER_TICKS 499
/*
   Control Bits:
0: Fire command issued
1: ISR_A registration and calculations confirmed
2: Release enable
3: Release mechanism triggered

 */
volatile uint8_t control_bits=0;
volatile uint16_t ticks,releasetick;
volatile unsigned long period=0,txtime=0;
volatile unsigned long mpr=60000; //millis per revolution
volatile float A, B;
int calcTick(int r){
	//Calculate and return tick at which release is to occur at 
	//return 210; //- 1/10 * rpm
        return (int)(A*r + B) % ENCODER_TICKS;
}
void fire(){
	digitalWrite(FIRE_PIN,HIGH);
}
void ISR_Z(){
	mpr = millis() - period;
	period = millis();
	if(_GET_CONTROL_BIT(ISR_SET_AND_CALCULATED)){
		//Launch parameters are ready! Enable Release!
		ticks=0;
		_SET_CONTROL_BIT(RELEASE_ENABLE)
	}
}
void ISR_A(){
	ticks++;
	if((ticks >= releasetick) && _GET_CONTROL_BIT(RELEASE_ENABLE)){
		fire();
		_SET_CONTROL_BIT(RELEASE_TRIGGERED);
		detachInterrupt(A_INT);
		SerComm.begin(9600);
		_CLEAR_CONTROL_BIT(RELEASE_ENABLE);
		_CLEAR_CONTROL_BIT(ISR_SET_AND_CALCULATED);
	}
}
void setup(){
        int go = 0;
        char inc;
	SerComm.begin(9600);
	digitalWrite(FIRE_PIN,LOW);
	pinMode(FIRE_PIN,OUTPUT);
        //Wait for a return 
        while(go==0){
          if(SerComm.available()){
            inc=SerComm.read();
            if(inc == '\n'){
               go=1;
            }
          }
        }
        //Print prompt
        SerComm.setTimeout(0xffffffff);
        SerComm.println("ReleaseTick = A * RPM + B");
        SerComm.print("A=");
        A=SerComm.parseFloat();
        SerComm.println();
        SerComm.print("B=");
        B=SerComm.parseFloat();
        SerComm.println();
        SerComm.print("ReleaseTick = ");
        SerComm.print(A);
        SerComm.print(" * RPM + ");
        SerComm.println(B);
        delay(2000);
        
        attachInterrupt(Z_INT,ISR_Z,RISING); 
             
}
void loop(){
	int rpm  = 60000 / mpr; // 60000 = 1000 milliseconds * 60 seconds
	if((millis()-txtime)>TX_INT){
		SerComm.print('S');
		SerComm.print(control_bits,BIN);
		SerComm.print(" R ");
		SerComm.println(rpm);
                SerComm.print("\r\n");
		txtime=millis();
	}
	if(SerComm.available()&&!_GET_CONTROL_BIT(FIRE_COMMAND_ISSUED)){
		if(SerComm.read()=='|'){
			_SET_CONTROL_BIT(FIRE_COMMAND_ISSUED);
		}
	}
	//We have a fire command! Attach the A_Interrupt!
	if(_GET_CONTROL_BIT(FIRE_COMMAND_ISSUED)&&(!_GET_CONTROL_BIT(ISR_SET_AND_CALCULATED))){
		//calculate RPM here
		releasetick=calcTick(rpm);
		SerComm.println(releasetick);
                SerComm.print("\r\n");
		SerComm.end();
		attachInterrupt(A_INT,ISR_A,RISING);
		_SET_CONTROL_BIT(ISR_SET_AND_CALCULATED);
	}
}



