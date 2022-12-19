#include "GameEngine.h"
#include <iostream>
#include "Constants.h"
#include "System.h"
#include "Sprite.h"
#include "Enemy.h"
#include "PlayableCharacter.h"
#include "StationaryObject.h"
#include "MovingObject.h"
//#define FPS 60

using namespace std;

GameEngine game;

class Shield : public StationaryObject {
    public:
       
        Shield(int x, string imagePath) : StationaryObject(x, 480, 150, 75, imagePath) {}

        int getX() {
            return rect.x - 10;
        }
        void isHit(Sprite* hitBy) {

            if (hitBy->getType() == "ghostBullet") {
                health--;
                hitBy->remove();
            }

            if (hitBy->getType() == "bullet") {
                hitBy->remove();
            }

            if (health == 10) {
                changeImage("images/shieldStage1.png");
            }
            else if (health == 8) {
                changeImage("images/shieldStage2.png");
            }
            else if (health == 6) {
                changeImage("images/shieldStage3.png");
            }
            else if (health == 4) {
                changeImage("images/shieldStage4.png");
            }
            else if (health == 2) {
                changeImage("images/shieldStageFinal.png");
            }
            else if (health == 0) {
                game.remove(this);
            }
        }
        void tick() {

        }

    private:
    int health = 12;
};

class GhostBullet : public MovingObject {
    public:

        static GhostBullet* getInstance(int x, int y, int w, int h, string imagePath, string typeName) {
            return new GhostBullet(x, y, w, h, imagePath, typeName);
        }

        GhostBullet(int x, int y, int w, int h, string imagePath, string typeName) : MovingObject(x, y, w, h, imagePath, typeName) {
            type = typeName;
        }

        void remove() {
            game.remove(this);
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

        std::string getType() { return type;}

    private:
        int counter = 0;
        string type;
};

class Ghost : public Enemy {
    public:
        Ghost(int x, int y, int w, int h, string imagePath) : Enemy(x, y, 55, 35, "images/Ghost.png") {}
     
        void isHit(Sprite* hitBy) {
            if (hitBy->getType() == "bullet") {
                game.remove(this);
                hitBy->remove();
            }
            
        }
        void shoot() {
            GhostBullet* ghostBullet = GhostBullet::getInstance((rect.x + rect.w / 2) - 10, rect.y, 20, 20, "images/ghostBullet.png", "ghostBullet");
            game.add(ghostBullet);
        }

        int getX() {
            return rect.x - 10;
        }

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
    int counter = 0;
    int resetCounter = 0;
    bool resetting;
    int shootCounter = 0;
    int whenToShoot = 0;
};



class Bullet : public MovingObject {
    public:

        static Bullet* getInstance(int x, int y, int w, int h,string imagePath, string typeName) {
            return new Bullet(x, y, w, h, imagePath, typeName);
        }

        //600, 20, 20,
        Bullet(int x, int y, int w, int h, string imagePath, string typeName) : MovingObject(x, y, w, h, imagePath, typeName) {
            type = typeName;
        }
   
        void remove() {
            game.remove(this);
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

        string getType() {return type;}

    private:
        int counter = 0;
        string type;
};

class Ship : public PlayableCharacter {
    public:

        Ship(string imagePath) : PlayableCharacter(640, 600, 55, 35, imagePath) {}

        void tick() {
        }

        void isHit(Sprite* hitBy) {
            if (remainingLives > 0 && hitBy->getType() == "ghostBullet") {
                remainingLives--;
                playSound("sounds/damageSound.mp3");
                hitBy->remove();
            }
            else if (hitBy->getType() == "ghostBullet") {
                game.remove(this);
                hitBy->remove();
            }
        }

        void spacebar() {
            //ImagePath ska läggas till
            Bullet* bullet = Bullet::getInstance((rect.x + rect.w / 2) - 10, 600, 20, 20, "images/bullet.png", "bullet");
            game.add(bullet);
        }

    private:
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

        game.add(new Ghost(x, y, 55, 35, "images/Ghost.png"));

    }

    Ship* ship = new Ship("images/ship.png");
    game.add(new Shield(100, "images/shieldDefault.png"));
    game.add(new Shield(400, "images/shieldDefault.png"));
    game.add(new Shield(700, "images/shieldDefault.png"));
    game.add(new Shield(1000, "images/shieldDefault.png"));
    game.add(ship);
    game.run();
    
    return 0;
}


