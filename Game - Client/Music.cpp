 #include "Music.h"



Music::Music(string Path)
{
	this->musicObject = MusicRepository::Instance()[Path];
	currentVolume = 5.0f;
	isPlaying = false;
}


Music::~Music()
{
}
void Music::Play()
{
	if (isPlaying == false)
	{
		isPlaying = true;
		alSourcePlay(this->musicObject->AlSource);
	}
}

void Music::PlayLoop()
{
	alSourcei(this->musicObject->AlSource, AL_LOOPING, AL_TRUE);
	this->Play();
}

void Music::Restart()
{
	alSourcePlay(this->musicObject->AlSource);
}

void Music::Stop()
{
	if (isPlaying == true)
	{
		isPlaying = false;
		alSourceStop(this->musicObject->AlSource);
	}
}

void Music::SetListener(vec3 ListenerPos, vec3 ListenerVel, vec3 ListenerOri)
{
	// Listener
	alListenerfv(AL_POSITION, glm::value_ptr(ListenerPos));
	alListenerfv(AL_VELOCITY, glm::value_ptr(ListenerVel));
	alListenerfv(AL_ORIENTATION, glm::value_ptr(ListenerOri));
}

void Music::SetPositions(vec3 SourcePos, vec3 SourceVel)
{
	//Source
	alSourcefv(this->musicObject->AlSource, AL_POSITION, glm::value_ptr(SourcePos));
	alSourcefv(this->musicObject->AlSource, AL_VELOCITY, glm::value_ptr(SourceVel));

}

void Music::AddVolume(float value)
{
	currentVolume += value;
	//if (value > 1.0f) exit(0);
	//if (value < 0.0f) exit(0);
	//alListenerfAL_GAIN, currentVolume);
	alSourcef(this->musicObject->AlSource, AL_GAIN, currentVolume);
	/*if (currentVolume < 0)
	{
		Stop();
	}
	if (currentVolume > 0)
	{
		Play();
	}*/

}


void MusicLoader::LoadWav(string Path)
{
	// READ FILE
	//alutInit(0, NULL);

	FILE * file;
	int CurrentBit = 0;
	//fopen_s(&file, R"(D:\Users\stasw\Documents\virheimur\Game - Client\Soundtracks\Perion.wav)", "rb");
	fopen_s(&file, Path.c_str(), "rb");
	//fopen_s(&file, R"(D:\Users\stasw\Documents\virheimur\Game - Client\Soundtracks\Violin.wav)", "rb");
	char type[5] = {};
	DWORD size = 0, chunkSize = 0;
	short formatType = 0, channels = 0;
	DWORD sampleRate = 0, avgBytesPerSec = 0;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;
	fread(type, sizeof(char), 4, file);
	fread(&size, sizeof(DWORD), 1, file);
	fread(type, sizeof(char), 4, file);
	fread(type, sizeof(char), 4, file);

	fread(&chunkSize, sizeof(DWORD), 1, file);
	fread(&formatType, sizeof(short), 1, file);
	fread(&channels, sizeof(short), 1, file);
	fread(&sampleRate, sizeof(DWORD), 1, file);
	fread(&avgBytesPerSec, sizeof(DWORD), 1, file);
	fread(&bytesPerSample, sizeof(short), 1, file);
	fread(&bitsPerSample, sizeof(short), 1, file);

	ReadUntilDataKeyword(file);
	CurrentBit = ftell(file);

	fread(&dataSize, sizeof(DWORD), 1, file);

	unsigned char* buf = new unsigned char[dataSize];
	fread(buf, sizeof(BYTE), dataSize, file);

	// INITIALIZE AL
	

	ALuint frequency = sampleRate;
	ALuint format = 0;

	alGenBuffers(1, &AlBuffer);
	alGenSources(1, &AlSource);

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

	alBufferData(AlBuffer, format, buf, dataSize, frequency);
	
	ALfloat SourcePos[] = { 0,0,0 };
	ALfloat SourceVel[] = { 0,1,0 };
	ALfloat ListenerPos[] = { 0,0,0 };
	ALfloat ListenerVel[] = { 0,-1,0 };
	ALfloat ListenerOri[] = { 0,0,-1.0f,0,1.0,0.0 };

	// Initialize Source
	int err;
	if ((err = alGetError()) != AL_NO_ERROR)
	{
		err = 0;
	}
	// Listener
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);

	//Source
	alSourcei(AlSource, AL_BUFFER, AlBuffer);
	alSourcef(AlSource, AL_PITCH, 1.0f);
	alSourcef(AlSource, AL_GAIN, 1.0f);
	alSourcefv(AlSource, AL_POSITION, SourcePos);
	alSourcefv(AlSource, AL_VELOCITY, SourceVel);
	alSourcei(AlSource, AL_LOOPING, AL_FALSE);
	delete[] buf;
}
void MusicLoader::ReadUntilDataKeyword(FILE * file)
{
	char data = 0;
	while (true)
	{
		fread(&data, sizeof(char), 1, file);
		if (data == 'd')
		{
			fread(&data, sizeof(char), 1, file);
			if (data == 'a')
			{
				fread(&data, sizeof(char), 1, file);
				if (data == 't')
				{
					fread(&data, sizeof(char), 1, file);
					if (data == 'a')
					{
						return;
					}
				}
			}
		}

	}
}
