#ifndef STATIONARY_OBJECT_H
#define STATIONARY_OBJECT_H

#include "Sprite.h"

class StationaryObject : public Sprite {
public:
    static StationaryObject* getInstance(int x, int y, int w, int h, string imagePath);
    void draw() const;
    void isHit();
    void tick();
    void changeImage(string imagePath);
    ~StationaryObject();
protected:
    StationaryObject(int x, int y, int w, int h, string imagePath);
private:
    SDL_Texture* texture;
    int counter = 0;
};





#endif