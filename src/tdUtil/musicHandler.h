#pragma once


#ifndef SDL_BACHELORDEFENDER_MUSICHANDLER_H
#define SDL_BACHELORDEFENDER_MUSICHANDLER_H

#include "../global.h"
#include "../gamebase.h"

class musicHandler {
public:
	void load();
	void uninitMusic();
	void pauseMusic();
	//load/init
	//uninit
	//pausemusic
	//continuemusic eventuel pause und continue zusammenfassen
};

#endif //SDL_BACHELORDEFENDER_MUSICHANDLER_H