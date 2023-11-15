#include <dac.h>
#define rotation 2100
int sw[8] = {0};

// initialize values for DC motor
int pwm_signal = 7;
int DC_phase = 6;
int DC_decay = 5;

// initialize values for the encoder
int CLK = 20;
int DT = 21;
int formerCLK;
int counter = 0;

//initialize values for the steppmotor
int A = 69;
int phase_A =  68;
int B = 67;
int phase_B = 66;
int max_stepp = 400; // one revolution

// initialize values for the PID controller
unsigned long crnttime, prevtime;
double elapsedtime;
double error, cumerror, rateerror;
double lasterror;
double output, setpoint;

// initialize values for floor position
int curfloor = 0;
int reqfloor;
int dist = 0;

void setup() {
  Serial.begin(9600);

  // Stepmotor variable declaration
  pinMode(phase_A, OUTPUT);
  pinMode(phase_B, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  dac_init();
  set_dac(4095,4095);

  // makes an array for the switches
  for(int i=0; i<8; i++)
    sw[i] = 22+i;

  // Set DC motor pins to output
  pinMode(DC_phase,OUTPUT);
  pinMode(DC_decay,OUTPUT);
  pinMode(pwm_signal,OUTPUT);

  // Go into the "updateEncoder" function each time one encoder interrupts change signal
  attachInterrupt(3, updateEncoder, CHANGE);

}
// function to increment each time an interrupt signal changes in value
void updateEncoder(){
  int currentCLK = digitalRead(CLK);
  int currentDT = digitalRead(DT);
  // String currentDIR = "";
  if(currentCLK != formerCLK && currentCLK ==1){
   if(digitalRead(DT) != currentCLK){
     counter++;
    //  currentDIR ="CW";
   } else {
     counter++;
    //  currentDIR = "CCW";
     }
  }
  formerCLK = currentCLK;
}
// code for determining direction for DCmotor
void DCmotorCW() {
  digitalWrite(DC_phase, LOW);
  digitalWrite(DC_decay, LOW);
}
void DCmotorCCW() {
  digitalWrite(DC_phase, HIGH);
  digitalWrite(DC_decay, LOW);
}

// function for door opening
void stepphalv(){
  for (int i=0; i<max_stepp/8; i++){
    digitalWrite(A, HIGH);
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, LOW);
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);
    
    digitalWrite(A, HIGH);
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);
    
    digitalWrite(A, HIGH);
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, LOW);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);
    
    digitalWrite(A, HIGH);
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, LOW);
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);
    
    digitalWrite(A, HIGH);
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);
    digitalWrite(phase_A,LOW);
    digitalWrite(B, LOW);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);   

  }
}
// function for door closing
void stepphalvu(){
  for (int i=0; i<max_stepp/8; i++){
    digitalWrite(A, HIGH);  // stepp 8
    digitalWrite(phase_A,LOW);
    digitalWrite(B, LOW);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500); 

    digitalWrite(A, HIGH);  // stepp 7
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, LOW); // stepp 6
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);  // stepp 5
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);  // stepp 4
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, LOW);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);  // stepp 3
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, LOW);   // stepp 2
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);    

    digitalWrite(A, HIGH);    // stepp 1
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);
  }
}

// function for indicating floor lights
void floorlights(){
  if(curfloor==0){
    digitalWrite(49,HIGH);
  } else{
    digitalWrite(49,LOW);
  } 
  if(curfloor==1){
    digitalWrite(48,HIGH);
  } else{
    digitalWrite(48,LOW);
  } 
  if(curfloor==2){
    digitalWrite(47,HIGH);
  } else{
    digitalWrite(47,LOW);
  } 
  if(curfloor==3){
    digitalWrite(46,HIGH);
  } else{
    digitalWrite(46,LOW);
  }
    if(curfloor==4){
    digitalWrite(45,HIGH);
  } else{
    digitalWrite(45,LOW);
  } 
  if(curfloor==5){
    digitalWrite(44,HIGH);
  } else{
    digitalWrite(44,LOW);
  } 
  if(curfloor==6){
    digitalWrite(43,HIGH);
  } else{
    digitalWrite(43,LOW);
  } 
  if(curfloor==7){
    digitalWrite(42,HIGH);
  } else{
    digitalWrite(42,LOW);
  } 
} 


// PID controller
double Kp = 0.2;

double computePID(double inp) {
  crnttime = millis();
  elapsedtime = (double)(crnttime - prevtime);
  error = setpoint - inp;
  cumerror += error * elapsedtime;
  rateerror = (error - lasterror) / elapsedtime;
  double out = Kp * error;
  lasterror = error;
  prevtime = crnttime;
  // if statement checks if the output is within target range 20-150 which controls the pwm_signal
  if (out < 20)
    out = 20;
  if (out > 150)
    out = 150;

  return out;
}

// function to see the PD controller using the serial plotter 
void PIDplot() {
  Serial.print("input:");
  Serial.print(abs(dist) * rotation);
  Serial.print(",");
  Serial.print("Output:");
  Serial.println(counter);
 
}


void loop() {
  floorlights();
 
  // if statement checks which button pressed, moves to wanted floor
  // CW for upward movement, CCW for downward movement
  // only the first if statement is documented for explanation
  if(digitalRead(sw[0]) == HIGH){
    reqfloor = 0;
    dist = curfloor - reqfloor;
    setpoint = abs(rotation*dist);

    // the steppmotor functions in if statement because won't trigger if button press is same floor as elevator
    if(dist < 0){
      stepphalv(); // closes elevator door
      DCmotorCW(); 
      while(counter < rotation*abs(dist)){
        output = computePID(counter); 
        delay(10);    // a delay here is used to make sure the microcontroller can read the signals
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu(); // opens elevator doors

    } else if (dist > 0) {
      stepphalv();
      DCmotorCCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu(); 
    }
    // after the elevator is done moving we reset counter and setpoint for later use and changes our current floor
    curfloor = reqfloor;
    setpoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[1]) == HIGH){
    reqfloor = 1;
    dist = curfloor - reqfloor;
    setpoint = abs(rotation*dist);

    if(dist < 0){
      stepphalv();
      DCmotorCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    }
    curfloor = reqfloor;
    setpoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[2]) == HIGH){
    reqfloor = 2;
    dist = curfloor - reqfloor;
    setpoint = abs(rotation*dist);

    if(dist < 0){
      stepphalv();
      DCmotorCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    } else if(dist > 0) {
      stepphalv();
      DCmotorCCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    }
    curfloor = reqfloor;
    setpoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[3]) == HIGH){
    reqfloor = 3;
    dist = curfloor - reqfloor;
    setpoint = abs(rotation*dist);

    if(dist < 0){
      stepphalv();
      DCmotorCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    } else if(dist > 0) {
      stepphalv();
      DCmotorCCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    }
    curfloor = reqfloor;
    setpoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[4]) == HIGH){
    reqfloor = 4;
    dist = curfloor - reqfloor;
    setpoint = abs(rotation*dist);

    if(dist < 0){
      stepphalv();
      DCmotorCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    } else if(dist > 0) {
      stepphalv();
      DCmotorCCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    }
    curfloor = reqfloor;
    setpoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[5]) == HIGH){
    reqfloor = 5;
    dist = curfloor - reqfloor;
    setpoint = abs(rotation*dist);

    if(dist < 0){
      stepphalv();
      DCmotorCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    } else if(dist > 0) {
      stepphalv();
      DCmotorCCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    }
    curfloor = reqfloor;
    setpoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[6]) == HIGH){
    reqfloor = 6;
    dist = curfloor - reqfloor;
    setpoint = abs(rotation*dist);

    if(dist < 0){
      stepphalv();
      DCmotorCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    } else if(dist > 0) {
      stepphalv();
      DCmotorCCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    }
    curfloor = reqfloor;
    setpoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[7]) == HIGH){
    reqfloor = 7;
    dist = curfloor - reqfloor;
    setpoint = abs(rotation*dist);

    if(dist < 0){
      stepphalv();
      DCmotorCW();
      while(counter <rotation*abs(dist)){
        output = computePID(counter);
        delay(10);
        analogWrite(pwm_signal, output);
        PIDplot();
      }
      analogWrite(pwm_signal, 0);
      stepphalvu();
    } 
     
    
    curfloor = reqfloor;
    setpoint = 0;
    counter = 0;
  }
}


