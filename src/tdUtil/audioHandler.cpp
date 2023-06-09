#include "audioHandler.h"

void AudioHandler::unInitAudioHandler() {
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}
}

void AudioHandler::playMusic(musicType music) {
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

void AudioHandler::playSound(soundType sound) {
	_soundmix = Mix_LoadWAV(getSoundPath(sound));
	if (!_soundmix) {
		cerr << "Mix_LoadWAV failed: " << Mix_GetError() << endl;
	}
	else {
		Mix_PlayChannelTimed(-1, _soundmix, 0, 1500);
	}
	return;
}

AudioHandler* AudioHandler::getHandler() {
	if (audioHelper == nullptr) {
		audioHelper = new AudioHandler();
	}
	return audioHelper;
}

void AudioHandler::loadMusic() {
	return;
}

void AudioHandler::loadSound() {
	return;
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

const char* AudioHandler::getSoundPath(soundType sound) {
	switch (sound) {
		case SoundTower:
			return BasePath "asset/sound/thriee.wav";
		case SoundProjectiles:
			return BasePath "asset/sound/pewf.wav";
		case SoundEnemy:
			return BasePath "asset/sound/ArrowHit.wav";
		case SoundArrow:
			return BasePath "asset/sound/ArrowHit.wav";
		default:
			cerr << "False Sound Type" << endl;
			return "asset/sound/thriee.wav";
	}
}

AudioHandler* AudioHandler::audioHelper = nullptr;
