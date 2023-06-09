#include "audioHandler.h"

void AudioHandler::unInitAudioHandler() {
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}
}

void AudioHandler::load(musicType music) {
	_musicmix = Mix_LoadMUS(getMusicPath(music));
	if (!_musicmix) {
		cerr << "Mix_LoadMUS failed: " << Mix_GetError() << endl;
	}
	else {
		Mix_PlayMusic(_musicmix, -1);
	}
	return;
}

void AudioHandler::pauseMusic() {
	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
	else {
		Mix_PauseMusic();
	}
	return;
}

AudioHandler* AudioHandler::getHandler() {
	if (audioHelper == nullptr) {
		audioHelper = new AudioHandler();
	}
	return audioHelper;
}

const char* AudioHandler::getMusicPath(musicType music) {
	switch (music) {
		case Music1:
			return BasePath "asset/music/severance.ogg";
		case Music2:
			return BasePath "asset/music/severance.ogg";
		case Music3:
			return BasePath "asset/music/severance.ogg";
	}
	cerr << "False Music Type" << endl;
	return "ERROR";
}

AudioHandler* AudioHandler::audioHelper = nullptr;
