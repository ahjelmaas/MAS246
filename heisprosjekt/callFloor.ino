void floorCall(){
  human = analogRead(callLift);
  vertical = analogRead(VERT);

  if(human < 100){
    if (digitalRead(sw[0]) == HIGH){
      requestedF = 0;
      dist = currentF - requestedF;
      setPoint = abs(rotation*dist);
    // dist = currentF - requestedF;
    // setPoint = abs(rotation*dist);
    
   // will be 0-1023
    if(vertical > 900){
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

    
    // if(vertical < 100){
        //brukes ikke i ground floor
    // }
  }
  // Serial.print("vertical: ");
  // Serial.print(vertical, DEC);
  // Serial.print("human:");
  // Serial.print(human,DEC);
}
// if(digitalRead(sw[0]) == HIGH){
//     requestedF = 0;
//     dist = currentF - requestedF;
//     setPoint = abs(rotation*dist);

//     // the steppmotor functions in if statement because won't trigger if button press is same floor as elevator
//     if(dist < 0){
//       stepphalv(); // closes elevator door
//       DCmotorCW(); 
//       while(counter < rotation*abs(dist)){
//         output = computePID(counter); 
//         delay(10);    // a delay here is used to make sure the microcontroller can read the signals
//         analogWrite(pwm_signal, output);
//         PIDplot();
//       }
//       analogWrite(pwm_signal, 0);
//       stepphalvu(); // opens elevator doors

//     } 
//     // after the elevator is done moving we reset counter and setPoint for later use and changes our current floor
//     currentF = requestedF;
//     setPoint = 0;
//     counter = 0;
//   }