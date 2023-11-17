void gotoFloor() {
  for (int i = 0; i < 8; i++) {
    if (digitalRead(sw[i]) == HIGH) {
      requestedF = i;
      
      if(requestedF == currentF){
        lcd.clear();
        lcd.print("Already on Floor");
        delay(2000);
        lcd.clear();
        return;
      }
      dist = currentF - requestedF;
      setPoint = abs(rotation * dist);

      // closeDoor();

      if (dist < 0) {
        DCmotorCW();
      } else if (dist > 0) {
        DCmotorCCW();
      }

      moveElevator();
      analogWrite(pwm_signal, 0);
      lcd.clear();
      lcd.print("Opening Doors");
      openDoor();
      delay(5000);
      lcd.clear();
      lcd.print("Closing Doors");
      closeDoor();
      delay(1500);
      lcd.clear();

      currentF = requestedF;
      setPoint = 0;
      counter = 0;

      break; // Exit the loop after handling the button press
    }
  }
}

void moveElevator() {
  // Ensure counter is updated in this function
  while (counter < rotation * abs(dist)) {
    output = computePID(counter);
    delay(10); // A delay to ensure the microcontroller can read the signals

    // Update counter here
    counter += 1;  // You might need to adjust this based on your system's requirements

    analogWrite(pwm_signal, output);
    PIDplot();
  }
}


void respondToBatSignal() {
  int sensorValue = analogRead(callLift);

  // Map the sensor value to a floor index
  int simulatedFloor = map(sensorValue, 0, 1023, 0, 7);

  if (simulatedFloor >= 0 && simulatedFloor <= 7) {
    requestedF = simulatedFloor;
    dist = currentF - requestedF;
    setPoint = abs(rotation * dist);

    // closeDoor();

    if (dist < 0 && currentF > 0) {
      // Move DOWN if not on floor 0
      DCmotorCW();
    } else if (dist > 0 && currentF < 7) {
      // Move UP if not on floor 7
      DCmotorCCW();
    }

    moveElevator();
    analogWrite(pwm_signal, 0);
    lcd.clear();
    lcd.print("Opening Doors");
    openDoor();
    delay(5000);
    lcd.clear();
    lcd.print("Closing Doors");
    closeDoor();
    delay(1500);
    lcd.clear();
    stopMotor();

    currentF = requestedF;
    setPoint = 0;
    counter = 0;
    
  }
}

void upOrDown() {
  int joystickValue = analogRead(VERT); // joystickValue >= 900 means up button is pressed
  int sensorValue = analogRead(callLift);

  // Map the sensor value to a floor index
  int simulatedFloor = map(sensorValue, 0, 1023, 0, 7);

  if (joystickValue > 900) {
    if(simulatedFloor == 7){
      return;
    }
    respondToBatSignal();
    //restrict next elevator movement to move UP 
    
  }
  if (joystickValue < 100) {
    respondToBatSignal();
    //restruct next elevator movement to move DOWN
    
  }
}
