#include <CrossInteger.h>

CrossInteger<uint8_t> MyNum1;


/*
	При начальных значениях нету первого вызова колбека с текущим значением
*/

void setup()
{
	Serial.begin(115200);
	
	randomSeed(analogRead(0));
	
	MyNum1.SetCallback(OnFading);
	//MyNum1.SetConversion(OnConversion);
	MyNum1.SetVal(100);
	MyNum1.SetMin(25);
	MyNum1.SetMax(250);
	MyNum1.SetStep(3);
	MyNum1.SetInterval(25);
	//MyNum1.GoMin();
	//MyNum1.GoMax();
	MyNum1.GoCenter();
	//MyNum1.FadeTo(75);
	//MyNum1.FadeMin();
	//MyNum1.FadeMax();
	//MyNum1.FadeCenter();
	//MyNum1.GetVal();
	//MyNum1.GetCallback();
	//MyNum1.Processing();
	
	return;
}

void loop()
{
	MyNum1.Processing();
	
	return;
}

void OnFading(uint8_t id, uint8_t value, bool complete)
{
	/*
	Serial.print("OnFading (");
	Serial.print(value);
	Serial.print(", ");
	Serial.print(complete, BIN);
	Serial.println(");");
	*/
	
	Serial.print((uint8_t)complete * 100);
	Serial.print(" ");
	Serial.println(value);
	
	if(complete)
	{
		MyNum1.FadeTo( rnd1() );
		MyNum1.SetInterval( rnd2() );
	}
	
	return;
}

uint8_t OnConversion(uint8_t id, uint8_t min, uint8_t max, uint8_t from, uint8_t to, uint8_t current)
{
	return current + 1;
}


uint8_t rnd1_val = 0;
uint8_t rnd2_val = 0;

uint8_t rnd1()
{
	uint8_t tmp;
	do
	{
		tmp = random(25, 250);
	} while(tmp == rnd1_val);
	rnd1_val = tmp;
	
	return tmp;
}

uint8_t rnd2()
{
	uint8_t tmp;
	do
	{
		tmp = random(5, 50);
	} while(tmp == rnd2_val);
	rnd2_val = tmp;
	
	return tmp;
}

