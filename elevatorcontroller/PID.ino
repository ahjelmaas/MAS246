// PID controller
double Kp = 0.6;


// initialize values for the PID controller
unsigned long curTime, prevtime;
double elapsedTime;
double error, cumulError, rateError;
double lastError;
double output, setPoint;

double computePID(double input) {
  curTime = millis();
  elapsedTime = (double)(curTime - prevtime);
  error = setPoint - input;
  cumulError += error * elapsedTime;
  rateError = (error - lastError) / elapsedTime;
  double out = Kp * error ;
  lastError = error;
  prevtime = curTime;
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
  Serial.print(abs(dist * (rotation/7)));
  Serial.print(",");
  Serial.print("Output:");
  Serial.println(counter);
 
}

//finne ut av 0-7, treffe 0 og treffe 7, for å treffe verdiene mellom, dele hver verdi på 7 
//sette at 7 etasje er max verdi
