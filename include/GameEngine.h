#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include "Sprite.h"

using namespace std;

class GameEngine {
    public:
      void add(Sprite* sprite);
      void remove(Sprite* sprite);
      void run();

    private:
    vector<Sprite*> sprites;
    vector<Sprite*> added, removed;

};

#endif