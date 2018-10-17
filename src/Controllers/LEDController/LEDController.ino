#include <Time.h>
//#include <TimeLib.h>

#include <Adafruit_NeoPixel.h>
#define PIN 6

// Strip variables
int LEDs = 150;         // How many LEDs to address
int delayTime = 1250;   // How long to delay
int increment = 1;      // How many LEDs to skip when addressing
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDs, PIN, NEO_GRB + NEO_KHZ800);

// Color identifiers
byte black[] = {0 , 0 , 0};
byte red[] = {255, 0 , 0};
byte green[] = {0, 255, 0};
byte blue[] = {0, 0, 255};
byte yellow[] = {255, 255, 0};
byte cyan[] = {0, 255, 255};
byte purple[] = {255, 0, 255};
byte nightLight[] = {255, 100, 0};
byte white[] = {255, 255, 255};

// Raw color matrix
byte colorArray[4][3] = {
		{255,0,0},
		{255,255,0},
		{255,100,0},
		{0,255,0}
};

// Potentiometer variables
int spin = 0;     // spin is input pin
int val = 0;      // Val is for incoming potentiometer val
double intensity = 0;// Intensity is val / 4 for led value

// Photo resistor variable
int lightPin = 1;
bool dimmable = false;

void setup()
{
  Serial.begin(9600);
  strip.begin();
  strip.show();
  setColor(black);
  delay(2000);
}

void loop()
{ 
    intensity = getIntensity();
   // dimmableLight(green, intensity);
    colorLoop(red, yellow, green, nightLight, 250);
	//pulse(purple);
	//rgbLoop();

	//setColor(red);
}

/** pulse() fades back and forth from full black to a full color
 *  using the fade() and setColor methods gives a 'breathing' effect
 */
void pulse(byte color[])
{
  fade(color, 0, 50, 5);
  setColor(color, 50);
  delay(750);
  fade(color, 50, 0, 5);
  setColor(black);  
  delay(750);
}

/** fade() will fade from an initial brightness to an end brightness
 *  uses the setColor(color[], intensity) method each iteration
 *
 *  @param sBright starting brightness
 *  @param eBright ending brightness
 *  @param rate bytes per iteration
 */
void fade(byte color[], int sBright, int eBright, byte rate)
{
  if(sBright < eBright)
  {
    while(sBright < eBright)
    {
      setColor(color, sBright);
      sBright+=rate;
    }
  }
  else
  {
    while(sBright > eBright)
    {
      setColor(color, sBright);
      sBright-=rate;
    }
  }
}

void rgbLoop()
{
  setColor(red);
  delay(delayTime);
  setColor(green);
  delay(delayTime);
  setColor(blue);
  delay(delayTime);
}

void colorLoop(byte color1[], byte color2[], byte color3[],
				byte color4[], int delayPeriod)
{
	int targetBrightness = 50;
	int step = 5;

	fade(color1, 0, targetBrightness, step);
	delay(delayPeriod);
	fade(color1, targetBrightness, 0, step);

	fade(color2, 0, targetBrightness, step);
	delay(delayPeriod);
	fade(color2, targetBrightness, 0, step);

	fade(color3, 0, targetBrightness, step);
	delay(delayPeriod);
	fade(color3, targetBrightness, 0, step);

	fade(color4, 0, targetBrightness, step);
	delay(delayPeriod);
	fade(color4, targetBrightness, 0, step);
}



void dimmableLight(byte lightColor[], int intensity)
{
  if(intensity < 5)
    setColor(black);
  else if(intensity > 240)
    setColor(lightColor);
  else
    setColor(lightColor, intensity);
}

int getAmbient()
{
  return analogRead(lightPin);
}

void printAmbient()
{
  Serial.println(analogRead(lightPin));
}

/**
 * Use this method when you want to set a specific intensity(brightness)
 * to your color
 *
 * @param color color you want to set
 * @param intensity intensity value
 */
void setColor(byte color[], double intensity)
{
  double brightness = intensity/250;
  byte r = color[0] * brightness;
  byte g = color[1] * brightness;
  byte b = color[2] * brightness;  
  byte newColor[] = {r, g, b};

  setColor(newColor);
}

/**
 * Sets all pixels in range to full color values.
 * Uses the 'LEDs' and 'increment' member variables
 */
void setColor(byte color[])
{
    for ( int x = 0; x < LEDs; x += increment )
      {
        strip.setPixelColor(x, color[0], color[1], color[2]);
        strip.show();
      }
}

/** getIntensity will return the value read by the potentiometer
 *  reduced by 1/4 to keep values within a range of roughly
 *  0 - 255
 */
double getIntensity()
{
  return analogRead(spin)*.25;  
}
