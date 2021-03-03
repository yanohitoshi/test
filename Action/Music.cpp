#include "Music.h"
Music::Music()
	:mMusic(nullptr)
{
}

Music::~Music()
{
	Mix_FreeMusic(mMusic);
}

void Music::Play()
{
	Mix_PlayMusic(mMusic, -1);
}

void Music::FadeInMusic(int fadeInTime)
{
	Mix_FadeInMusic(mMusic, -1, fadeInTime);
}

bool Music::LoadMusic(const std::string& fileName)
{
	mMusic = Mix_LoadMUS(fileName.c_str());
	return mMusic != nullptr;
}

void Music::Stop()
{
	Mix_HaltMusic();
}

void Music::FadeOutMusic(int fadeOutTime)
{
	Mix_FadeOutMusic(fadeOutTime);
}

bool Music::IsPlaying()
{
	return Mix_PlayingMusic();
}
