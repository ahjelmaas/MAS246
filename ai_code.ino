#include <dac.h>
#define rotation 2100

int Switch[8] = {0};

// Step motor - doors
int A = 69;
int A_phase = 68;
int B = 67;
int B_phase = 66;
int stepsRev = 200; // 1/2 rotation

// DC motor - floors
int motorspeed = 255;
int enable = 7;
int phase = 6;
int decay = 5;

// Encoder
const byte encoderPinA = 20;
const byte encoderPinB = 21;
volatile long encoderPos = 0;
volatile boolean A_set = true;
volatile boolean B_set = true;

// Define movement
int currentf = 0;
int requiredf;
int distance = 0;

// Function for indicating floor lights
void floorlights() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(49 - i, (currentf == i) ? HIGH : LOW);
  }
}

void setup() {
  // Doors
  pinMode(A, OUTPUT);
  pinMode(A_phase, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(B_phase, OUTPUT);
  dac_init();
  set_dac(4095, 4095);

  // DC motor
  pinMode(enable, OUTPUT);
  pinMode(phase, OUTPUT);
  pinMode(decay, OUTPUT);
  digitalWrite(decay, LOW);

  // Floor switches
  for (int i = 0; i < 8; i++)
    Switch[i] = 22 + i;

  // Encoder
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  // ISR (Interrupt service routine)
  // attachInterrupt(digitalPinToInterrupt(encoderPinA), doSignal, CHANGE);
}

// Function to stop the elevator
void stopElevator() {
  digitalWrite(enable, LOW);
  delay(500);
}

// Winding or unwinding
void DCmotorCW() {
  digitalWrite(phase, LOW);
  digitalWrite(decay, LOW);
}

void DCmotorCCW() {
  digitalWrite(phase, HIGH);
  digitalWrite(decay, LOW);
}

// Function for door opening
void doorOpen() {
  for (int i = 0; i < stepsRev / 8; i++) {
    digitalWrite(A, HIGH); // Step 1
    digitalWrite(A_phase, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_phase, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, LOW); // Step 2
    digitalWrite(A_phase, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_phase, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH); // Step 3
    digitalWrite(A_phase, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(B_phase, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH); // Step 4
    digitalWrite(A_phase, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(B_phase, LOW);
    delayMicroseconds(2500);
  }
}

void stepphalv() {
  for (int i = 0; i < stepsRev / 8; i++) {
    digitalWrite(A, HIGH);
    digitalWrite(A_phase, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_phase, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, LOW);
    digitalWrite(A_phase, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_phase, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);
    digitalWrite(A_phase, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(B_phase, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);
    digitalWrite(A_phase, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(B_phase, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);
    digitalWrite(A_phase, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(B_phase, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, LOW);
    digitalWrite(A_phase, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_phase, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);
    digitalWrite(A_phase, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_phase, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);
    digitalWrite(A_phase, LOW);
    digitalWrite(B, LOW);
    digitalWrite(B_phase, LOW);
    delayMicroseconds(2500);
  }
}

void loop() {
  floorlights(); // Update floor lights

  // Check for button presses to request going up or down
  for (int i = 0; i < 8; i++) {
    if (digitalRead(Switch[i]) == HIGH) {
      requiredf = i;
      distance = currentf - requiredf;

      if (distance > 0) {
        DCmotorCCW(); // Move down
      } else if (distance < 0) {
        DCmotorCW(); // Move up
      } else {
        stopElevator(); // Stop if already at the requested floor
        continue; // Skip the movement if already at the requested floor
      }

      analogWrite(enable, motorspeed);
      delay(3000);
      stopElevator(); // Stop the elevator
      currentf = requiredf; // Update the current
    }
  }
}
