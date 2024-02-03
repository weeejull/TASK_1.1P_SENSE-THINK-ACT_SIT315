#define ledR 8
#define ledG 7
#define ledY 12
#define motionSensor 2  
#define tempSensor A1   

int interrCount = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  
  digitalWrite(ledR, 0);
  digitalWrite(ledG, 0);
  digitalWrite(ledY, 0);
  
  attachInterrupt(digitalPinToInterrupt(motionSensor), interruptMotion, RISING);  
}

void loop()
{
  int tempValue = analogRead(tempSensor);
  
  float voltage = (tempValue / 1023.0) * 5000.0;  //THIS LINE CONVERTS THE RAW ANALOG VALUE COLLECTED FROM THE SENSOR TO THE VOLTAGE
  float temperature = (voltage - 500.0) / 10.0;  //THIS LINE CONVERTS THE VOLTAGE INTO TEMPERATURE VALUE IN DEGREE CELSIUS
  Serial.print("TEMPERATURE: ");
  Serial.print(temperature);
  Serial.println(" °C");

  interrCount++;
  
  digitalWrite(ledR, 1);
  digitalWrite(ledG, 0);
  delay(300);
  digitalWrite(ledR, 0);
  digitalWrite(ledG, 1);
  delay(300);
  
  if (interrCount == 10)
  {
    interrCount = 0;
    digitalWrite(ledY, 0);
    Serial.println("NORMAL FUNCTIONALITY");
  }
}

void interruptMotion()
{
  digitalWrite(ledY, 1);
  Serial.println("INTERRUPT! INTERRUPT! INTERRUPT! MOTION DETECTED!");
}
