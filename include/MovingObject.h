#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include "Sprite.h"

class MovingObject : public Sprite {
public:
    static MovingObject* getInstance(int x, int y, int w, int h, string imagePath, string type);
    void draw() const;
    void isHit();
    void tick();
    void updatePosition();
    void remove();
    std::string getType() {return type;}
    SDL_Point getPosition();
    bool checkCollision(Sprite* target);
    ~MovingObject();
protected:
    MovingObject(int x, int y, int w, int h, string imagePath, string type);
private:
    SDL_Texture* texture;
    int counter = 0;
    SDL_Point position;
    std::string type;
};





#endif