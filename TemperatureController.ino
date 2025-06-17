#define LED1 2
#define LED2 4
#define MOTOR 7
#define TEMPERATURELIMIT 100

const int processTempSensor = A0;

int processTempCelcius = 0;
const int motorStatus = 9;
int motorState = LOW;
volatile bool state = false;

void status()
{
	state = !state;
}

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(motorStatus, INPUT);
  pinMode(processTempSensor, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(motorStatus), status, CHANGE);
  Serial.begin(9600);
}

void loop()
{
  motorState = getMotorStatus();
  processTempCelcius = getTemperature();
  if(processTempCelcius > TEMPERATURELIMIT ){
    digitalWrite(MOTOR, HIGH);
    delay(50);
    if (motorStatus==HIGH){
      digitalWrite(LED2, HIGH);
    }
  }
  if((processTempCelcius > TEMPERATURELIMIT) & (motorState==LOW)){
    digitalWrite(LED1, HIGH);
    Serial.println("Processo parado");
  }
  if((processTempCelcius > TEMPERATURELIMIT) & (motorState==HIGH)){
    digitalWrite(LED2, HIGH);
  }
  if((processTempCelcius <= TEMPERATURELIMIT) & (motorState==LOW)){
    digitalWrite(LED2, HIGH);
  }
  else{
  	digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  	digitalWrite(MOTOR, LOW);
  }
  
}
float getTemperature(){
  return map(((analogRead(processTempSensor) - 20) * 3,04), 0, 1023, -40, 125);
}
int getMotorStatus(){
  noInterrupts();
  int statusMotor = state;
  interrupts();
  return statusMotor;
}
