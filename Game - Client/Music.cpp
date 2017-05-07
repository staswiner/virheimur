#include "Music.h"



Music::Music()
{
}


Music::~Music()
{
}

void Music::Initialize()
{
	// READ FILE
	//alutInit(0, NULL);
	FILE * file;
	fopen_s(&file, R"(D:\Users\stasw\Documents\virheimur\Game - Client\Soundtracks\Perion.wav)", "rb");
	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;
	fread(type, sizeof(char), 1, file);
	fread(&size, sizeof(DWORD), 4, file);
	fread(type, sizeof(char), 4, file);
	fread(type, sizeof(char), 4, file);

	fread(&chunkSize, sizeof(DWORD), 1, file);
	fread(&formatType, sizeof(short), 1, file);
	fread(&channels, sizeof(short), 1, file);
	fread(&sampleRate, sizeof(DWORD), 1, file);
	fread(&avgBytesPerSec, sizeof(DWORD), 1, file);
	fread(&bytesPerSample, sizeof(short), 1, file);
	fread(&bitsPerSample, sizeof(short), 1, file);

	fread(type, sizeof(char), 4, file);
	fread(&dataSize, sizeof(DWORD), 1, file);

	unsigned char* buf = new unsigned char[dataSize];
	fread(buf, sizeof(BYTE), dataSize, file);

	// INITIALIZE AL
	ALCdevice *device;
	ALCcontext *context;
	device = alcOpenDevice(NULL);
	if (!device)
	{

		int i = 0;
	}
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	if (!context) {
		int i = 0;
	}

	ALuint frequency = sampleRate;
	ALuint format=0;

	alGenBuffers(1, &buffer);
	alGenBuffers(1, &source);
	if (bitsPerSample == 8)
	{
		if (channels == 1)
		{
			format = AL_FORMAT_MONO8;
		}
		else
		{
			format = AL_FORMAT_STEREO8;
		}
	}
	else if (bitsPerSample == 16)
	{
		if (channels == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		else
		{
			format = AL_FORMAT_STEREO16;
		}
	}
	alBufferData(buffer, format, buf, dataSize, frequency);
	ALfloat SourcePos[] = { 0,0,0 };
	ALfloat SourceVel[] = { 0,1,0 };
	ALfloat ListenerPos[] = { 0,0,0 };
	ALfloat ListenerVel[] = { 0,-1,0 };
	ALfloat ListenerOri[] = { 0,0,-1.0f,0,1.0,0.0 };

	// Listener
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);

	//Source
	alSourcei(source, AL_BUFFER, buffer);
	alSourcef(source, AL_PITCH, 1.0f);
	alSourcef(source, AL_GAIN, 1.0f);
	alSourcefv(source, AL_POSITION, SourcePos);
	alSourcefv(source, AL_VELOCITY, SourceVel);
	alSourcei(source, AL_LOOPING, AL_FALSE);

	alSourcePlay(source);
	delete[] buf;
}

void Music::Play()
{
	alSourcePlay(source);
}
