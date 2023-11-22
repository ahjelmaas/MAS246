
#include <LiquidCrystal.h>
#include <dac.h>
#define rotation 15020 // max rotations, distance from floor 0 to floor 7



int sw[8] = {0}; //change the size of this array to match number of buttons in the elevator cabin

// initializing analog sensors
const int VERT = A2; // analog
int vertical;
int callLift = A0;

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

// initialize values for elevator position at startup
int currentF = 0;
int requestedF;
int dist = 0;




LiquidCrystal lcd(41,40,37,36,35,34);

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
  for(int i=0; i<8; i++) //change the size of this array to match number of buttons in the elevator cabin
    sw[i] = 22+i;

  // Set DC motor pins to output
  pinMode(DC_phase,OUTPUT);
  pinMode(DC_decay,OUTPUT);
  pinMode(pwm_signal,OUTPUT);

  // Go into the "updateEncoder" function each time one encoder interrupts change signal
  attachInterrupt(3, updateEncoder, CHANGE);

  int LCD_Backlight =4;
  pinMode(LCD_Backlight, OUTPUT);
  analogWrite(LCD_Backlight, 128);
  lcd.begin(16,2);
}





void loop() {

  

  floorlights();

  gotoFloor();

  displayFloor();

  // callElevator();
  upOrDown();



}
