//Half revolution to open door
int stepRev = 200; //200 = half revolution, 400 = full revolution

// function for door opening
void stepphalv(){
  for (int i=0; i<stepRev/8; i++){
    digitalWrite(A, HIGH);
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, LOW);
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);
    
    digitalWrite(A, HIGH);
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);
    
    digitalWrite(A, HIGH);
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, LOW);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);
    
    digitalWrite(A, HIGH);
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, LOW);
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);
    
    digitalWrite(A, HIGH);
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);
    digitalWrite(phase_A,LOW);
    digitalWrite(B, LOW);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);   

  }
}
// function for door closing
void stepphalvu(){
  for (int i=0; i<stepRev/8; i++){
    digitalWrite(A, HIGH);  // stepp 8
    digitalWrite(phase_A,LOW);
    digitalWrite(B, LOW);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500); 

    digitalWrite(A, HIGH);  // stepp 7
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, LOW); // stepp 6
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);  // stepp 5
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, HIGH);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);  // stepp 4
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, LOW);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, HIGH);  // stepp 3
    digitalWrite(phase_A,HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);

    digitalWrite(A, LOW);   // stepp 2
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);    

    digitalWrite(A, HIGH);    // stepp 1
    digitalWrite(phase_A,LOW);
    digitalWrite(B, HIGH);
    digitalWrite(phase_B, LOW);
    delayMicroseconds(2500);
  }
}