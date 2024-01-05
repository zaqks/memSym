#define soundsNum 4

char *soundsPaths[soundsNum] = {"assets/sounds/start1.mp3", "assets/sounds/stop1.mp3", "assets/sounds/start2.mp3", "assets/sounds/stop2.mp3"};
Mix_Music *sounds[soundsNum];

void initSounds()
{
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640); // open the device
    
    for (int i = 0; i < soundsNum; i++)
    {
        sounds[i] = Mix_LoadMUS(soundsPaths[i]);
    }
}