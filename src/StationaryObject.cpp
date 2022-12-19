#include "StationaryObject.h"
#include <SDL2/SDL.h>
#include "Constants.h"
#include <SDL2/SDL_image.h> 
#include "System.h"

using namespace std;

StationaryObject::StationaryObject(int x, int y, int w, int h, string imagePath):Sprite(x, y, w, h, imagePath) {
    texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + imagePath).c_str() );
}

StationaryObject::~StationaryObject() {
    SDL_DestroyTexture(texture);
}

StationaryObject* StationaryObject::getInstance(int x, int y, int w, int h, string imagePath) { 
    return new StationaryObject(x, y, w, h, imagePath);
}

void StationaryObject::draw() const {
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.renderer, texture, NULL, &rect);
}

void StationaryObject::tick() {

}

void StationaryObject::isHit() {

}

void StationaryObject::changeImage(string imagePath) {
    texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + imagePath).c_str() );
}