#define ledR 8
#define ledG 7
#define ledY 12

int interrCount = 0;

void setup()
{
  Serial.begin(9600);
  pinMode( ledR, OUTPUT );
  pinMode( ledR, OUTPUT );
  pinMode( ledR, OUTPUT );
  
  digitalWrite( ledR, 0);
  digitalWrite( ledG, 0);
  digitalWrite( ledY, 0);
  
  attachInterrupt(0, interruptChange, RISING);
}

void loop()
{
  interrCount++;
  
  digitalWrite(ledR,1);
  digitalWrite(ledG,0);
  delay(300);
  digitalWrite(ledR,0);
  digitalWrite(ledG,1);
  delay(300);
  
  if (interrCount == 10)
  {
    interrCount = 0;
    digitalWrite( ledY, 0);
    Serial.println("NORMAL FUNCTIONALITY");
  }
}

void interruptChange()
{
  digitalWrite(ledY, 1);
  Serial.println("INTERRUPT-MOTION DETECTED!");
}
