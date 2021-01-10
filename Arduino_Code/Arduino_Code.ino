// THE ARDUINO CODE FOR EEG

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bits per second
  analogReference(INTERNAL);
}

void loop() {
  Serial.println(analogRead(A0)); // reads pin A0

  /*
  int average = 0;
  for (int i=0; i < 10; i++) {
   average = average + analogRead(A0);
  }
  average = average/10;
  Serial.println(average);
  delay(100);
  */
}
