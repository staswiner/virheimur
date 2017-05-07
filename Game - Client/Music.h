#pragma once
#include <al.h>
#include <alc.h>
#include <AL\alut.h>
#include <iostream>
#include <Windows.h>
class Music
{
public:
	Music();
	~Music();
	void Initialize();
	void Play();
private:
	ALuint source;
	ALuint buffer;
};

