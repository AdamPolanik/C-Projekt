#include "PlayableCharacter.h"
#include <SDL2/SDL.h>
#include "Constants.h"
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_mixer.h>
#include "System.h"

using namespace std;

PlayableCharacter::PlayableCharacter(int x, int y, int w, int h, string imagePath):Sprite(x, y, w, h, imagePath) {
    texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + imagePath).c_str() );
}

PlayableCharacter::~PlayableCharacter() {
    SDL_DestroyTexture(texture);
    Mix_FreeChunk(sound);
}

PlayableCharacter* PlayableCharacter::getInstance(int x, int y, int w, int h, string imagePath) { 
    return new PlayableCharacter(x, y, w, h, imagePath);
}

void PlayableCharacter::draw() const {
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.renderer, texture, NULL, &rect);
}

void PlayableCharacter::tick() {

}

void PlayableCharacter::isHit() {

}

void PlayableCharacter::spacebar() {
    
}

void PlayableCharacter::arrowLeft() {
    rect.x = rect.x - 10;
}

void PlayableCharacter::arrowRight() {
    rect.x = rect.x + 10;
}

void PlayableCharacter::playSound(string soundPath) {
sound = Mix_LoadWAV( (constants::gResPath + soundPath).c_str() );
Mix_Volume(3, 30);
Mix_PlayChannel(3, sound, 0);
}

