#pragma once


#ifndef SDL_BACHELORDEFENDER_MUSICHANDLER_H
#define SDL_BACHELORDEFENDER_MUSICHANDLER_H

#include "../global.h"
#include "../gamebase.h"

class AudioHandler {
public:
	~AudioHandler();
	void load(musicType music);
	void pauseMusic();
	static AudioHandler *getHandler();
private:
	static AudioHandler* audioHelper;
	const char *getMusicPath(musicType music);
	Music *_musicmix = nullptr;
};

#endif //SDL_BACHELORDEFENDER_MUSICHANDLER_H