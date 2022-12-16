#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include "GameEngine.h"
#include "Sprite.h"
#include "System.h"
#include "Constants.h"
#include <algorithm>
#include <iostream>


using namespace std;

#define FPS 60

void GameEngine::add(Sprite* sprite) {
    added.push_back(sprite);
}

void GameEngine::remove(Sprite* sprite) {
    removed.push_back(sprite);
}

// void GameEngine::checkCollisions(Sprite* sprite1, Sprite* sprite2) { 
//     for (Sprite* s : sprites) {
//         if (Bullet* b = dynamic_cast<Bullet*> (s)) {
            
//             b->checkCollition(sprite2);
//         //}
//     }
// }

void GameEngine::checkCollision(string bulletType, string targetType, bool takesDamage) {
        for (Sprite* bullet : sprites) {
            if (bullet->getType() == bulletType) {
                Sprite* b = bullet;

                for (Sprite* target : sprites) {
                    if (target->getType() == targetType) {
                        if ( (b->getX() >= target->getX()) && (b->getX() < (target->getX() + target->getW())) && (b->getY() >= target->getY()) && (b->getY() < (target->getY() + target->getH())) ) {
                            if (takesDamage) {
                                target->isHit();
                                b->remove();
                            }
                            else {
                                b->remove();
                            }
                        }
                    }
                }
            }
        }
}

void GameEngine::run() {
    const int tickInterval = 1000 / FPS;
    Uint32 nextTick;
    int delay;

    // Här skapar vi bakgrunden
    SDL_Surface* backgroundSurface = IMG_Load( (constants::gResPath + "images/background.png").c_str() );
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(sys.renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    //här startas programmloopen
    bool play = true;
    while (play) {
        nextTick = SDL_GetTicks() + tickInterval;


        // Här kollar vi användarens input och utför funktionalitet baserat på detta
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
           
            switch (event.type) {
                case SDL_QUIT: { play = false; break; }

                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_RIGHT : { 
                            for (Sprite* sprite : sprites) {
                                sprite->arrowRight();
                            }
                            break;
                        }
                        case SDLK_LEFT : {
                             for (Sprite* sprite : sprites) {
                                sprite->arrowLeft();
                            }
                            break;
                        }

                        //lägg till så man kan åka och skjuta samtitigt
                        case SDLK_SPACE : {
                            break;
                        }
                        
                    }
                    break;
                }
                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_RIGHT : { 
                            break;
                        }
                        case SDLK_LEFT : {
                            break;
                        }
                        case SDLK_SPACE : {
                            for(Sprite* sprite : sprites) {
                                sprite->spacebar();
                                Mix_PlayChannel(2, sys.gunSound, 0);
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }

        for (Sprite* sprite : sprites) {
            sprite->tick();
        }

        checkCollision("bullet", "ghost", true);
        checkCollision("ghostBullet", "ship", true);
        checkCollision("ghostBullet", "shield", true);
        checkCollision("bullet", "shield", false);

        //Lägger till allt från bufferten till huvudVectorn och rensar bufferten
        for (Sprite* sprite : added) {
            sprites.push_back(sprite);
        }
        added.clear();

        for (Sprite* sprite : removed) {
            for (vector<Sprite*>::iterator i = sprites.begin(); i != sprites.end();) {
                if (*i == sprite) {
                    i = sprites.erase(i);
                }
                else {
                    i++;
                }
            }
        }
        removed.clear();

        // Här renderar vi allt på skärmen
        SDL_RenderClear(sys.renderer);
        SDL_RenderCopy(sys.renderer, backgroundTexture, NULL, NULL);

        for(Sprite* sprite : sprites) {
            sprite->draw();
        }

        SDL_RenderPresent(sys.renderer);

        //här väntar loopen tills delay är 0
        delay = nextTick - SDL_GetTicks();
        if (delay > 0) {
            SDL_Delay(delay);
        }
    }

}
