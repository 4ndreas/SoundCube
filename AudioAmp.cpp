#include "AudioAmp.h"
#include <Arduino.h>
#include <Wire.h>
#include <pins_arduino.h>

AudioAmp::AudioAmp()
{
}

void AudioAmp::Init(char I2C_Addr, char Mute, char Enable)
{
	ADDRESS = I2C_Addr;
	EnablePin = A3;
	MutePin = A4;

	pinMode(EnablePin, OUTPUT);
	pinMode(MutePin, OUTPUT);

	digitalWrite(EnablePin, LOW);	// disable
	digitalWrite(MutePin, LOW);	// Mute 

	Wire.begin();
	Wire.beginTransmission(ADDRESS);
	Wire.write(63);
	Wire.endTransmission();
}

//
// set MasterVolume vom 0(=Mute) to 100 % 
int AudioAmp::setVolume(int Vol)
{
	if((Vol <= 100)&&(Vol >= 0))
	{
		volx = Vol;
		Wire.beginTransmission(ADDRESS);
		Wire.write(volume(volx));  
		Wire.endTransmission();
	}
	unMute();
	return volx;
}


int AudioAmp::getVolume()
{
	return volx;
}

// set volume in -dB range (0 to -78,75) in 1.25 steps
char AudioAmp::volume(int VOLUME)
{
	char temp = (char)VOLUME;

	temp = (char)map(VOLUME,0,100,0,63);
	temp = 63-temp;

	return temp;
}

#define MaxValue 32
// Set the Gain for all 4 speakers
// Range from 0 Max gain to 8(=-15dB)
int AudioAmp::setSpeaker(int SpeakerGain)
{
	int temp = 0;

	if((SpeakerGain <= MaxValue)&&(SpeakerGain >= 0))
	{
	gSpeakerGain = SpeakerGain;

	speakerGain[0] = MaxValue - SpeakerGain;
	speakerGain[1] = MaxValue - SpeakerGain;
	speakerGain[2] = MaxValue - SpeakerGain;
	speakerGain[3] = MaxValue - SpeakerGain;



	Wire.beginTransmission(ADDRESS);
	Wire.write(SpeakerATT(1,speakerGain[0]));
	Wire.write(SpeakerATT(2,speakerGain[1]));
	Wire.write(SpeakerATT(3,speakerGain[2]));
	Wire.write(SpeakerATT(4,speakerGain[3]));
	Wire.endTransmission();

	}
	return gSpeakerGain;
}
#undef MaxValue

// Config the single speakers:
// Speaker 1-4
// Gain Range 0% (=-38,75dB to 100 %(=0dB)
// 0 => Mute
char AudioAmp::SpeakerATT(int Speaker, int Gain)
{
	char temp = 0;
	if(Speaker == 1){
		temp = 0b10000000;}

	else if(Speaker == 2){
		temp = 0b10100000;}

	else if(Speaker == 3){
		temp = 0b11000000;}

	else if(Speaker == 4){
		temp = 0b11100000;}

	temp += Gain ; // (byte)map(Gain,0,100,0,31);

	return temp;
}


void AudioAmp::setInput(int inp, int iGain)
{
	if((inp>=0) && (inp < 4))
	{
		input = inp;
		if((iGain >= 0) && (iGain < 4))
		{
			
			inputGain[input] = iGain;

			Wire.beginTransmission(ADDRESS);
			Wire.write(AudioSwitch(input,inputGain[input]));  
			Wire.endTransmission();
		}
		else 
		{
			inputGain[input] = 3;	// min Value if err
		}
	}
}

void AudioAmp::setInputGain(int iGain)
{
	if((iGain>=0) &&(iGain<4))
	{
		inputGain[input] = iGain;

		Wire.beginTransmission(ADDRESS);
		Wire.write(AudioSwitch(input,inputGain[input]));  
		Wire.endTransmission();
	}
		else 
		{
			inputGain[input] = 3;	// min Value if err
		}
}


char AudioAmp::AudioSwitch(int Channel, int Gain)
{
	input = Channel;
	inputGain[input] = Gain;

	// Gain 0 - 3
	// Channel 0 -3
	char temp = 0b01000000; // MSB 010

	temp += ((3-Gain)<<3);

	temp += Channel;

	return temp;

}

// Value from -14 to 14 in steps of 2
char AudioAmp::BassControl(int Value)
{

	char temp = (96); //MSB 0110
	
	if(Value >0)
	{
		temp += 8;
		temp +=(7-Value);
	}
	else
	{
		temp +=(7+Value);
	}

	return temp; 
}

char AudioAmp::TrebleControl(int Value)
{
	char temp = (112); //MSB 0111
	if(Value >0)
	{
		temp += 8;
		temp +=(7-Value);
	}
	else
	{
		temp +=(7+Value);
	}
	return temp;
}

void AudioAmp::Mute()
{
	digitalWrite(MutePin, LOW);
}

void AudioAmp::unMute()
{
	digitalWrite(MutePin, HIGH);
}

void AudioAmp::Sleep()
{
	digitalWrite(EnablePin, LOW);
}

void AudioAmp::Enable()
{
	digitalWrite(EnablePin, HIGH);
}

#define MaxValue 7

int AudioAmp::setBass(int value)
{
	if((value <= MaxValue)&&(value >= -MaxValue))
	{
	Bass = value;
		Wire.beginTransmission(ADDRESS);
		Wire.write(BassControl(Bass));  
		Wire.endTransmission();
	}
	return Bass;
}

int AudioAmp::setTreble(int value)
{
	if((value <= MaxValue)&&(value >= -MaxValue))
	{
	Treble = value;
		Wire.beginTransmission(ADDRESS);
		Wire.write(TrebleControl(Treble));  
		Wire.endTransmission();
	}
	return Treble;
}
#undef MaxValue