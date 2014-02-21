#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <Arduino.h>
#include <UTFT.h>
#include <ITDB02_Touch.h>

//struct _Color
//{
//	uint8_t red;
//	uint8_t green;
//	uint8_t blue;
//};

class ProgressBar
{
public:
	ProgressBar();
	void Init(UTFT *gLCD);
	void drawButton(int x_Color, int y_Color, _Color text_Color, _Color back_Color, _Color border_Color, int VALUE, char Page= 0, int MaxValue = 100,int offset= 0);
	bool TouchInput(int xInput, int yInput);
	void setValue(int VALUE);
	inline int getValue(){return value;};

protected:
	UTFT *myLCD;
	int value;
	int xCenter;
	int yCenter;
	char page;
	int maxValue;
	int centerValue;
	//bool pressed;
	//String buttonText;
	_Color textColor;
	_Color backColor;
	_Color borderColor;
	//int buttonStyle;
};

#endif 

