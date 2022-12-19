#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include "Sprite.h"

class PlayableCharacter : public Sprite {
public:
    static PlayableCharacter* getInstance(int x, int y, int w, int h, string imagePath);
    void draw() const;
    void isHit();
    void spacebar();
    void tick();
    void arrowLeft();
    void arrowRight();
    ~PlayableCharacter();
    void playSound(string soundPath);
protected:
    PlayableCharacter(int x, int y, int w, int h, string imagePath);
private:
    SDL_Texture* texture;
    int remainingLives = 3;
    Mix_Chunk* sound;
};





#endif