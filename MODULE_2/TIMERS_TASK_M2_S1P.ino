// NAME = VIJUL
// ROLL NUMER = 2210994860
// ACTIVITY 3

const byte LED_PIN = 13;
const byte METER_PIN = A4;
// BLINKS THE LED EVERY 2 SECONDS
volatile double timerFrequency = 0.25; 

// PROCEDURE TO START THE TIMER WITH A GIVEN FREQUENCY
void startTimer(double frequency);

// PROCEDURE TO UPDATE THE TIMER BASED ON THE POTENTIOMETER 
void updateTimerFrequency();

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
  
  Serial.begin(9600);
  
  startTimer(timerFrequency);
}

void loop()
{ 
  // CONTINUOUSLY UPDATES THE TIMER BASED ON THE POTENTIOMETER
  updateTimerFrequency();
}

void startTimer(double frequency)
{
  noInterrupts();
  
  // CALCULATE THE VALUES FOR OCR1A AND PRESCALER BASED ON THE DESIRED FREQUENCY
  double period = 1.0 / frequency;
  double timerTicks = (period * 16000000) - 1; // 16 MHz Arduino clock frequency
  
  // SET THE VALUES FOR OCR1A AND TCCR1B REGISTERS
  OCR1A = static_cast<uint16_t>(timerTicks);  // ENSURE TIMERTICKS FITS WITHIN 16 BITS
  TCCR1A = 0;  // CONFIGURE TIMER1 FOR NORMAL MODE
  TCCR1B = (1 << WGM12) | (1 << CS12); // CTC MODE, PRESCALER 256
  TIMSK1 = (1 << OCIE1A); // ENABLE TIMER COMPARE INTERRUPT
  
  interrupts();
}

ISR(TIMER1_COMPA_vect)
{
  digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}

void updateTimerFrequency()
{
  // READ THE ANALOG VALUE FROM THE POTENTIOMETER
  int potValue = analogRead(METER_PIN);
  
  // MAP THE POTENTIOMETER VALUE TO THE TIMERFREQUENCY RANGE
  timerFrequency = map(potValue, 0, 1023, 0.1, 10.0); // ADJUST THE RANGE AS NEEDED
  
  // UPDATE THE TIMER WITH THE NEW FREQUENCY
  startTimer(timerFrequency);
}


