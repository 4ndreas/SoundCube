

#ifndef MENUEGRID_H
#define MENUEGRID_H

#include <Arduino.h>
#include <UTFT.h>
#include <ITDB02_Touch.h>
#include "Touchbutton.h"
#include "ProgressBar.h"
#include "ProgressBar.h"

const _Color ButtonBackColor = {255,110,0};
const _Color ButtonBorderColor = {255,255,0};
const _Color ButtonTextColor = {255,255,255};
const _Color ProgressColor = {100,0,255};

class MenueGrid
{
public:
	MenueGrid();
	void Init(UTFT *gLCD);
	void setPage(int Page);
	int maxPages;
	
	void nextPage();
	void prevPage();
	int page;

	void touchInput(int tx, int ty);

	//Buttons
	Touchbutton LeftButton;
	Touchbutton RightButton;
	Touchbutton CenterButton;
	// Volume Page + Batterie Voltage
	Touchbutton Volup;
	Touchbutton Voldown;
	Touchbutton Mute;
	ProgressBar VolumeBar;
	int Volume;
	int Voltage;
	ProgressBar VoltageBar;

	// Input Page
	Touchbutton InputButton1; 
	Touchbutton InputButton2;
	Touchbutton InputButton3;
	Touchbutton InputButton4;
	Touchbutton	InputGainUp;
	Touchbutton InputGainDown;

	// Bass/Treble Controll 
	Touchbutton Bassup;
	Touchbutton Bassdown;
	ProgressBar BassBar;

	Touchbutton Trebleup;
	Touchbutton Trebledown;
	ProgressBar TrebleBar;

	// Speaker Set
	Touchbutton SpeakerGainUp;
	Touchbutton SpeakerGainDown;
	ProgressBar SpeakerGainBar;


	// Settings

	Touchbutton ResetButton;
	Touchbutton SaveButton;

protected:
	UTFT *myLCD;
};
#endif