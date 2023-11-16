void gotoFloor(){
  if(human > 800){
  if(digitalRead(sw[0]) == HIGH){
    requestedF = 0;
    dist = currentF - requestedF;
    setPoint = abs(rotation*dist);

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

    } 
    // after the elevator is done moving we reset counter and setPoint for later use and changes our current floor
    currentF = requestedF;
    setPoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[1]) == HIGH){
    requestedF = 1;
    dist = currentF - requestedF;
    setPoint = abs(rotation*dist);

    if(dist < 0){
      delay(1000);
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
    currentF = requestedF;
    setPoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[2]) == HIGH){
    requestedF = 2;
    dist = currentF - requestedF;
    setPoint = abs(rotation*dist);

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
    currentF = requestedF;
    setPoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[3]) == HIGH){
    requestedF = 3;
    dist = currentF - requestedF;
    setPoint = abs(rotation*dist);

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
    currentF = requestedF;
    setPoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[4]) == HIGH){
    requestedF = 4;
    dist = currentF - requestedF;
    setPoint = abs(rotation*dist);

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
    currentF = requestedF;
    setPoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[5]) == HIGH){
    requestedF = 5;
    dist = currentF - requestedF;
    setPoint = abs(rotation*dist);

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
    currentF = requestedF;
    setPoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[6]) == HIGH){
    requestedF = 6;
    dist = currentF - requestedF;
    setPoint = abs(rotation*dist);

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
    currentF = requestedF;
    setPoint = 0;
    counter = 0;
  }
  if(digitalRead(sw[7]) == HIGH){
    requestedF = 7;
    dist = currentF - requestedF;
    setPoint = abs(rotation*dist);

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
     
    
    currentF = requestedF;
    setPoint = 0;
    counter = 0;
  }
  }
}