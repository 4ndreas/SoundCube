#include "ProgressBar.h"

ProgressBar::ProgressBar()
{

}

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

void ProgressBar::Init(UTFT *gLCD)
{
	myLCD = gLCD;
	myLCD->setFont(BigFont);
}

#define ButtonSize 18


void ProgressBar::drawButton(int x_Color, int y_Color, _Color text_Color, _Color back_Color, _Color border_Color, int VALUE, char Page, int MaxValue ,int offset)
{
	xCenter = x_Color;
	yCenter = y_Color;
	value = VALUE;
	page = Page;
	maxValue = MaxValue;
	centerValue = offset;

	textColor.red = text_Color.red;
	backColor.red = back_Color.red;
	borderColor.red = border_Color.red;

	textColor.green = text_Color.green;
	backColor.green = back_Color.green;
	borderColor.green = border_Color.green;

	textColor.blue = text_Color.blue;
	backColor.blue = back_Color.blue;
	borderColor.blue = border_Color.blue;

#define ButtonSize 21
#define ButtonLenght 65

	//draw Border
	myLCD->setColor(borderColor.red,borderColor.green,borderColor.blue);
	myLCD->drawRect(xCenter - ButtonLenght-1 ,yCenter - ButtonSize-1 ,xCenter + ButtonLenght+1,yCenter + ButtonSize+1);

	//draw Background
	myLCD->setColor(0,0,0);
	myLCD->fillRect(xCenter - ButtonLenght , yCenter - ButtonSize,xCenter - ButtonLenght , yCenter + ButtonSize+1);

	setValue(value);

#undef ButtonLenght
#undef ButtonSize
}

void ProgressBar::setValue(int VALUE)
{
	//VALUE += centerValue ;

	//if (value == VALUE)
	//{
	//	return;
	//}

#define ButtonSize 20
#define ButtonLenght 65

	//draw Background
	//myLCD->setColor(0,0,0);
	//myLCD->fillRect(xCenter - ButtonLenght , yCenter - ButtonSize,xCenter + ButtonLenght, yCenter + ButtonSize);

	myLCD->setFont(BigFont);

	if(value < 44)	// just for text 
		{
			myLCD->setBackColor(0,0,0);
		}
		else
		{
			myLCD->setBackColor(backColor.red,backColor.green,backColor.blue);
		}

	if(VALUE >= value)
	{
		value = VALUE; 

		myLCD->setColor(backColor.red,backColor.green,backColor.blue);

		myLCD->fillRect(xCenter - ButtonLenght, yCenter - ButtonSize, xCenter - ButtonLenght + (ButtonLenght*2 * (value+centerValue))/maxValue , yCenter + ButtonSize);

		myLCD->setColor(255,255,255);
		myLCD->printNumI(value,xCenter - (3 * myLCD->cfont.x_size / 2) , yCenter - (myLCD->cfont.y_size / 2),3);
	}
	else
	{
		value = VALUE; 

		myLCD->setColor(0,0,0);
		myLCD->fillRect(xCenter - ButtonLenght + (ButtonLenght * 2 * (value+centerValue))/maxValue , yCenter - ButtonSize, xCenter + ButtonLenght , yCenter + ButtonSize);

		myLCD->setColor(255,255,255);
		myLCD->printNumI(value,xCenter - (3 * myLCD->cfont.x_size / 2) , yCenter - (myLCD->cfont.y_size / 2),3);
	}

#undef ButtonLenght
#undef ButtonSize
}

