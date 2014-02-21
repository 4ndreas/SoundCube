#include "Touchbutton.h"



Touchbutton::Touchbutton()
{
}

const int ButtonSize = 21;
const int ButtonLenght = 24;
const int TitleButtonLenght = 65;

void Touchbutton::Init(UTFT *gLCD)
{
	myLCD = gLCD;
}

extern uint8_t SmallFont[];
extern uint8_t BigFont[];


void Touchbutton::Init(ButtonStyle BStyle)
{
	myLCD = BStyle.myLCD;
	xCenter = BStyle.x_Center;
	yCenter = BStyle.y_Center;
	buttonStyle = BStyle.style;
	myFont = 	BStyle.myFont;
	textColor = BStyle.text_Color;
	activeColor = BStyle.back_Color;
	backColor = BStyle.back_Color;
	borderColor = BStyle.border_Color;
	buttonStyle = BStyle.style;
	page = BStyle.PAGE;

}


//void Touchbutton::drawButton(int x_Center, int y_Center, char * text, _Color text_Color, _Color back_Color, _Color border_Color, char style, char PAGE)
//{
//	xCenter = x_Center;
//	yCenter = y_Center;
//	buttonStyle = style;
//
//	buttonText = text;
//	//text.toCharArray(buttonText,10);
//	textColor = text_Color;
//
//	activeColor = back_Color;
//	backColor = back_Color;
//
//	borderColor = border_Color;
//
//	buttonStyle = style;
//	page = PAGE;
//
//	pressedColor.red = 200;
//	pressedColor.green = 255;
//	pressedColor.blue = 0;
//
//	runningColor.red = 192;
//	runningColor.green = 150;
//	runningColor.blue = 0;
//
//	myFont = SmallFont;
//
//	paintButton();
//}


void Touchbutton::drawButton(int x_Center, int y_Center, char * text, _Color text_Color, _Color back_Color, _Color border_Color, char style, char PAGE, uint8_t * _myFont)
{
	xCenter = x_Center;
	yCenter = y_Center;
	buttonStyle = style;

	buttonText = text;
	//text.toCharArray(buttonText,10);
	textColor = text_Color;

	activeColor = back_Color;
	backColor = back_Color;

	borderColor = border_Color;

	buttonStyle = style;
	page = PAGE;

	pressedColor.red = 200;
	pressedColor.green = 255;
	pressedColor.blue = 0;

	runningColor.red = 192;
	runningColor.green = 150;
	runningColor.blue = 0;

	myFont = _myFont;

	paintButton();
}



void Touchbutton::changeText(String text)
{
	text.toCharArray(buttonText,10);
	paintButton();
}

// Draw Button to Grid
//  ____________________
// |                    |
// |    0   1   2   3   |
// |    4   5   6   7   |
// |    8   9   10  11  |
// |    12  13  14  15  |
// |____________________|
//
//void Touchbutton::drawButton(int grid, char * text, _Color text_Color, _Color back_Color, _Color border_Color, char style)
//{
//	xCenter = (myLCD->getDisplayXSize() / 4) *( grid % 4);
//	yCenter = (myLCD->getDisplayYSize() / 4) *( grid / 3);
//
//	buttonStyle = style;
//	buttonText = text;
//	textColor = text_Color;
//	activeColor = back_Color;
//	backColor = back_Color;
//	borderColor = border_Color;
//	buttonStyle = style;
//
//	paintButton();
//}

void Touchbutton::paintButton()
{
	myLCD->setFont(myFont);

	int length = 0;
	for(int i = 0; i<10; i++)
	{
		length = i;

		if((buttonText[i] == ' ')||(buttonText[i] == 0))
		{
			i = 11;
		}
	}
	int letterwidth = (myLCD->cfont.x_size / 2);

	switch( buttonStyle)
	{

		//	 ___
		//	|___)
		//
	case 0:	//right LCARS Button
		//draw Border
		myLCD->setFont(SmallFont);
		myLCD->setColor(borderColor.red,borderColor.green,borderColor.blue);
		myLCD->drawRect(xCenter - ButtonSize-1 ,yCenter - ButtonSize-1 ,xCenter + ButtonSize+1,yCenter + ButtonSize+1);
		myLCD->drawCircle(xCenter + ButtonSize, yCenter, ButtonSize+1);

		//draw Background
		myLCD->setColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->fillRect(xCenter - ButtonSize,yCenter - ButtonSize,xCenter + ButtonSize,yCenter + ButtonSize+1);
		myLCD->fillCircle(xCenter + ButtonSize, yCenter, ButtonSize);

		//print Text
		myLCD->setBackColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->setColor(textColor.red,textColor.green,textColor.blue);
		myLCD->print(buttonText, xCenter - (length * letterwidth ), yCenter - (myLCD->cfont.y_size / 2));
		break;

		//	 ___
		//	(___|
		//
	case 1:	//left LCARS Button
		//draw Border
		myLCD->setFont(SmallFont);
		myLCD->setColor(borderColor.red,borderColor.green,borderColor.blue);
		myLCD->drawRect(xCenter - ButtonSize-1 ,yCenter - ButtonSize-1 ,xCenter + ButtonSize+1,yCenter + ButtonSize+1);
		myLCD->drawCircle(xCenter - ButtonSize, yCenter, ButtonSize+1);

		//draw Background
		myLCD->setColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->fillRect(xCenter - ButtonSize,yCenter - ButtonSize,xCenter + ButtonSize,yCenter + ButtonSize+1);
		myLCD->fillCircle(xCenter - ButtonSize, yCenter, ButtonSize);

		//print Text
		myLCD->setBackColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->setColor(textColor.red,textColor.green,textColor.blue);
		myLCD->print(buttonText, xCenter - (length * letterwidth ) , yCenter - (myLCD->cfont.y_size / 2));
		break;

		//	 ________
		//	|________|
		//
	case 2:	//Center LCARS Button

		//#define ButtonLenght 65
		//draw Border
		myLCD->setColor(borderColor.red,borderColor.green,borderColor.blue);
		myLCD->drawRect(xCenter - TitleButtonLenght-1 ,yCenter - ButtonSize-1 ,xCenter + TitleButtonLenght+1,yCenter + ButtonSize+1);

		//draw Background
		myLCD->setColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->fillRect(xCenter - TitleButtonLenght , yCenter - ButtonSize,xCenter + TitleButtonLenght , yCenter + ButtonSize+1);

		//print Text
		myLCD->setBackColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->setColor(textColor.red,textColor.green,textColor.blue);
		myLCD->print(buttonText, xCenter - (length * letterwidth ), yCenter - (myLCD->cfont.y_size / 2));

		//#undef ButtonLenght
		break;

		//	 _____
		//	(_____)
		//
	case 3:	//Round flat LCARS Button

		//draw Border
		myLCD->setColor(borderColor.red,borderColor.green,borderColor.blue);
		myLCD->drawRect(xCenter - ButtonLenght-1 ,yCenter - ButtonSize-1 ,xCenter + ButtonLenght+1,yCenter + ButtonSize+1);

		myLCD->drawCircle(xCenter - ButtonLenght, yCenter, ButtonSize+1);
		myLCD->drawCircle(xCenter + ButtonLenght, yCenter, ButtonSize+1);

		//draw Background
		myLCD->setColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->fillRect(xCenter - ButtonLenght,yCenter - ButtonSize,xCenter + ButtonLenght,yCenter + ButtonSize+1);

		myLCD->fillCircle(xCenter - ButtonLenght, yCenter, ButtonSize);
		myLCD->fillCircle(xCenter + ButtonLenght, yCenter, ButtonSize);

		//print Text
		myLCD->setBackColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->setColor(textColor.red,textColor.green,textColor.blue);
		myLCD->print(buttonText, xCenter - (length * letterwidth), yCenter - (myLCD->cfont.y_size / 2));
	
		break;

		//	 _
		//	/ \
		//	| |
		//	\_/
		//
	case 4:	//Round hight LCARS Button

		break;

		//	 _
		//	(_)
		//
	case 5:	//Round LCARS Button

		//draw Border
		myLCD->setColor(borderColor.red,borderColor.green,borderColor.blue);
		myLCD->drawCircle(xCenter, yCenter, ButtonSize+1);

		//draw Background
		myLCD->setColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->fillCircle(xCenter, yCenter, ButtonSize);

		//print Text
		myLCD->setBackColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->setColor(textColor.red,textColor.green,textColor.blue);
		myLCD->print(buttonText, xCenter - letterwidth, yCenter - (myLCD->cfont.y_size / 2));

		break;

		//	 __
		//  (  )
		//	 \/
	case 6:	//Round LCARS Button

		//draw Border
		myLCD->setColor(borderColor.red,borderColor.green,borderColor.blue);
		myLCD->drawCircle(xCenter, yCenter, ButtonSize+1);
		//myLCD->drawLine();


		//draw Background
		myLCD->setColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->fillCircle(xCenter, yCenter, ButtonSize);


		//print Text
		myLCD->setBackColor(activeColor.red,activeColor.green,activeColor.blue);
		myLCD->setColor(textColor.red,textColor.green,textColor.blue);
		myLCD->print(buttonText, xCenter - letterwidth, yCenter - (myLCD->cfont.y_size / 2));

		break;

	}
}

#define Touchdistance 20

bool Touchbutton::TouchInput(int xInput, int yInput)
{
	if ((xInput > xCenter-Touchdistance) && (xInput < xCenter+Touchdistance))
	{
		if ((yInput > yCenter-Touchdistance) && (yInput < yCenter+Touchdistance))
		{
			if(pressed == false)
			{
				ticker++;
				pressed = true;
				pressedSignal();
				return true;
			}
			else
			{
				ticker++;
				if(ticker >5)
				{
					ticker = 0;
					return true;
				}
				return false;
			}
		}
	}
	if(pressed)
	{
		pressed = false;
		pressedSignal();
	}

	pressed = false;
	return false;
}

bool Touchbutton::TouchInput(int xInput, int yInput, char Page)
{
	if((page!= 0)&&(Page == page))
	{
		if ((xInput > xCenter-Touchdistance) && (xInput < xCenter+Touchdistance))
		{
			if ((yInput > yCenter-Touchdistance) && (yInput < yCenter+Touchdistance))
			{
				if(pressed == false)
				{
					ticker++;
					pressed = true;
					pressedSignal();
					return true;
				}
				else
				{
					ticker++;
					if(ticker >2)
					{
						ticker = 0;
						return true;
					}
					return false;
				}
			}
		}

		if(pressed)
		{
			pressed = false;
			pressedSignal();
		}
	}
	pressed = false;
	return false;
}

void Touchbutton::pressedSignal()
{
	if(pressed)
	{
		activeColor = pressedColor;
	}
	else
	{
		activeColor = backColor;
	}

	paintButton();
}

void Touchbutton::selectButton(bool select)
{
	if(select)
	{
		activeColor = runningColor;
	}
	else
	{
		activeColor = backColor;
	}
	selected = select;
	paintButton();
}
void Touchbutton::setFont(uint8_t* font)
{
	myFont = font;
	myLCD->setFont(myFont);
}