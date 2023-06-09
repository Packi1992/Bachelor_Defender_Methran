#pragma once


#ifndef SDL_BACHELORDEFENDER_MUSICHANDLER_H
#define SDL_BACHELORDEFENDER_MUSICHANDLER_H

#include "../global.h"
#include "../gamebase.h"

class AudioHandler {
public:
	void unInitAudioHandler();
	void playMusic(musicType music);
	void pauseMusic();
	void playSound(soundType sound);
	static AudioHandler *getHandler();
private:
	void loadMusic();
	void loadSound();
	const char *getMusicPath(musicType music);
	const char* getSoundPath(soundType sound);
	static AudioHandler* audioHelper;

	Music* _musicmix = nullptr;
	Chunk* _soundmix = nullptr;
};

#endif //SDL_BACHELORDEFENDER_MUSICHANDLER_H