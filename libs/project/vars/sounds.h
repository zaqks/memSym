#include "SDL2/SDL_mixer.h"
#define soundsNum 4

char *soundsPaths[soundsNum] = {"assets/sounds/start1.wav", "assets/sounds/stop1.wav", "assets/sounds/start2.wav", "assets/sounds/stop2.wav"};
Mix_Chunk *sounds[soundsNum];

void initSounds()
{
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // open the device

    for (int i = 0; i < soundsNum; i++)
    {
        sounds[i] = Mix_LoadWAV(soundsPaths[i]);
    }
}

void playSound(int soundId, bool canPlay)
{
    if (canPlay)
    {
        Mix_PlayChannel(-1, sounds[soundId], 0);
        //Mix_PlayMusic(sounds[soundId], 0);
    }
}