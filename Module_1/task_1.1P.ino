const int motionSensorPin = 2;     // output pin for motion sensor
const int externalLedPin = 7;      // output pin for external LED
const int buzzerPin = 8;           // output pin for buzzer

void setup() {
  Serial.begin(9600);  
  pinMode(motionSensorPin, INPUT);  
  pinMode(externalLedPin, OUTPUT);  
  pinMode(buzzerPin, OUTPUT);       
}

void loop() {
  int motionValue = digitalRead(motionSensorPin);
  
  if (motionValue == HIGH) {
    digitalWrite(externalLedPin, HIGH);  
    Serial.println("MOTION DETECTED!!!");
  } else {
    digitalWrite(externalLedPin, LOW);   
    Serial.println("THERE IS NOTHING AROUND");
  }

  if (motionValue == HIGH) {
    tone(buzzerPin, 100); 
  } else {
    noTone(buzzerPin);     
  }
  delay(1000); 
}
