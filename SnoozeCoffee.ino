/*
 * Press snooze button of a clock and then turn on coffee machine
 * Read 9.6v pulse from Pin 16 (Alarm Output) of LM8560, and send
 * LOW signal to coffee machine switch
 *
 * MCU Sony Dream Machine: EM78P153K
 * MCU Cuisinart Coffee Machine: UTC LM8560
 * http://www.emc.com.tw/twn/database/Data_Sheet/8BIT/EM78P153K.pdf
 * http://www.unisonic.com.tw/datasheet/LM8560.pdf
 */

const int ledPin           = 13;
const int alarmOutputPin   = 4;
const int coffeeSwitchPin  = 9;
const int coffeeLedPin     = 8;

bool lastAlarm    = false;
bool currentAlarm = false;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(coffeeSwitchPin, OUTPUT);
  pinMode(coffeeLedPin, INPUT_PULLUP);
  pinMode(alarmOutputPin, INPUT);
//  Serial.begin(9600);
  
  // turn off cofee machine
  digitalWrite(coffeeSwitchPin, HIGH);
}

void makeCoffee()
{
  // turn on coffee machine only when it is off
  // coffeeLedPin is HIGH when it is off
  int val = digitalRead(coffeeLedPin);
  if (val == HIGH) 
  {
//    Serial.println("make coffee!");
    
    // Digitally press push button
    digitalWrite(coffeeSwitchPin, LOW);
    delay(20);
    digitalWrite(coffeeSwitchPin, HIGH);
    
    // turn on arduino LED
    digitalWrite(ledPin, HIGH);
    delay(3000);
    digitalWrite(ledPin, LOW);
  }
}

void parseCoffee(int pulseCount)
{
  // detect current alarm status based on pulse
  if ( pulseCount > 0 ) {
    currentAlarm = true;
  }
  else {
    currentAlarm = false;
  }
  
  // make coffee if last time alarm was on and 
  // current alarm is off (snooze pressed)
  if ( lastAlarm == true && currentAlarm == false )
  {
//    Serial.println("Snooze!");
    makeCoffee();
  }
  
  // Alarm is going on
  else if ( lastAlarm == true && currentAlarm == true )
  {
//    Serial.println("Alarm!");
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  
  // save alarm status
  lastAlarm = currentAlarm;
}

void loop() 
{
  bool currentaAlrmStatus = false;
  
  int pulseCount = 0;
  long startMillis = millis();
  
  for (;;)
  {
    long currentMillis = millis();
    
    // end of 100ms sampling
    // can also use RC low pass filter instead
    if ( currentMillis - startMillis >= 100 ) 
    {
      parseCoffee(pulseCount);
      pulseCount = 0;
      break;
    }

    int val = digitalRead(alarmOutputPin);
    if (val == HIGH)  {
      pulseCount++; 
    }
    
    // sample at 100Hz
    delay(10);
  }
}
