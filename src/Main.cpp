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



class Bullet : public Sprite {
    public:
        static Bullet* getInstance(int x) {
            return new Bullet(x);
        }
        Bullet(int x) : Sprite(x, 600, 10, 5) {
            texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/ship.png").c_str() );
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
            else if (counter % 10 == 0) {
                rect.y--;
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
            Bullet* bullet = Bullet::getInstance(rect.x);
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

    Ship* ship = new Ship();
    game.add(ship);
    game.run();
    
    return 0;
}


