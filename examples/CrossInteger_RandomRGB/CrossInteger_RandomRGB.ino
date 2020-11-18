#include <CrossInteger.h>

constexpr uint8_t PIN_LED_R = 11;
constexpr uint8_t PIN_LED_G = 10;
constexpr uint8_t PIN_LED_B = 9;

void OnFading(uint8_t id, uint8_t value, bool complete);

CrossInteger<uint8_t, PIN_LED_R> LedR(OnFading, 0, 0, 255, 1, 10);
CrossInteger<uint8_t, PIN_LED_G> LedG(OnFading, 0, 0, 255, 1, 10);
CrossInteger<uint8_t, PIN_LED_B> LedB(OnFading, 0, 0, 255, 1, 10);

uint32_t LastRandColorTime = 0;

void setup()
{
	Serial.begin(115200);
	
	randomSeed( analogRead(0) + analogRead(1) );
	
	pinMode(PIN_LED_R, OUTPUT);
	pinMode(PIN_LED_G, OUTPUT);
	pinMode(PIN_LED_B, OUTPUT);
	
	// Это не имеет отношения к работе библиотеки, просто мне так удобнее было. //
	pinMode(8, OUTPUT);
	digitalWrite(8, LOW);
	// //
	
	RandColor();
	
	return;
}

void loop()
{
	uint32_t time = millis();
	
	LedR.Processing(time);
	LedG.Processing(time);
	LedB.Processing(time);
	
	if( LastRandColorTime + 5000 < time)
	{
		RandColor();
		
		LastRandColorTime = time;
	}
	
	return;
}

void OnFading(uint8_t id, uint8_t value, bool complete)
{
	/*
	Serial.print("OnFading (");
	Serial.print(id);
	Serial.print(", ");
	Serial.print(value);
	Serial.print(", ");
	Serial.print(complete, BIN);
	Serial.println(");");
	*/
	
	analogWrite(id, value);
	
	return;
}

void RandColor()
{
	LedR.FadeTo( random(0, 255) );
	LedG.FadeTo( random(0, 255) );
	LedB.FadeTo( random(0, 255) );
}
