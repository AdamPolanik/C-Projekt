#include "GameEngine.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Constants.h"
#include <SDL2/SDL_image.h> 
#include "System.h"
#include "Sprite.h"
//#define FPS 60

using namespace std;

GameEngine game;

class Shield : public Sprite {
    public:
        static Shield* getInstance(int x) { 
            return new Shield(x);
        }
        Shield(int x) : Sprite(x, 400, 300, 250) {
            texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldDefault.png").c_str() );
        }
        ~Shield() {
            SDL_DestroyTexture(texture);
        }
        void draw() const {
            const SDL_Rect &rect = getRect();
            SDL_RenderCopy(sys.renderer, texture, NULL, &rect);
        }
        void tick() {
            counter++;

            if (counter == 500) {
                texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldStage1.png").c_str() );
            }
            else if (counter == 1000) {
                texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldStage2.png").c_str() );
            }
            else if (counter == 1500) {
                texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldStage3.png").c_str() );
            }
            else if (counter == 2000) {
                texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldStage4.png").c_str() );
            }
            else if (counter == 2500) {
                texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldStageFinal.png").c_str() );
            }
            else if (counter == 3000) {
                game.remove(this);
            }

        }

    private:
    SDL_Texture* texture;
    int counter = 0;
    int damageCounter = 0;
};

class Ghost : public Sprite {
    public:
        static Ghost* getInstance(int x, int y) { 
            return new Ghost(x, y);
        }
        Ghost(int x, int y) : Sprite(x, y, 55, 35) {
            texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/Ghost.png").c_str() );
        }
        ~Ghost() {
            SDL_DestroyTexture(texture);
        }
        void draw() const {
            const SDL_Rect &rect = getRect();
            SDL_RenderCopy(sys.renderer, texture, NULL, &rect);
        }
        void tick() {
            counter++;
            if (rect.y <= 0) {
                game.remove(this);
            }
            else if (counter % 50 == 0) {
                
                if (!resetting && resetCounter != 30) {
                    rect.x++;
                    resetCounter++;
                }
                else if (!resetting && resetCounter == 30) {
                    rect.y += 10;
                    resetting = true;
                }
                else if (resetting && resetCounter != 0) {
                    rect.x--;
                    resetCounter--;
                }
                else if (resetting && resetCounter == 0) {
                    rect.y += 10;
                    resetting = false;
                }
            }
            
        }

    private:
    SDL_Texture* texture;
    int counter = 0;
    int resetCounter = 0;
    bool resetting;
};

class Bullet : public Sprite {
    public:
        static Bullet* getInstance(int x) {
            return new Bullet(x);
        }
        Bullet(int x) : Sprite(x, 600, 20, 20) {
            texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/bullet.png").c_str() );
        }
        ~Bullet() {
            SDL_DestroyTexture(texture);
        }
        void draw() const {
            const SDL_Rect &rect = getRect();
            SDL_RenderCopy(sys.renderer, texture, NULL, &rect);
        }
        void tick() {
            counter++;
            if (rect.y <= 0) {
                game.remove(this);
            }
            else if (counter % 1 == 0) {
                rect.y -= 5;
            }
        }
        void arrowLeft() {
        }
         void arrowRight() {
        }
    
    private:
        SDL_Texture* texture;
        int counter = 0;

};

class Ship : public Sprite {
    public:
        static Ship* getInstance() {
            return new Ship();
        }
        Ship() : Sprite(640, 600, 55, 35) {
            texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/ship.png").c_str() );
        }
        ~Ship() {
            SDL_DestroyTexture(texture);
        }
        void draw() const {
            const SDL_Rect &rect = getRect();
            SDL_RenderCopy(sys.renderer, texture, NULL, &rect);
        }
        void tick() {

        }
        void arrowLeft() {
            rect.x = rect.x - 10;
        }
         void arrowRight() {
            rect.x = rect.x + 10;
        }
        void spacebar() {
            Bullet* bullet = Bullet::getInstance((rect.x + rect.w / 2) - 10);
            game.add(bullet);
        }

    private:
        SDL_Texture* texture;

};


int main(int argc, char** argv) {
    //const int tickInterval = 1000 / FPS;
    //Uint32 nextTick;
    //int delay;

// if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
// 	{
// 		cout << "Error SDL2 Initialization : " << SDL_GetError();
// 		return EXIT_FAILURE;
// 	}

//     SDL_Window* window = SDL_CreateWindow("Game", 100, 100, 1280, 720, 0);

//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Här skapar vi bakgrunden
    // SDL_Surface* backgroundSurface = IMG_Load( (constants::gResPath + "images/background.png").c_str() );
    // SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    // SDL_FreeSurface(backgroundSurface);

    // Här skapar vi rymdskeppet
    // SDL_Surface* shipSurface = IMG_Load( (constants::gResPath + "images/ship.png").c_str() );
    // SDL_Texture* shipTexture = SDL_CreateTextureFromSurface(renderer, shipSurface);
    // SDL_Rect shipRectangle = {640, 600, 55, 35};
    // SDL_FreeSurface(shipSurface);

    //här startas programmloopen
    // bool play = true;
    // while (play) {
    //     nextTick = SDL_GetTicks() + tickInterval;


    //     // Här kollar vi användarens input och utför funktionalitet baserat på detta
    //     SDL_Event event;
    //     while (SDL_PollEvent(&event)) {
    //         switch (event.type) {
    //             case SDL_QUIT: { play = false; break; }

    //             case SDL_KEYDOWN: {
    //                 switch (event.key.keysym.sym) {
    //                     case SDLK_RIGHT : {shipRectangle.x = shipRectangle.x + 10; break;}
    //                     case SDLK_LEFT : {shipRectangle.x = shipRectangle.x - 10; break;}
    //                 }
    //                 break;
    //             }

    //         }
    //     }


        // Här renderar vi allt på skärmen
        // SDL_RenderClear(renderer);
        // SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        // SDL_RenderCopy(renderer, shipTexture, NULL, &shipRectangle);
        // SDL_RenderPresent(renderer);

        //här väntar loopen tills delay är 0
    //     delay = nextTick - SDL_GetTicks();
    //     if (delay > 0) {
    //         SDL_Delay(delay);
    //     }
    // }

    
    // SDL_DestroyTexture(backgroundTexture);
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // SDL_Quit();
    int x = 300;
    int y = -20;

    for (int i = 0; i < 55; i++) {
        
        if (i % 11 == 0) {
            x = 300;
            y += 65;
        }
        else {
            x += 80;
        }

        game.add(new Ghost(x, y));
    }

   
    Ship* ship = new Ship();
    game.add(new Shield(50));
    game.add(new Shield(350));
    game.add(new Shield(650));
    game.add(new Shield(950));
    game.add(ship);
    game.run();
    
    return 0;
}


