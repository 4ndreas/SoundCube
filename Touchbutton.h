#ifndef TOUCHBUTTON_H
#define TOUCHBUTTON_H

#include <Arduino.h>
#include <UTFT.h>
#include <ITDB02_Touch.h>

extern uint8_t SmallFont[];

struct ButtonStyle
{
	UTFT * myLCD;
	uint8_t * myFont;
	int x_Center;
	int y_Center;
	char * text;
	_Color text_Color;
	_Color back_Color;
	_Color border_Color;
	char style;
	char PAGE;
};

class Touchbutton
{
public:
	Touchbutton();
	void Init(UTFT *gLCD);
	void Init(ButtonStyle BStyle);
	//void drawButton(int grid, char * text, _Color text_Color, _Color back_Color, _Color border_Color, char style=0);

	//void drawButton(int x_Center, int y_Center, char * text, _Color text_Color, _Color back_Color, _Color border_Color, char style= 0, char PAGE=0);
	void drawButton(int x_Center, int y_Center, char * text, _Color text_Color, _Color back_Color, _Color border_Color, char style= 0, char PAGE=0, uint8_t * _myFont=SmallFont);
	bool TouchInput(int xInput, int yInput);
	bool TouchInput(int xInput, int yInput, char Page);
	void Enable(bool en);
	void selectButton(bool select);
	void setFont(uint8_t* font);
	void changeText(String text);

protected:
	UTFT *myLCD;
	void paintButton();
	void pressedSignal();
	uint8_t * myFont;

	char ticker; 
	int xCenter;
	int yCenter;
	bool pressed;
	bool selected;

	//char buttonText[10];
	char * buttonText;
	_Color textColor;
	_Color backColor;
	_Color activeColor;
	_Color pressedColor;
	_Color borderColor;
	_Color runningColor;

	char buttonStyle;
	char page;
};

#endif 
