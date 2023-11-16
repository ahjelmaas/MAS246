void test(){
   human = analogRead(callLift);
  vertical = analogRead(VERT);
  int floorState = 0;
if(analogRead(vertical > 900)){

    stepphalv();

    requestedF = 0;
    dist = currentF - requestedF;
    digitalWrite(DC_phase, HIGH);
    analogWrite(pwm_signal, 128);
    delay(3000);
    analogWrite(pwm_signal, 0);

    floorState = 1;
  }
   Serial.print("vertical: ");
  Serial.print(vertical, DEC);
  // Serial.print("human:");
  // Serial.print(human,DEC);
}