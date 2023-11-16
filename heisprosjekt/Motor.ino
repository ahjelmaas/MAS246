
// Code for setting direction of motor
void DCmotorCW() {
  digitalWrite(DC_phase, LOW);
  digitalWrite(DC_decay, LOW);
}
void DCmotorCCW() {
  digitalWrite(DC_phase, HIGH);
  digitalWrite(DC_decay, LOW);
}
