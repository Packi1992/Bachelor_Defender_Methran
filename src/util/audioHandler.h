#pragma once


#ifndef SDL_BACHELORDEFENDER_MUSICHANDLER_H
#define SDL_BACHELORDEFENDER_MUSICHANDLER_H

#include "global.h"
#include "gamebase.h"

class AudioHandler {
public:
	void stopMusic();
	void playMusic(musicType music);
	void pauseMusic();
	void playSound(soundType sound, float x=0.5);
	static AudioHandler *getHandler();
private:
	AudioHandler();
	void loadMusic();
	void loadSound();
	const char *getMusicPath(musicType music);
	const char* getSoundPath(soundType sound);
	static AudioHandler* audioHelper;
	Music* _musicmixArray[MusicDisabled] = {};
	Chunk* _soundmixArray[SoundDisabled] = {};
	int channelnumber = 0;
};

#endif //SDL_BACHELORDEFENDER_MUSICHANDLER_H