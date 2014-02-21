#include "MenueGrid.h"
#include "Touchbutton.h"
#include <Wire.h>

//This requires the UTFT TFT and Touch library
// http://henningkarlsen.com/electronics/library.php?id=52

#include <UTFT.h>
#include <ITDB02_Touch.h>
//#include <avr/wdt.h>

#include "AudioAmp.h"
#include "Touchbutton.h"
#include "ProgressBar.h"
#include "MenueGrid.h"
#include <EEPROM.h>

#define SerialOut

MenueGrid Menue;

// Declare which fonts we will be using
extern uint8_t SmallFont[];
//#define BigFont SmallFont
extern uint8_t BigFont[];

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

UTFT myGLCD(ITDB32S,38,39,40,41);   
//myTouch(TCLK,TCS,DIN,DOUT,IRQ);
ITDB02_Touch  myTouch(6,5,4,3,2);

#else
// Uncomment the next line for Arduino 2009/Uno
//myGLCD(RS,WR,CS,RST,ALE,mode);
UTFT myGLCD(A1,A2,A0,A3,A5,ITDB32S);
//myTouch(TCLK,TCS,DIN,DOUT,IRQ);
ITDB02_Touch  myTouch(13,10,11,12,A4);
#endif


#ifdef SerialOut
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

#endif

const char TDA7318_ADDRESS = 0b1000100;

AudioAmp myAmp;

int MainVolume = 50;
int Treble = 0;
int Bass = 0;
int SpeakerGain = 15;

void setup()
{
	//wdt_disable();

	// Setup the LCD
	myGLCD.InitLCD(1);

	myGLCD.clrScr();

	myGLCD.setFont(SmallFont);

	myTouch.InitTouch(1);
	myTouch.setPrecision(PREC_LOW);


#ifdef SerialOut
	Serial.begin(9600);  // start serial for output

	inputString.reserve(20);
#endif
	// Load Saved Data

	 MainVolume = EEPROM.read(0);
	 Treble = EEPROM.read(1);
	 Bass = EEPROM.read(2);
	 SpeakerGain = EEPROM.read(3);

	 myAmp.input = EEPROM.read(4);
	 myAmp.inputGain[0] = EEPROM.read(5);
	 myAmp.inputGain[1] = EEPROM.read(6);
	 myAmp.inputGain[2] = EEPROM.read(7);
	 myAmp.inputGain[3] = EEPROM.read(8);

	Menue.Init(&myGLCD);

	myAmp.Init(TDA7318_ADDRESS,A4,A3); 
	myAmp.setVolume(MainVolume);
	myAmp.setSpeaker(SpeakerGain);
	myAmp.setInput(myAmp.input,myAmp.inputGain[myAmp.input]);
	myAmp.setBass(Bass);
	myAmp.setTreble(Treble);
	myAmp.Enable();
	myAmp.unMute();

	Menue.SpeakerGainBar.setValue(SpeakerGain);
	Menue.VolumeBar.setValue(MainVolume);
	Menue.BassBar.setValue(Bass);
	Menue.TrebleBar.setValue(Treble);

	
	debug("Start:", 0);
	Menue.setPage(1);
	
}
int TimeOut = 0;
int sensorValue = 200;

void loop()
{
#ifdef SerialOut
	if (stringComplete) {
		if(inputString.charAt(0) == 'v')
		{
			inputString.replace('v', '0');
			MainVolume = inputString.toInt();

			Menue.VolumeBar.setValue(MainVolume);
			myAmp.setVolume(MainVolume);
			myAmp.Enable();

			debug("Volume:", MainVolume);
		}

		if(inputString.charAt(0) == 'r')
		{

		}
		if(inputString.charAt(0) == 's')
		{
			myAmp.Sleep();
		}
		inputString = "";
		stringComplete = false;
	}

  sensorValue += analogRead(A0);
  sensorValue/= 2;

  float Voltage = sensorValue * 0.0548;
  Voltage += 0.7;

  // print out the value you read:
  //Serial.print(sensorValue);
  //Serial.print(" ");
  //Serial.println(Voltage);


  if(Menue.page == 1)
  {
	//String Voltagestring = sprint(Voltage);
	//myGLCD.printNumI(sensorValue,myGLCD.getDisplayXSize()-100,myGLCD.getDisplayYSize()-50,4);

	  myGLCD.setFont(BigFont);
	  myGLCD.setBackColor(0,0,0);
	  myGLCD.setColor(255,255,255);
	  myGLCD.printNumF(Voltage,2,myGLCD.getDisplayXSize()-110,myGLCD.getDisplayYSize()-50);
	  myGLCD.print("V",myGLCD.getDisplayXSize()-20,myGLCD.getDisplayYSize()-50);
  }

#endif
	int gx = 0;
	int gy = 0;

	delay(50);

	TimeOut++;
	if (TimeOut > 200)
	{
		myGLCD.lcdOff();
		TimeOut = 0;
	}

	if(myTouch.dataAvailable())
	{
		myTouch.read();

		gx = map(myTouch.TP_Y, 3900,300,320,0);
		gy = map(myTouch.TP_X,  3900, 220,240,0);
		myGLCD.lcdOn();
		TimeOut = 0;
	}

	if(Menue.LeftButton.TouchInput(gx, gy))
	{
		Menue.prevPage();
		//debug("Page:", Menue.page);
	}

	if(Menue.RightButton.TouchInput(gx, gy))
	{
		Menue.nextPage();
		//debug("Page:", Menue.page);
	}

	if(Menue.CenterButton.TouchInput(gx, gy))
	{
		//Serial.println("CenterButton");
	}

	if(Menue.Volup.TouchInput(gx, gy,Menue.page))
	{
		myAmp.unMute();
		MainVolume = myAmp.setVolume(++MainVolume);
		Menue.VolumeBar.setValue(MainVolume);

		debug("Volume:", MainVolume);
	}

	if(Menue.Voldown.TouchInput(gx, gy,Menue.page))
	{	
		myAmp.unMute();
		MainVolume = myAmp.setVolume(--MainVolume);
		Menue.VolumeBar.setValue(MainVolume);

		debug("Volume:", MainVolume);
	}

	if(Menue.Mute.TouchInput(gx, gy,Menue.page))
	{
		myAmp.Mute();
		Menue.VolumeBar.setValue(0);
		debug("Mute", MainVolume);
	}


	// Input Selection
	if(Menue.InputButton1.TouchInput(gx, gy,Menue.page))
	{
		myAmp.setInput(0,myAmp.inputGain[0]);
		debug("Input:", 0,"Gain:",myAmp.inputGain[0]);
	}
	if(Menue.InputButton2.TouchInput(gx, gy,Menue.page))
	{
		myAmp.setInput(1,myAmp.inputGain[1]);
		debug("Input:", 1, "Gain:",myAmp.inputGain[1]);
	}
	if(Menue.InputButton3.TouchInput(gx, gy,Menue.page))
	{
		myAmp.setInput(2,myAmp.inputGain[2]);
		debug("Bluetooth", 2,"Gain:",myAmp.inputGain[2]);
	}
	if(Menue.InputButton4.TouchInput(gx, gy,Menue.page))
	{
		myAmp.setInput(3,myAmp.inputGain[3]);
		debug("Input:", 3,"Gain:",myAmp.inputGain[3]);
	}

	if(Menue.InputGainUp.TouchInput(gx, gy,Menue.page))
	{
		int temp = (myAmp.inputGain[myAmp.input]);
		temp++;

		myAmp.setInputGain(temp);
		debug("Input:", myAmp.input,"Gain:",myAmp.inputGain[myAmp.input]);
	}

	if(Menue.InputGainDown.TouchInput(gx, gy,Menue.page))
	{
		int temp = (myAmp.inputGain[myAmp.input]);
		temp--;

		myAmp.setInputGain(temp);
		debug("Input:", myAmp.input,"Gain:",myAmp.inputGain[myAmp.input]);
	}


	// Page 3

	if(Menue.Trebleup.TouchInput(gx, gy,Menue.page))
	{

		Treble = myAmp.setTreble(++Treble);
		Menue.TrebleBar.setValue(Treble);

		debug("Treble:", Treble);
	}

	if(Menue.Trebledown.TouchInput(gx, gy,Menue.page))
	{	

		Treble = myAmp.setTreble(--Treble);
		Menue.TrebleBar.setValue(Treble);

		debug("Treble:", Treble);
	}

	if(Menue.Bassup.TouchInput(gx, gy,Menue.page))
	{
		Bass = myAmp.setBass(++Bass);
		Menue.BassBar.setValue(Bass);

		debug("Bass:", Bass);
	}

	if(Menue.Bassdown.TouchInput(gx, gy,Menue.page))
	{	
		Bass = myAmp.setBass(--Bass);
		Menue.BassBar.setValue(Bass);

		debug("Bass:", Bass);
	}

	// Speaker Gain
	if(Menue.SpeakerGainUp.TouchInput(gx, gy,Menue.page))
	{
		SpeakerGain = myAmp.setSpeaker(++SpeakerGain);
		Menue.SpeakerGainBar.setValue(SpeakerGain);

		debug("Gain:", SpeakerGain);
	}
	
	if(Menue.SpeakerGainDown.TouchInput(gx, gy,Menue.page))
	{	
		SpeakerGain = myAmp.setSpeaker(--SpeakerGain);
		Menue.SpeakerGainBar.setValue(SpeakerGain);

		debug("Gain:", SpeakerGain);
	}


	//settings 
	if(Menue.ResetButton.TouchInput(gx, gy,Menue.page))
	{
		//wdt_enable(WDTO_4S);

		debug("Reset", 1);
	}
	if(Menue.SaveButton.TouchInput(gx, gy,Menue.page))
	{
		EEPROM.write(0, MainVolume);
		EEPROM.write(1, Treble);
		EEPROM.write(2, Bass);
		EEPROM.write(3, SpeakerGain);


		EEPROM.write(4, myAmp.input);
		EEPROM.write(5, myAmp.inputGain[0]);
		EEPROM.write(6, myAmp.inputGain[1]);
		EEPROM.write(7, myAmp.inputGain[2]);
		EEPROM.write(8, myAmp.inputGain[3]);

		debug("Saved", 1);
	}
}

void showText(char msg[15], int val)
{
myGLCD.setColor(0,0,0);
myGLCD.fillRect(0,55,myGLCD.getDisplayXSize(),90);

myGLCD.print(msg,10,70);
myGLCD.printNumI(val, myGLCD.getDisplayXSize() -50, 70);
}

#ifdef SerialOut
/*
SerialEvent occurs whenever a new data comes in the
hardware serial RX.  This routine is run between each
time loop() runs, so using delay inside loop can delay
response.  Multiple bytes of data may be available.
*/
void serialEvent() {
	while (Serial.available()) {
		// get the new byte:
		char inChar = (char)Serial.read(); 
		// add it to the inputString:
		inputString += inChar;
		// if the incoming character is a newline, set a flag
		// so the main loop can do something about it:
		if (inChar == '\n') {
			stringComplete = true;
		} 
	}
}
#endif

void debug(char name[10], int var)
{
#ifdef SerialOut
	Serial.print(name);
	Serial.print(" ");
	Serial.println(var);
#endif
	myGLCD.setColor(0,0,0);
	myGLCD.fillRect(0,60,myGLCD.getDisplayXSize(),100);

	myGLCD.setFont(BigFont);
	myGLCD.setBackColor(0,0,0);
	myGLCD.setColor(255,255,255);
	myGLCD.print(name,10,70);
	myGLCD.printNumI(var, myGLCD.getDisplayXSize() -50, 70);
}

void debug(char name[10], int var,char name2[10], int var2)
{
#ifdef SerialOut
	Serial.print(name);
	Serial.print(" ");
	Serial.println(var);
#endif
	myGLCD.setColor(0,0,0);
	myGLCD.fillRect(0,60,myGLCD.getDisplayXSize(),100);

	myGLCD.setFont(BigFont);
	myGLCD.setBackColor(0,0,0);
	myGLCD.setColor(255,255,255);
	myGLCD.print(name,10,70);
	myGLCD.printNumI(var, 140 , 70);
	myGLCD.print(name2,myGLCD.getDisplayXSize() -130,70);
	myGLCD.printNumI(var2, myGLCD.getDisplayXSize() -40, 70);
}
