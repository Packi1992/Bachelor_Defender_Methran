#include "audioHandler.h"

AudioHandler::AudioHandler() {
	loadMusic();
	loadSound();
}

void AudioHandler::stopMusic() {
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}
}

void AudioHandler::playMusic(musicType music) {
	if (_musicmixArray[music]) {
		Mix_PlayMusic(_musicmixArray[music], -1);
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
	if (_soundmixArray[sound]) {
		Mix_PlayChannelTimed(-1, _soundmixArray[sound],0, 1500);
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
	for (int i = 0; i < MusicDisabled; i++) {
		_musicmixArray[i] = Mix_LoadMUS(getMusicPath(static_cast <musicType>(i)));
		if (!_musicmixArray[i]) {
			cerr << "Mix_LoadMUS failed at " << static_cast <musicType>(i) << " : " << Mix_GetError() << endl;
		}
	}
	return;
}

void AudioHandler::loadSound() {
	for (int i = 0; i < SoundDisabled; i++) {
		_soundmixArray[i] = Mix_LoadWAV(getSoundPath(static_cast <soundType>(i)));
		if (!_soundmixArray[i]) {
			cerr << "Mix_LoadWAV failed at " << static_cast <soundType>(i) << " : " << Mix_GetError() << endl;
		}
	}
	return;
}

const char* AudioHandler::getMusicPath(musicType music) {
	switch (music) {
		case MusicMainMenu:
			return BasePath "asset/music/severance.ogg";
		case MusicEditor:
			return BasePath "asset/music/testsound.wav";
		case MusicGame:
			return BasePath "asset/music/severance.ogg";
		case MusicError:
			return BasePath "asset/music/severance.ogg";
		default:
			cerr << "False Sound Type" << endl;
			return "asset/sound/thriee.wav";
	}
}

// Eventually split Projectile Sound in Fire and Hit mabey dont I dont know
const char* AudioHandler::getSoundPath(soundType sound) {
	switch (sound) {
		case SoundTowerPointer:
			return BasePath "asset/sound/thriee.wav";
		case SoundEnemyOrdinary:
			return BasePath "asset/sound/ArrowHit.wav";
		case SoundArrowFire:
			return BasePath "asset/sound/pewf.wav";
		case SoundArrowHit:
			return BasePath "asset/sound/ArrowHit.wav";
		case SoundBullet:
		case SoundFFire:
		case SoundBaseExplosion:
		case SoundError:
		default:
			cerr << "False Sound Type" << endl;
			return "asset/sound/thriee.wav";
	}
}

AudioHandler* AudioHandler::audioHelper = nullptr;