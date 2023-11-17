void floorlights() {
  // Array to map floor number to pin number
  const int floorPins[] = {49, 48, 47, 46, 45, 44, 43, 42};

  // Ensure currentF is within a valid range
  if (currentF >= 0 && currentF < sizeof(floorPins) / sizeof(floorPins[0])) {
    // Turn off all lights
    for (int i = 0; i < sizeof(floorPins) / sizeof(floorPins[0]); ++i) {
      digitalWrite(floorPins[i], LOW);
    }

    // Turn on the light for the current floor
    digitalWrite(floorPins[currentF], HIGH);
  }
}