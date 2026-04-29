#include <Adafruit_NeoPixel.h>
#include <BleKeyboard.h>

#define BUTTON_PIN 3
#define LED_PIN 4
#define NUM_PIXELS 1

BleKeyboard bleKeyboard("Macropad", "XIAO" 100);
Adafruit_NeoPixel pixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

bool lastButtonState = HIGH;
uint32_t firstPixelHue = 0;

void setup() 
{
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pixel.begin();
	pixel.setBrightness(50);
	pixel.show();
	delay(1000);
	bleKeyboard.begin();
}

void loop()
{
	pixel.setPixelColor(0, pixel.gamma32(pixel.ColorHSV(firstPixelHue)));
	pixel.show();
	firstPixelHue += 256;
	if(firstPixelHue >= 65536) firstPixelHue = 0;
	bool currentButtonState = digitalRead(BUTTON_PIN);
	if (currentButtonState == LOW && lastButtonState == HIGH)
	{
		if (bleKeyboard.isConnected())
		{
			bleKeyboard.press(KEY_LEFT_GUI);
			delay(10);
			bleKeyboard.press(KEY_TAB);
			delay(50);
			bleKeyboard.releaseAll();
		}
		
	}
	lastButtonState = currentButtonState;
	delay(10);
}