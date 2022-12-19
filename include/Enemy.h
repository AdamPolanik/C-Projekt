#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"

class Enemy : public Sprite {
public:
    static Enemy* getInstance(int x, int y, int w, int h, string imagePath);
    void draw() const;
    void isHit();
    void shoot();
    void tick();
    ~Enemy();
protected:
    Enemy(int x, int y, int w, int h, string imagePath);
private:
    SDL_Texture* texture;
    int counter = 0;
    int resetCounter = 0;
    bool resetting;
    //string type = "ghost";
    int shootCounter = 0;
    int whenToShoot = 0;
};





#endif