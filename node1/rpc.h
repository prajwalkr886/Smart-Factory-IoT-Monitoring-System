// ESP32 RGB LED Blink

#define RED_PIN    25
#define GREEN_PIN  26
#define BLUE_PIN   27

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // RED
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  delay(1000);

  // OFF
  digitalWrite(RED_PIN, LOW);
  delay(500);

  // GREEN
  digitalWrite(GREEN_PIN, HIGH);
  delay(1000);

  // OFF
  digitalWrite(GREEN_PIN, LOW);
  delay(500);

  // BLUE
  digitalWrite(BLUE_PIN, HIGH);
  delay(1000);

  // OFF
  digitalWrite(BLUE_PIN, LOW);
  delay(500);
}