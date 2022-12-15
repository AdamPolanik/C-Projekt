#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include "Sprite.h"
#include <array>

using namespace std;

class GameEngine {
    public:
      void add(Sprite* sprite);
      void remove(Sprite* sprite);
      void checkCollision(string bulletType, string targetType, bool takesDamage);
      void run();

    private:
    vector<Sprite*> sprites;
    vector<Sprite*> added, removed;
    vector<vector<Sprite*>> ghosts;

};

#endif