#pragma once
#include <al.h>
#include <alc.h>

//#include <AL\alut.h>
#include <iostream>
#include <string>
#include <map>
#include <Windows.h>
#include "GLM_Headers.h"
using namespace std;
using namespace glm;
class MusicLoader;
class MusicRepository;

class MusicLoader
{
private:
	MusicLoader() {
		this->AlBuffer = 0;
		this->AlSource = 0;
	}
	void ReadUntilDataKeyword(FILE*);
	void LoadWav(string Path);
public:
	ALuint AlSource;
	ALuint AlBuffer;
	static MusicLoader* Load(string Path) {
		MusicLoader* musicLoader = new MusicLoader();
		musicLoader->LoadWav(Path);
		return musicLoader;
	}
};

class MusicRepository
{
private:
	///<singleton>
	MusicRepository() {
		ALCdevice *device;
		ALCcontext *context;
		device = alcOpenDevice(NULL);

		context = alcCreateContext(device, NULL);
		alcMakeContextCurrent(context);
	}
	MusicRepository(MusicRepository&) = delete;
	static MusicRepository instance;

	/// <members>
	map<string, MusicLoader*> Repository;
	
	MusicLoader* GetSoundtrack(string Path)
	{
		if (Repository.find(Path) != Repository.end())
		{
			return Repository[Path];
		}
		else
		{
			Repository[Path] = MusicLoader::Load(Path);
			return Repository[Path];
		}
	}
public:
	~MusicRepository() {}
	MusicLoader* operator[] (string rhs) {
		return GetSoundtrack(rhs);
	}
	static MusicRepository& Instance()
	{
		static MusicRepository instance;
		return instance;
	}
	void Unload(string Path)
	{

	}
	
};

class Music
{
public:
	Music(string Path);
	~Music();
	void Play();
	void PlayLoop();
	void Restart();
	void Stop();
	void SetPositions( vec3 SourcePos, vec3 SourceVel);
	static void SetListener(vec3 ListenerPos, vec3 ListenerVel, vec3 ListenerOri);
	/*range of 0.0f - 1.0f*/
	void AddVolume(float value);
private:
	MusicLoader* musicObject;
	float currentVolume;
	bool isPlaying;
};
