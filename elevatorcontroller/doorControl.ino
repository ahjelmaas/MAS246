//Half revolution to open door
int stepRev = 200; //200 = half revolution, 400 = full revolution

// List of door states
enum DoorState {
  CLOSED,
  HALF,
  OPEN
};
// Variable to store the current door state
DoorState doorState = CLOSED; // The idle state for the door is closed

// function for door closing
void closeDoor(){
  for (int i=0; i<stepRev/8; i++){
    doorState = HALF; // set doorstate to half as the doors move

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

    doorState = CLOSED; //set doorstate to closed, so the elevator can start moving
  }

}
// function for door opening
void openDoor(){
  for (int i=0; i<stepRev/8; i++){
    doorState = HALF; // set the doorstate to half as the doors move

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

    doorState = OPEN; // set the doorstate to open, passengers may now embark/disembark
  }
}