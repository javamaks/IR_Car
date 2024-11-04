
int in1 = 11;
int in2 = 10;
int in3 = 9;
int in4 = 8;


#define IR_1    0xA2
#define IR_2    0x62
#define IR_3    0xE2
#define IR_4    0x22
#define IR_5    0x2
#define IR_6    0xC2
#define IR_7    0xE0
#define IR_8    0xA8
#define IR_9    0x90
#define IR_STAR 0x68
#define IR_0    0x98
#define IR_HASH 0xB0
#define IR_UP   0x18
#define IR_LEFT 0x10
#define IR_OK   0x38
#define IR_RIGHT 0x5A
#define IR_DOWN 0x4A

#include <NecDecoder.h>
NecDecoder ir;

int currentCommand = 0;  
unsigned long lastCommandTime = 0; 
const unsigned long commandTimeout = 300; 
void setup() {
  Serial.begin(9600);
  attachInterrupt(0, irIsr, FALLING);

 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void irIsr() {
  ir.tick();
}

void loop() {
  if (ir.available()) {
    currentCommand = ir.readCommand(); 
    lastCommandTime = millis();        
    Serial.print("Received command: ");
    Serial.println(currentCommand, HEX);
  }

  
  if (millis() - lastCommandTime > commandTimeout) {
    stopMotors(); 
    currentCommand = 0;
  } else {
    switch (currentCommand) {
      case IR_UP: 
        moveForward();
        break;
      case IR_DOWN: 
        moveBackward();
        break;
      case IR_LEFT: 
        turnLeft();
        break;
      case IR_RIGHT: 
        turnRight();
        break;
      case IR_OK: 
        stopMotors();
        currentCommand = 0; 
        break;
      default:
        stopMotors();
    }
  }
}

void moveForward() {
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);
}


void moveBackward() {
  digitalWrite(in1, LOW);   
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);   
  digitalWrite(in4, HIGH);
}


void turnLeft() {
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);
}


void turnRight() {
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);   
  digitalWrite(in4, HIGH);
}


void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

