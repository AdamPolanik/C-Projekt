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
        Shield(int x) : Sprite(x, 480, 150, 75) {
            texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldDefault.png").c_str() );
        }
        ~Shield() {
            SDL_DestroyTexture(texture);
        }
        void draw() const {
            const SDL_Rect &rect = getRect();
            SDL_RenderCopy(sys.renderer, texture, NULL, &rect);
        }
        string getType() {
            return type;
        }
        int getX() {
            return rect.x - 10;
        }
        void isHit() {
            health--;

            if (health == 10) {
                texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldStage1.png").c_str() );
            }
            else if (health == 8) {
                texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldStage2.png").c_str() );
            }
            else if (health == 6) {
                texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldStage3.png").c_str() );
            }
            else if (health == 4) {
                texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldStage4.png").c_str() );
            }
            else if (health == 2) {
                texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/shieldStageFinal.png").c_str() );
            }
            else if (health == 0) {
                game.remove(this);
            }
        }
        void tick() {

        }

    private:
    SDL_Texture* texture;
    int health = 12;
    string type = "shield";
};

class GhostBullet : public Sprite {
    public:

        static GhostBullet* getInstance(int x, int y) {
            return new GhostBullet(x, y);
        }
        GhostBullet(int x, int y) : Sprite(x, y, 20, 20) {
            texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + "images/ghostBullet.png").c_str() );
        }
        ~GhostBullet() {
            SDL_DestroyTexture(texture);
        }
        void remove() {
            game.remove(this);
        }
        void draw() const {
            const SDL_Rect &rect = getRect();
            SDL_RenderCopy(sys.renderer, texture, NULL, &rect);
        }
        void tick() {
            counter++;
            if (rect.y >= 630) {
                game.remove(this);
            }
            else if (counter % 1 == 0) {
                rect.y += 5;
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
        string type = "ghostBullet";
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
        void shoot() {
            GhostBullet* ghostBullet = GhostBullet::getInstance((rect.x + rect.w / 2) - 10, rect.y);
            game.add(ghostBullet);
        }

        int getX() {
            return rect.x - 10;
        }

        std::string getType() { return type;}

        void tick() {
            counter++;
            shootCounter++;
            if (rect.y <= 0) {
                game.remove(this);
            }
            else if (counter % 5 == 0) {
                
                if (!resetting && resetCounter != 230) {
                    rect.x++;
                    resetCounter++;
                }
                else if (!resetting && resetCounter == 230) {
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

            if (shootCounter == 1200) {
                shootCounter = 0;
            }

            if (whenToShoot == 0) {
                whenToShoot = rand() % 1200 + 1;
            }

            if (shootCounter == whenToShoot) {
                shoot();
                whenToShoot = 0;
            }
        }

    private:
    SDL_Texture* texture;
    int counter = 0;
    int resetCounter = 0;
    bool resetting;
    string type = "ghost";
    int shootCounter = 0;
    int whenToShoot = 0;
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
        void remove() {
            game.remove(this);
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
        void isHit() {
            if (remainingLives > 0) {
                remainingLives--;
                Mix_PlayChannel(3, sys.damageSound, 0);
            }
            else {
                game.remove(this);
            }

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
        std::string getType() { return type;}

    private:
        SDL_Texture* texture;
        string type = "ship";
        int remainingLives = 3;

};


int main(int argc, char** argv) {

    int x = 100;
    int y = -20;

    for (int i = 0; i < 55; i++) {
        
        if (i % 11 == 0) {
            x = 100;
            y += 65;
        }
        else {
            x += 80;
        }

        game.add(new Ghost(x, y));

    }

    Ship* ship = new Ship();
    game.add(new Shield(100));
    game.add(new Shield(400));
    game.add(new Shield(700));
    game.add(new Shield(1000));
    game.add(ship);
    game.run();
    
    return 0;
}


