#include "MovingObject.h"
#include <SDL2/SDL.h>
#include "Constants.h"
#include <SDL2/SDL_image.h> 
#include "System.h"
#include "GameEngine.h"
#include <iostream>

using namespace std;

MovingObject::MovingObject(int x, int y, int w, int h, string imagePath, string typeName):Sprite(x, y, w, h, imagePath) {
    texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + imagePath).c_str() );
}

MovingObject::~MovingObject() {
    SDL_DestroyTexture(texture);
}

MovingObject* MovingObject::getInstance(int x, int y, int w, int h, string imagePath, string typeName) { 
    return new MovingObject(x, y, w, h, imagePath, typeName);
}

void MovingObject::draw() const {
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.renderer, texture, NULL, &rect);
}

void MovingObject::tick() {

}

void MovingObject::isHit() {

}

void MovingObject::remove() {

}

 void MovingObject::updatePosition() {
    position.x = rect.x;
    position.y = rect.y;
}

SDL_Point MovingObject::getPosition() {
    return position;
}

bool MovingObject::checkCollision(Sprite* target) {
    if ( (this->getX() >= target->getX()) && (this->getX() < (target->getX() + target->getW())) && (this->getY() >= target->getY()) && (this->getY() < (target->getY() + target->getH())) ) {
        return true;
    }
    else {
        return false;
    }
}