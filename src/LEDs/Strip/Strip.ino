#include <Adafruit_NeoPixel.h>
#define PIN 6

/**
 * Strip is the base sketch to control an LED strip. Note that this sketch
 * involves the use of a potentiometer (rheostat) to modulate the intensity
 * of the led strip. This is not neccessary and the LED's can be set directly
 * via setColor or setColorIntensity.
 */
 
 // Strip variables
int LEDs = 250;         // How many LED's to address
int delayTime = 1250;   // How long to delay
int increment = 1;      // How many LED's to skip when addressing
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDs, PIN, NEO_GRB + NEO_KHZ800);

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
byte nightLight = 11;

// Color array NO white; length 9
byte colors[] = {red, green, blue, magenta, yellow, 
                 cyan, purple, teal, olive};

// Potentiometer variables
int spin = 0;     // spin is input pin
int val = 0;      // Val is for incoming potentiometer val
int intensity = 0;// Intensity is val / 4 for led value

// Photo resistor variable
int lightPin = 1;
bool dimmable = false;

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

double getIntensity()
{
  return analogRead(spin)*.25;  
}

void setup()
{
  Serial.begin(9600);
  strip.begin();
  strip.show();
  setColor(black);
}

void loop()
{
  setColorIntensity(nightLight, getIntensity());
  //colorLoop(colors);

}
