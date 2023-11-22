
unsigned long displayStartTime = 0;
unsigned long delayDuration = 5000;
bool clearLCD = true;  // Flag to control whether to clear the LCD

void displayFloor() {
  const char* floorNames[] = {//change floor name as needed
    "Batcave",
    "Guest Entrance",
    "Man Cave",
    "Kitchen",
    "Mechatronics Lab",
    "Floor 69",
    "Honeymoon Suite",
    "Penthouse"
  };

  lcd.setCursor(0, 0);
  lcd.print(floorNames[currentF]);

  int sensorValue = analogRead(callLift);

  // Map the sensor value to a floor index
  int simulatedFloor = map(sensorValue, 0, 1023, 0, 7); //change 7 to be equal to number of floors -1

  lcd.setCursor(0, 1);
  lcd.print("SimulatedFloor:");
  lcd.print(simulatedFloor);

  displayStartTime = millis();
  clearLCD = true;

  for (int i = 0; i < 8; i++) {//change the size of this array to match number of floors
    if (digitalRead(sw[i]) == HIGH) {
      lcd.clear();
      lcd.print("Closing doors");

      lcd.clear();
      lcd.print("Moving to");
      lcd.setCursor(0, 1);
      lcd.print(floorNames[i]);
   
 // Do not clear the LCD after button press

      break; // Exit the loop after handling the button press
    }
  }

 
}
