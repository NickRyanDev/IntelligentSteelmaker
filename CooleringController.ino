#define LED1 12
#define LED2 13
#define MOTOR 7
#define CHANNELA 2
#define SWITCH 8

const int motorStts = 9;

volatile int pulseCount = 0;
volatile byte state = LOW;

void countPulse(){
	pulseCount++;
}

void motor(){
	state = !state;
}

bool motorStatus(){
  noInterrupts();
  int pulses = pulseCount;
  pulseCount = 0;
  interrupts();
  
  if(pulses>=20){
    return true;
  }
    return false;
}

bool changeMotorStatus(){
  noInterrupts();
  bool statusMotor = state;
  interrupts();
  
  return statusMotor;
}


void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(motorStts, OUTPUT);
  pinMode(SWITCH, OUTPUT);
  
  pinMode(MOTOR, INPUT);
  attachInterrupt(digitalPinToInterrupt(MOTOR),motor, CHANGE);
  
  pinMode(CHANNELA, INPUT);
  attachInterrupt(digitalPinToInterrupt(CHANNELA),countPulse, RISING);
  
}


void loop()
{
  bool motorOn = changeMotorStatus();
  bool motorState = motorStatus();
  if((motorOn == true) & (motorState == true)){
  	digitalWrite(SWITCH, HIGH);
    digitalWrite(motorStts, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
  }
  else{
  	digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(motorStts, LOW);
    digitalWrite(SWITCH, LOW);
  }
}