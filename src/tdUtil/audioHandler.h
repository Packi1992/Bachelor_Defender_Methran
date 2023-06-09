#pragma once


#ifndef SDL_BACHELORDEFENDER_MUSICHANDLER_H
#define SDL_BACHELORDEFENDER_MUSICHANDLER_H

#include "../global.h"
#include "../gamebase.h"

class AudioHandler {
public:
	void unInitAudioHandler();
	void load(musicType music);
	void pauseMusic();
	static AudioHandler *getHandler();
private:
	const char *getMusicPath(musicType music);
	static AudioHandler* audioHelper;
	Music *_musicmix = nullptr;
};

#endif //SDL_BACHELORDEFENDER_MUSICHANDLER_H