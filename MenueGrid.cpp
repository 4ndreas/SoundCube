#include "MenueGrid.h"

MenueGrid::MenueGrid()
{
}

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

void MenueGrid::Init(UTFT *gLCD)
{
	myLCD = gLCD;
	maxPages = 5;
	page = 1;

	CenterButton.Init(myLCD);
	CenterButton.setFont(SmallFont);

	RightButton.Init(myLCD);
	LeftButton.Init(myLCD);

	//RightButton.setFont(SmallFont);
	RightButton.drawButton(myLCD->getDisplayXSize() -50, 30 ,"next",ButtonTextColor,ButtonBackColor,ButtonBorderColor,0);
	//LeftButton.setFont(SmallFont);
	LeftButton.drawButton(50, 30 ,"back",ButtonTextColor,ButtonBackColor,ButtonBorderColor, 1);

	Volup.Init(myLCD);
	Voldown.Init(myLCD);
	VolumeBar.Init(myLCD);
	Mute.Init(myLCD);
	VoltageBar.Init(myLCD);


	// Input selection
	InputButton1.Init(myLCD);
	InputButton2.Init(myLCD);
	InputButton3.Init(myLCD);
	InputButton4.Init(myLCD);
	InputGainUp.Init(myLCD);
	InputGainDown.Init(myLCD);


	// Tone Ctr
	Bassup.Init(myLCD);
	Bassdown.Init(myLCD);
	BassBar.Init(myLCD);

	Trebleup.Init(myLCD);
	Trebledown.Init(myLCD);
	TrebleBar.Init(myLCD);

	//Speaker Gain page
	SpeakerGainUp.Init(myLCD);
	SpeakerGainDown.Init(myLCD);
	SpeakerGainBar.Init(myLCD);

	//Settings
	ResetButton.Init(myLCD);
	SaveButton.Init(myLCD);

	setPage(1);
}

// setMenue to Page
// 0 = Clean Menue Stripe
// 1 = Volume Page + Batterie Voltage
// 2 = Input Select
// 3 = Bass/Treble Controll 
// 4 = Speaker Set
// 5 = Settings
void MenueGrid::setPage(int Page)
{
	if (Page != 0)	// never stay at 0
	{
	page = Page;
	}

	switch (Page)
	{
		// Clean Page
	case 0:

		myLCD->setColor(0,0,0);
		myLCD->fillRect(0,55,myLCD->getDisplayXSize(),myLCD->getDisplayYSize());

		break;

		// Volume Page + Batterie Voltage
	case 1:
		setPage(0);	//clear
			
		CenterButton.drawButton(myLCD->getDisplayXSize() / 2, 30 ,"Volume",ButtonTextColor,ButtonBackColor,ButtonBorderColor,2,0,BigFont);

		//Volup.setFont(BigFont);
		Volup.drawButton(myLCD->getDisplayXSize() -50, 130 ,"+",ButtonTextColor,ButtonBackColor,ButtonBorderColor,0,1,BigFont);
		//Voldown.setFont(BigFont);
		Voldown.drawButton(50, 130 ,"-",ButtonTextColor,ButtonBackColor,ButtonBorderColor, 1,1,BigFont);

		//Mute.setFont(BigFont);
		Mute.drawButton(53,200,"Mute",ButtonTextColor,ButtonBackColor,ButtonBorderColor,3,1,BigFont);

		VolumeBar.drawButton(myLCD->getDisplayXSize() / 2, 130 ,ButtonTextColor,ProgressColor,ButtonBorderColor,VolumeBar.getValue());
		//VoltageBar.drawButton(200, 200 ,ButtonTextColor,ProgressColor,ButtonBorderColor,VoltageBar.getValue());

		break;

		//Input Select
	case 2:
		setPage(0);	//clear

		// draw Menue Text stripe
		CenterButton.drawButton(myLCD->getDisplayXSize() / 2, 30 ,"Input",ButtonTextColor,ButtonBackColor,ButtonBorderColor,2,0,BigFont);
		// draw Buttons

		InputButton1.drawButton(53,130,"Input 1",ButtonTextColor,ButtonBackColor,ButtonBorderColor,3,2);
		InputButton2.drawButton(53,200,"Input 2",ButtonTextColor,ButtonBackColor,ButtonBorderColor,3,2);
		InputButton3.drawButton(myLCD->getDisplayXSize() - 53,130,"Bluetooth",ButtonTextColor,ButtonBackColor,ButtonBorderColor,3,2);
		InputButton4.drawButton(myLCD->getDisplayXSize() - 53,200,"NC",ButtonTextColor,ButtonBackColor,ButtonBorderColor,3,2);

		InputGainUp.drawButton(160,130,"+",ButtonTextColor,ButtonBackColor,ButtonBorderColor,5,2);
		InputGainDown.drawButton(160,200,"-",ButtonTextColor,ButtonBackColor,ButtonBorderColor,5,2);

		break;

		// Bass/Treble Controll 
	case 3:
		setPage(0);	//clear

		// draw Menue Text stripe
		CenterButton.drawButton(myLCD->getDisplayXSize() / 2, 30 ,"ToneCrl",ButtonTextColor,ButtonBackColor,ButtonBorderColor,2,0,BigFont);

		//Bassup.setFont(BigFont);
		Bassup.drawButton(myLCD->getDisplayXSize() -50, 130 ,"+",ButtonTextColor,ButtonBackColor,ButtonBorderColor,0,3,BigFont);
		//Bassdown.setFont(BigFont);
		Bassdown.drawButton(50, 130 ,"-",ButtonTextColor,ButtonBackColor,ButtonBorderColor, 1,3,BigFont);

		BassBar.drawButton(myLCD->getDisplayXSize() / 2, 130 ,ButtonTextColor,ProgressColor,ButtonBorderColor,BassBar.getValue(),3,14,7);

		//Trebleup.setFont(BigFont);
		Trebleup.drawButton(myLCD->getDisplayXSize() -50, 200 ,"+",ButtonTextColor,ButtonBackColor,ButtonBorderColor,0,3,BigFont);
		//Trebledown.setFont(BigFont);
		Trebledown.drawButton(50, 200 ,"-",ButtonTextColor,ButtonBackColor,ButtonBorderColor, 1,3,BigFont);

		TrebleBar.drawButton(myLCD->getDisplayXSize() / 2, 200 ,ButtonTextColor,ProgressColor,ButtonBorderColor,TrebleBar.getValue(),3,14,7);

		break;

		//Speaker Set
	case 4:
		setPage(0);	//clear

		// draw Menue Text stripe
		CenterButton.drawButton(myLCD->getDisplayXSize() / 2, 30 ,"Speaker",ButtonTextColor,ButtonBackColor,ButtonBorderColor,2,0,BigFont);

		SpeakerGainUp.setFont(BigFont);
		SpeakerGainUp.drawButton(myLCD->getDisplayXSize() -50, 130 ,"+",ButtonTextColor,ButtonBackColor,ButtonBorderColor,0,4);
		//SpeakerGainDown.setFont(BigFont);
		SpeakerGainDown.drawButton(50, 130 ,"-",ButtonTextColor,ButtonBackColor,ButtonBorderColor, 1,4);

		SpeakerGainBar.drawButton(myLCD->getDisplayXSize() / 2, 130 ,ButtonTextColor,ProgressColor,ButtonBorderColor,SpeakerGainBar.getValue(),4,32,0);
		break;

		//Settings
	case 5:
		setPage(0);	//clear

		// draw Menue Text stripe
		CenterButton.drawButton(myLCD->getDisplayXSize() / 2, 30 ,"Settings",ButtonTextColor,ButtonBackColor,ButtonBorderColor,2,0,BigFont);
		
		ResetButton.drawButton(53,130,"Reset",ButtonTextColor,ButtonBackColor,ButtonBorderColor,3,5,BigFont);
		SaveButton.drawButton(53,200,"Save",ButtonTextColor,ButtonBackColor,ButtonBorderColor,3,5,BigFont);

		break;
	}
}

void MenueGrid::nextPage()
{
	page++;

	if (page > maxPages)
	{
		page = 1;
	}
	setPage(page);
}

void MenueGrid::prevPage()
{
	page--;

	if (page <= 0)
	{
		page = maxPages;
	}
	setPage(page);
}
