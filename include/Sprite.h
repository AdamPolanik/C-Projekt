#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_mixer.h>

using namespace std;

class Sprite
{
protected:
    Sprite(int x, int y, int w, int h, string imagePath);
    SDL_Rect rect;
    SDL_Point position;
    std::string type;

public:
    virtual ~Sprite();
    virtual void draw() const = 0;
    const SDL_Rect getRect() const { return rect; }
    virtual void tick() = 0;
    virtual void arrowLeft() {}
    virtual void arrowRight() {}
    virtual void spacebar() {}
    virtual void spacebarUp() {}
    virtual void isHit(Sprite* hitBy) {}
    virtual void remove() {}
    void updatePosition() {}
    SDL_Point getPosition() {return position;}
    virtual std::string getType() {return type;}
    virtual int getX() {return rect.x;}
    virtual int getY() {return rect.y;}
    virtual int getW() {return rect.w;}
    virtual int getH() {return rect.h;}
    virtual void shoot() {}
    virtual void playSound(string soundPath) {}
};

#endif