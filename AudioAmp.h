#ifndef AudioAmp_h
#define AudioAmp_h

class AudioAmp
{
public:
	AudioAmp();
	void Init(char I2C_Addr, char Mute, char Enable);
	int setVolume(int Vol);
	int setBass(int value);
	int setTreble(int value);
	int getVolume();
	int channel;

	int setSpeaker(int SpeakerGain);
	char SpeakerATT(int Speaker, int Gain);


	void setInput(int inp, int iGain);
	void setInputGain(int iGain);

	int speakerGain[4];

	int input;
	int inputGain[4];

	void Mute();
	void unMute();
	void Sleep();
	void Enable();
	
protected:
	char ADDRESS;
	int volx;
	int Treble;
	int Bass;
	int EnablePin;
	int MutePin;
	int gSpeakerGain;

	char volume(int VOLUME); // set volume in -dB range (0 to -78,75) in 1.25 steps
	char AudioSwitch(int Channel, int Gain);
	char BassControl(int Value);
	char TrebleControl(int Value);
};

#endif











