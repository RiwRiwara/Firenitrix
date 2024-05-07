const int buttonPin4 = 4;
const int buttonPin5 = 5;
const int buttonPin6 = 6;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
}

void loop() {
  int state4 = digitalRead(buttonPin4);
  int state5 = digitalRead(buttonPin5);
  int state6 = digitalRead(buttonPin6);

  if (state4 == LOW) {
    Serial.println("Button 4 pressed");
    delay(200); 
  }
  if (state5 == LOW) {
    Serial.println("Button 5 pressed");
    delay(200); 
  }
  if (state6 == LOW) {
    Serial.println("Button 6 pressed");
    delay(200); 
  }

}
