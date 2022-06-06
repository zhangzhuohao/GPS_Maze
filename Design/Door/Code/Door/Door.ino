#define dir1Pin 4
#define pul1Pin 5
#define dir2Pin 8
#define pul2Pin 9
#define signalPin 10
#define control1Pin 2
#define control2Pin 3
#define stepsPerRevolution 1600 // slide door
#define stepsPerQuarter 3200 // double door
// 6 mm per revolution

int dir1 = HIGH, dir2 = LOW;
int var1 = 1, var2 = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(dir1Pin, OUTPUT);
  pinMode(pul1Pin, OUTPUT);
  pinMode(control1Pin, INPUT_PULLUP);
  pinMode(dir2Pin, OUTPUT);
  pinMode(pul2Pin, OUTPUT);
  pinMode(control2Pin, INPUT_PULLUP);
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);
  
  Serial.begin(9600);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  var1 = digitalRead(control1Pin);
  if(var1==0) {
    delay(50);
    var1 = digitalRead(control1Pin);
    if(var1==0) {
      if(dir1==HIGH) {
        digitalWrite(signalPin, HIGH);
        delay(500);
      }
      doubleDoorMove(dir1, stepsPerQuarter, dir1Pin, pul1Pin);
      dir1 = 1 - dir1;
      delay(480);
      digitalWrite(signalPin, LOW);
    }
  }
  
  var2 = digitalRead(control2Pin);
  if(var2==0) {
    delay(50);
    var2 = digitalRead(control2Pin);
    if(var2==0) {
      if(dir2==LOW) {
        digitalWrite(signalPin, HIGH);
        delay(500);
      }
      slideDoorMove(dir2, stepsPerRevolution, dir2Pin, pul2Pin);
      dir2 = 1 - dir2;
      digitalWrite(signalPin, LOW);
    }
  }
}

void slideDoorMove(int DIR, int STEPS, int DIRPIN, int PULPIN) {
  digitalWrite(DIRPIN, DIR);
  for(int i=0; i<12*STEPS; i++) {
    digitalWrite(PULPIN, HIGH);
    delayMicroseconds(25);
    digitalWrite(PULPIN, LOW);
    delayMicroseconds(25);
  }
  for(int i=0; i<12*STEPS; i++) {
    digitalWrite(PULPIN, HIGH);
    delayMicroseconds(25);
    digitalWrite(PULPIN, LOW);
    delayMicroseconds(25);
  }
} // 1.92s : 14.4cm.

void doubleDoorMove(int DIR, int STEPS, int DIRPIN, int PULPIN) {
  digitalWrite(DIRPIN, DIR);
  for(int i=0; i<STEPS; i++) {
    digitalWrite(PULPIN, HIGH);
    delayMicroseconds(50);
    digitalWrite(PULPIN, LOW);
    delayMicroseconds(50);
  }
} // 0.32s : 90°.
