 int LCD_Backlight = 4;
void displayFloor(){

  analogWrite(LCD_Backlight, 128);
  lcd.begin(16,2);
  lcd.clear();

  if(currentF==0){
    lcd.print("Batcave");
  }

  if(currentF==1){
    lcd.print("Guest Entrance");
  }

  if(currentF==2){
    lcd.print("Man Cave");
  }

  if(currentF==3){
    lcd.print("Kitchen");
  }

  if(currentF==4){
    lcd.print("Mechatronics Lab");
  }

  if(currentF==5){
    lcd.print("Floor 69");
  }

  if(currentF==6){
    lcd.print("Honeymoon Suite");
  }

  if(currentF==7){
    lcd.print("Penthouse");
  }


  // runs when the floor button is pressed
  if(digitalRead(sw[0]) == HIGH){
    lcd.clear();
    lcd.print("Moving to");
    lcd.setCursor(0,1);
    lcd.print("Batcave");
  }
  if(digitalRead(sw[1]) == HIGH){
    lcd.clear();
    lcd.print("Moving to");
    lcd.setCursor(0,1);
    lcd.print("Guest Entrance");
  }
  if(digitalRead(sw[2]) == HIGH){
    lcd.clear();
    lcd.print("Moving to");
    lcd.setCursor(0,1);
    lcd.print("Man Cave");
  }
  if(digitalRead(sw[3]) == HIGH){
    lcd.clear();
    lcd.print("Moving to");
    lcd.setCursor(0,1);
    lcd.print("Kitchen");
  }
  if(digitalRead(sw[4]) == HIGH){
    lcd.clear();
    lcd.print("Moving to");
    lcd.setCursor(0,1);
    lcd.print("Mechatronics Lab");
  }
  if(digitalRead(sw[5]) == HIGH){
    lcd.clear();
    lcd.print("Moving to");
    lcd.setCursor(0,1);
    lcd.print("Floor 69");
  }
  if(digitalRead(sw[6]) == HIGH){
    lcd.clear();
    lcd.print("Moving to");
    lcd.setCursor(0,1);
    lcd.print("Honeymoon Suite");
  }
  if(digitalRead(sw[7]) == HIGH){
    lcd.clear();
    lcd.print("Moving to");
    lcd.setCursor(0,1);
    lcd.print("Penthouse");
  }
}