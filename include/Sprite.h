#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

class Sprite
{
protected:
    Sprite(int x, int y, int width, int height) : rect{x, y, width, height} {}
    SDL_Rect rect;

public:
    virtual void draw() const = 0;
    SDL_Rect getRect() const { return rect; }
    virtual void tick() = 0;
    virtual void arrowLeft() {}
    virtual void arrowRight() {}
    virtual void spacebar() {}
    virtual void spacebarUp() {}


};

#endif