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

        void isHit() {
            game.remove(this);
        }

        SDL_Rect fetchArea() {
            return getRect();
        }

        int getX() {
            return rect.x;
        }

        std::string getType() { return type;}

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
    string type = "ghost";
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
            updatePosition();
        }
        void arrowLeft() {
        }
        void arrowRight() {
        }
        void updatePosition() {
            position.x = rect.x;
            position.y = rect.y;
        }
        SDL_Point getPosition() {
            return position;
        }

        std::string getType() { return type;}



    private:
        SDL_Texture* texture;
        int counter = 0;
        SDL_Point position;
        string type = "bullet";
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


