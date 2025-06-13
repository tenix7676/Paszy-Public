#include "AudioSystem.h"
#include <iostream>

SDL_AudioDeviceID AudioSystem::deviceID = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK;
std::unordered_map<MusicId, Mix_Music*>  AudioSystem::musicMap;
std::unordered_map<SoundId, Mix_Chunk*> AudioSystem::soundMap;

bool AudioSystem::init() {
	if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
		SDL_Log("AudioSystem: SDL_InitSubSystem error: %s.\n", SDL_GetError());
		return false;
	}
	if (!Mix_OpenAudio(deviceID, nullptr)) {
		SDL_Log("AudioSystem: Mix_OpenAudio error: %s.\n", SDL_GetError());
		return false;
	}

	return true;
}

bool AudioSystem::loadSong(MusicId id, const char* path) {
	Mix_Music* music = Mix_LoadMUS(path);
	if (music == nullptr) {
		SDL_Log("AudioSystem: loadSong error. Couldn't load \"%s\", SDL error: %s\n", path, SDL_GetError());
		return false;
	}
	musicMap[id] = music;

	return true;
}

bool AudioSystem::loadSound(SoundId id, const char* path) {
	Mix_Chunk* sound = Mix_LoadWAV(path);
	if (sound == nullptr) {
		SDL_Log("AudioSystem: loadSong error. Couldn't load \"%s\", SDL error: %s\n", path, SDL_GetError());
		return false;
	}
	soundMap[id] = sound;

	return true;
}

bool AudioSystem::loadAll() {
	return 
		loadSound(SoundId::GAMEOVER, "sounds/gameover.wav") and
		loadSound(SoundId::JUMP, "sounds/jump.wav") and
		loadSound(SoundId::KILL, "sounds/kill.wav") and
		loadSound(SoundId::LANDING, "sounds/landing.wav") and
		loadSound(SoundId::LEVEL_WIN, "sounds/level_win.wav");
	// ... <--------------
	// TUTAJ DODAJ MUZYKÊ I DWIÊKI 
}

void AudioSystem::setMusicVolume(int percent) {
	if (percent < 0) percent = 0;
	if (percent > 100) percent = 100;
	Mix_VolumeMusic(MIX_MAX_VOLUME * percent / 100);
}

void AudioSystem::setSoundVolume(int percent) {
	if (percent < 0) percent = 0;
	if (percent > 100) percent = 100;
	Mix_Volume(-1, MIX_MAX_VOLUME * percent / 100);
}

void AudioSystem::playBackgroundMusic(MusicId id) {
	if(!Mix_PlayMusic(musicMap[id], -1))
		std::cout << "AudioSystem: playBackgroundMusic error. " << SDL_GetError() << std::endl;
}

void AudioSystem::playSound(SoundId id) {
	if (Mix_PlayChannel(-1, soundMap[id], 0) == -1) {
		std::cout << "AudioSystem: playSound error. " << SDL_GetError() << std::endl;
	}
}

void AudioSystem::fadeOutMusic() {
	Mix_FadeOutMusic(3000);
}

void AudioSystem::haltMusic() {
	Mix_HaltMusic();
}