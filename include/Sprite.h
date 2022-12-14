#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>

class Sprite
{
protected:
    Sprite(int x, int y, int width, int height) : rect{x, y, width, height} {}
    SDL_Rect rect;
    SDL_Rect hitArea;
    SDL_Point position;
    std::string type;


public:
    virtual void draw() const = 0;
    SDL_Rect getRect() const { return rect; }
    virtual void tick() = 0;
    virtual void arrowLeft() {}
    virtual void arrowRight() {}
    virtual void spacebar() {}
    virtual void spacebarUp() {}
    virtual void isHit() {}
    void updatePosition() {}
    SDL_Point getPosition() {return position;}
    SDL_Rect fetchArea() {return hitArea;}
    virtual std::string getType() {return type;}
    virtual int getX() {return rect.x;}
};

#endif