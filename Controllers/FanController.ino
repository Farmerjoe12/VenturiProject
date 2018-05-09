/**
 * This sketch comprises the base functionality to control PWM fans via
 * pins 10*, 11* (implementation dependent). Be aware that the code in this file can be used to control anything PWM
 * and is therefore used in my own implementation to control a PWM water pump.
 * 
 * Potentiometer pins from L -> R
 * 5v, signal, GND
 */

 /**
  * The PWM signal on the default arduino is different than what most fans
  * and pumps require. The function setPwmFreuqency() is used to adjust that 
  * base frequency to more closely match the one the fans require.
  * See this page for more info: https://playground.arduino.cc/Code/PwmFrequency
  * 
  * Be aware using this function may or may not affect other libraries you are using.
  */

// fanSpeed range 0 - 255
int defaultFanSpeed = 100;
int fanPin[] = {10, 11};
int numFans = 2;

// potPin
int potPin = 0;
int potVal = 0;

// polling intervals
int updateInterval = 100;
unsigned long lastUpdate = 0;

void initializeFans(int fanPin[])
{
  setPwmFrequency(10, 1);       // Change PWM frequency on pin 10 to roughly 31khz
  for(int i = 0; i < numFans; i++){ 
    pinMode(fanPin[i], OUTPUT);    
    writeToFans(fanPin[i], defaultFanSpeed);
  }  
  
}

void writeToFans(int fanPin, int intensity)
{
  analogWrite(fanPin, intensity);
}

// getIntensity returns a reading from the potentiometer
// adjusted to read b/w (roughly) 0-255
double getIntensity()
{
  return analogRead(potPin)/4;  
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

void setup()
{
  initializeFans(fanPin);
}

void loop()
{
  if ((millis() - lastUpdate) > updateInterval)
  {
    lastUpdate = millis();
    int currentIntensity = getIntensity();
    
    if(currentIntensity > potVal + 3 || currentIntensity < potVal-3){
      for(int i = 0; i < numFans; i++){ 
        writeToFans(fanPin[i], currentIntensity);
      }
    }
  }  
}
