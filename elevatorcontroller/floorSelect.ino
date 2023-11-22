// Enumeration for elevator direction
enum ElevatorDirection {
  UP,
  DOWN,
  STOP
};
// Variable to store the current elevator direction
ElevatorDirection elevatorDirection = STOP;

void gotoFloor() {
  for (int i = 0; i < 8; i++) { //
    if (digitalRead(sw[i]) == HIGH) {
      requestedF = i;

      // Checks if the elevator is currently on the requested floor
      if(requestedF == currentF){
        lcd.clear();
        lcd.print("Already on Floor");
        delay(2000);
        lcd.clear();
        return;
      }

      // Check if there are requests in the same direction
      if ((elevatorDirection == UP && requestedF > currentF) ||
          (elevatorDirection == DOWN && requestedF < currentF)) {
        lcd.clear();
        lcd.print("Cannot change direction");
        delay(2000);
        lcd.clear();
        return;
      }

      dist = currentF - requestedF;
      setPoint = abs(rotation/7 * dist);

      // Check if the doors are closed before moving
      if (doorState != CLOSED) {
        lcd.clear();
        lcd.print("Doors must be");
        lcd.setCursor(0,1);
        lcd.print("closed");
        delay(2000);
        lcd.clear();
        return;
      }

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
      delay(5000); // delay for closing doors
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
  
  while (counter < rotation/7 * abs(dist)) { //change the number rotation is divided by to equal number of floors -1
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
  int simulatedFloor = map(sensorValue, 0, 1023, 0, 7); //change 7 to be equal to number of buttons -1

  if (simulatedFloor >= 0 && simulatedFloor <= 7) { //change <= 7 to be equal to top floor
    requestedF = simulatedFloor;
    dist = currentF - requestedF;
    setPoint = abs(rotation/7 * dist); //change the number rotation is divided by to equal number of floors -1

    // Check if there are requests in the same direction
      if ((elevatorDirection == UP && requestedF > currentF) ||
          (elevatorDirection == DOWN && requestedF < currentF)) {
        lcd.clear();
        lcd.print("Cannot change direction");
        delay(2000);
        lcd.clear();
        return;
      }

    // Check if the doors are closed before moving
      if (doorState != CLOSED) {
        lcd.clear();
        lcd.print("Doors must be");
        lcd.setCursor(0,1);
        lcd.print("closed");
        delay(2000);
        lcd.clear();
        return;
      }


    if (dist < 0 && currentF > 0) {
      // Move DOWN if not on floor 0
      DCmotorCW();
    } else if (dist > 0 && currentF < 7) {// change <7 to be equal to top floor
      // Move UP if not on floor 7
      DCmotorCCW();
    }

    moveElevator();
    analogWrite(pwm_signal, 0);
    lcd.clear();
    lcd.print("Opening Doors");
    openDoor();
    delay(5000); // delay for closing doors
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
  int simulatedFloor = map(sensorValue, 0, 1023, 0, 7); //change 7 to be equal to number of buttons -1

  if (joystickValue > 900) {
    if(simulatedFloor == 7){ //disables up button for 7th floor, change as needed for top floor
      return;
    }
    respondToBatSignal();
    //restrict next elevator movement to move UP 
    
  }
  if (joystickValue < 100) {
    if(simulatedFloor == 0){ // disables down button for 0th floor
      return;
    }
    respondToBatSignal();
    //restruct next elevator movement to move DOWN
    
  }
}
