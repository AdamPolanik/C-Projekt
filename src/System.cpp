#include "System.h"
#include "Constants.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

System::System() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		cout << "Error SDL2 Initialization : " << SDL_GetError();
		EXIT_FAILURE;
	}

    window = SDL_CreateWindow("Game", 100, 100, 1280, 720, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);

    music = Mix_LoadWAV( (constants::gResPath + "sounds/backgroundMusic.mp3").c_str() );
    Mix_Volume(1, 10);
    Mix_PlayChannel(1, music, -1);

    gunSound = Mix_LoadWAV( (constants::gResPath + "sounds/bulletSoundShit.mp3").c_str() );
    Mix_Volume(2, 25);

    damageSound = Mix_LoadWAV( (constants::gResPath + "sounds/damageSound.mp3").c_str() );
    Mix_Volume(3, 30);
}

System::~System() {
    Mix_FreeChunk(music);
    Mix_FreeChunk(gunSound);
    Mix_FreeChunk(damageSound);
    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

System sys;