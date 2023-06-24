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

// playStereoSound using Mix_SetPanning, MixVolume, ChunkVolume 

void AudioHandler::playSound(soundType sound, float x) {
	int left = 255;
	int right = 255;
	if (x > 1) {
		x = 1;
	}
	else if (x < 0) {
		x = 0;
	}
	if (x > 0.5) {
		left = 510 * (1-x);
	}
	else if (x < 0.5) {
		right = 510 * x;
	}
	if (_soundmixArray[sound]) {
		int channel = Mix_PlayChannelTimed(-1, _soundmixArray[sound],0, 1500);
		Mix_SetPanning(channel, left, right);
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
		case SoundPointerTower:
			return BasePath "asset/sound/thriee.wav";
		case SoundHashCanon:
			return BasePath "asset/sound/thriee.wav";
		case SoundLinkedListTower:
			return BasePath "asset/sound/thriee.wav";
		case SoundRecursivTower:
			return BasePath "asset/sound/thriee.wav";
		case SoundStringTower:
			return BasePath "asset/sound/thriee.wav";
		case SoundEnemyOrdinary:
			return BasePath "asset/sound/ArrowHit.wav";
		case SoundFrolePöhlich:
			return BasePath "asset/sound/thriee.wav";
		case SoundDrüberbolz:
			return BasePath "asset/sound/thriee.wav";
		case SoundArrowFire:
			return BasePath "asset/sound/pewf.wav";
		case SoundArrowHit:
			return BasePath "asset/sound/ArrowHit.wav";
        case SoundBoomerangFire:
            return BasePath "asset/sound/thriee.wav";
		case SoundBoomerangHit:
			return BasePath "asset/sound/Darth_Vader_NO.mp3";
		case SoundHashbombFire:
			return BasePath "asset/sound/thriee.wav";
		case SoundHashbombHit:
			return BasePath "asset/sound/thriee.wav";
		case SoundLinkFire:
			return BasePath "asset/sound/thriee.wav";
		case SoundLinkHit:
			return BasePath "asset/sound/thriee.wav";
		case SoundStringProjectileFire:
			return BasePath "asset/sound/thriee.wav";
		case SoundStringProjectileHit:
			return BasePath "asset/sound/thriee.wav";
		case SoundFire:
			return BasePath "asset/sound/thriee.wav";
		case SoundBaseExplosion:
			return BasePath "asset/sound/thriee.wav";
		case SoundError:
			cerr << "False Sound Type" << endl;
			return "asset/sound/thriee.wav";
	}
}

AudioHandler* AudioHandler::audioHelper = nullptr;
