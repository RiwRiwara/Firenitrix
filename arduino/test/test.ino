const int buttonPin8 = 8;
const int buttonPin9 = 9;
const int buttonPin10 = 10;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin8, INPUT_PULLUP);
  pinMode(buttonPin9, INPUT_PULLUP);
  pinMode(buttonPin10, INPUT_PULLUP);
}

void loop() {
  int state8 = digitalRead(buttonPin8);
  int state9 = digitalRead(buttonPin9);
  int state10 = digitalRead(buttonPin10);

  if (state8 == LOW) {
    Serial.println("Button 8 pressed");
    delay(200); 
  }
  if (state9 == LOW) {
    Serial.println("Button 9 pressed");
    delay(200); 
  }
  if (state10 == LOW) {
    Serial.println("Button 10 pressed");
    delay(200); 
  }

}
