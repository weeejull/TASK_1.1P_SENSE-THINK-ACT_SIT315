// NAME - VIJUL
// ROLL NUMBER - 2210994860
// DISTINCTION TASK 1.4D - MORE INPUTS TIMER BOARD
// DEFINING PIN NUMBERS FOR LEDS, SENSORS, AND ADDITIONAL SENSORS (PUSH BUTTONS)
#define ledR 8
#define ledG 7
#define ledY 12
#define motionSensor 2
#define tempSensor A1
#define additionalSensor1 3
#define additionalSensor2 4

// THIS IS A COUNTER SO IT KEEPS TRACK OF THE INTERRUPTS
int interrCount = 0;

volatile unsigned long startTime = 0;

void setup()
{
  // THIS LINE BEGINS SERIAL COMMUNICATION
  Serial.begin(9600);

  // SETTING UP THE PIN MODES FOR LEDS AND ADDITIONAL SENSORS
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(additionalSensor1, INPUT);
  pinMode(additionalSensor2, INPUT);

  // SETTING UP THE INITIAL STATES FOR THE LEDS
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledY, LOW);

  // ATTACHING INTERRUPT FOR MOTION SENSOR - CHANGE TRIGGER - INTRUDUCED WHENEVER THERE IS A CHANGE IN THE VOLTAGE
  attachInterrupt(digitalPinToInterrupt(motionSensor), interruptMotion, CHANGE);

  // ATTACHING INTERRUPT FOR ADDITIONAL SENSORS - CHANGE TRIGGER - INTRUDUCED WHENEVER THERE IS A CHANGE IN THE VOLTAGE
  attachInterrupt(additionalSensor1, interruptAdditionalSensor, CHANGE);
  attachInterrupt(additionalSensor2, interruptAdditionalSensor, CHANGE);

  // SETTING UP TIME INTERRUPT
  setupTimerInterrupt();
}

void loop()
{
  // REDING TEMPERATURE FROM THE SENSOR
  int tempValue = analogRead(tempSensor);
  float voltage = (tempValue / 1023.0) * 5000.0;
  float temperature = (voltage - 500.0) / 10.0;

  // PRINTING TEMPERATURE TO SERIAL MONITOR
  Serial.print("TEMPERATURE: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // POLLING FOR ADDITIONAL SENSORS
  if (digitalRead(additionalSensor1) == HIGH) {
    // HANDLING THE EVENT WHEN THE FIRST PUSH BUTTON IS PRESSED
    Serial.println("*TRIGERRRR*...ADDITIONAL SENSOR 1 TRIGGERED! - INTERRUPT 2");
  }

  if (digitalRead(additionalSensor2) == HIGH) {
    // HANDLING THE EVENT WHEN THE SECOND PUSH BUTTON IS PRESSED
    Serial.println("*TRIGGERRR*...ADDITIONAL SENSOR 2 TRIGGERED! - INTERRUPT 3");
  }

  // CREATING A TOGGLE EFFECT OF LEDS
  interrCount++;
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, LOW);
  delay(300);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, HIGH);
  delay(300);

  // RESETTING THE COUNTER
  if (interrCount == 10)
  {
    interrCount = 0;
    digitalWrite(ledY, LOW);
    //Serial.println("NORMAL FUNCTIONALITY");
  }
  
  Serial.print("TEMPERATURE: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Print the current time
  Serial.print("TIME: ");
  printElapsedTime();
  Serial.println("");
}

// INTERRUPT FOR MOTION SENSOR
void interruptMotion()
{
  digitalWrite(ledY, HIGH);
  Serial.println("*TRIGERRRR*...MOTION DETECTED - INTERRUPT 1");
}

// INTERRUPT FOR ADDITIONAL SENSORS- PUSH BUTTONS
void interruptAdditionalSensor()
{
  Serial.println("*TRIGERRR*...INTERRUPT INITIATED!");
}

// SETTING UP TIMER FUNCTION
void setupTimerInterrupt()
{
  startTime = millis();  // STORING THE START TIME
}

void printElapsedTime()
{
  unsigned long elapsedTime = millis() - startTime;

  // CONVERTING MILLISECONDS TO SECONDS
  unsigned long elapsedSeconds = elapsedTime / 1000;

  // PRINTING THE ELAPSED TIME
  Serial.print("ELAPSED TIME: ");
  Serial.print(elapsedSeconds);
  Serial.println(" seconds");
}


