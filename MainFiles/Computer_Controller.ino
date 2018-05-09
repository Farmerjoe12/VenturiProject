#include <Adafruit_NeoPixel.h>
/**
 * This sketch will control an arduino-based system involving LED's as well as 
 * pwm for fans and a water pump. My muse for the sketch is all of the proprietary software 
 * that exists in the world for standalone led strips, the motherboard software that controls
 * pwm fans, and the AIO water cooling systems. Because my motherboard does not easily support
 * pwm and user-control, I decided to use the arduino as a platform to allow implementation
 * independent fan control. Builiding on top of the fan controller, I added in LED strip support,  
 * as well as a water pump for a liquid cooling system, which functions almost identical to the fans.
 * 
 * This sketch includes functionality for the following:
 * Rheostat for fan control
 * LED strip control
 * Fan control
 * Pump Control
 * 
 */
#define RHEO_PIN 0
#define LED_PIN 6
#define PUMP_PIN 9
#define FAN1_PIN 10
#define FAN2_PIN 11

// Fan controller vars
// fanSpeed range 0 - 255
int defaultFanSpeed = 100;
int fanArray[] = {FAN1_PIN, FAN2_PIN};
int numFans = 2;

// Rheostat(Potentiometer) vars
int rheoVal = 0;

// Led Strip vars
int LEDs = 250;         // How many LED's to address
int increment = 1;      // How many LED's to skip when addressing
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDs, LED_PIN, NEO_GRB + NEO_KHZ800);

// Color identifiers
byte red   = 0;
byte green = 1;
byte blue  = 2;
byte white = 3;
byte magenta = 4;
byte yellow = 5;
byte cyan = 6;
byte purple = 7;
byte teal = 8;
byte olive = 9;
byte black = 10;
byte orange = 11;

// Color array NO white OR black; length 10
byte colors[] = {red, green, blue, magenta, yellow, 
                 cyan, purple, teal, olive, orange};

// Polling vars
int updateInterval = 50;
unsigned long lastUpdate = 0;

/**
 * Initialize the fans to their default speed
 */
void initializeFans(int fanPin[])
{
  for(int i = 0; i < numFans; i++){ 
    pinMode(fanPin[i], OUTPUT);    
    writeToFans(fanPin[i], defaultFanSpeed);
  }  
}

/**
 * Method to directly mutate the fan speed
 */
void writeToFans(int fanPin, int intensity)
{
  analogWrite(fanPin, intensity);
}

/**
 * Get a value from the potentiometer and adjust so it's within
 * (roughly) 0-255 range
 */
double getIntensity()
{
  return analogRead(RHEO_PIN)/4;  
}

/**
 * Set the color of the strip at full bright
 * 
 * Used as a helper (lazy) method for setColor intensity
 */
void setColor(byte color)
{
  setColorIntensity(color, 255);
}

/** 
 *  Method to set colors and brightness. Primary colors being Red, Green, and Blue
 *  recieve full intensity when they are the sole color. If a mix is desired, then 
 *  intensity is modulated by a scalar value to decrese the maximum amount of color
 *  which will produce the desired color.
 */
void setColorIntensity(byte color, int intensity)
{
  // shout out to @RFW from TCD
  int r = 0, g = 0, b = 0;
  
  switch( color )
  {
    case 0: // red
      r = intensity;
      break;
    case 1: // green
      g = intensity;
      break;
    case 2: // blue
      b = intensity;
      break;
    case 3: // white
      r = intensity;
      g = intensity;
      b = intensity;
      break;
    case 4: // magenta
      r = intensity; 
      b = intensity;
      break;
    case 5: // yellow
      r = intensity;
      g = intensity;
      break;
    case 6: // cyan
      g = intensity;
      b = intensity;
      break;
    case 7: // purple
      r = (intensity/2);
      b = (intensity/2);
      break;
    case 8: // teal
      g = (intensity/2);
      b = (intensity/2);
      break;
    case 9: // olive
      r = (intensity/2);
      g = (intensity/2);
      break;
    case 10: // black
      r = 0;
      g = 0;
      b = 0;
      break;
    case 11:// Orange
      r = intensity;
      g = intensity/4;
      break;
  }
  for ( int x = 0; x < LEDs; x += increment )
      {
        strip.setPixelColor(x, r, g, b);
        strip.show();
      }
}

void setup()
{
  initializeFans(fanArray); // Get the fans going
  
  Serial.begin(9600); // Start up the serial monitor
  
  strip.begin();      // Start and show the strip
  strip.show();
}

void loop()
{  
  if ((millis() - lastUpdate) > updateInterval)
  {
    lastUpdate = millis();    
    for(int i = 0; i < numFans; i++){ 
        writeToFans(fanArray[i], getIntensity());
    }
  }
  setColor(teal);
}
