/**
 * This sketch comprises the base functionality to control PWM fans via
 * pins 10*, 11* (implementation dependent). Potentiometer pins from L -> R
 * Be aware that the code in this file can be used to control anything PWM
 * and is therefore used in my own implementation to control a PWM water pump.
 * 5v, signal, GND
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
