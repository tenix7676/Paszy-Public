#pragma once
#include "SDL_mixer.h"
#include <unordered_map>

enum class MusicId {
	COUNT
};

enum class SoundId {
	LEVEL_WIN,
	JUMP,
	LANDING,
	KILL,
	GAMEOVER,
	COUNT
};

class AudioSystem
{
	static std::unordered_map<MusicId, Mix_Music*> musicMap;
	static std::unordered_map<SoundId, Mix_Chunk*> soundMap;
	static SDL_AudioDeviceID deviceID;
public:
	static bool init();
	static bool loadSong(MusicId id, const char* path);
	static bool loadSound(SoundId id, const char* path);
	static bool loadAll();
	static void playBackgroundMusic(MusicId id);
	static void playSound(SoundId id);
	static void fadeOutMusic();
	static void haltMusic();
	static void setMusicVolume(int percent);
	static void setSoundVolume(int percent);
};
