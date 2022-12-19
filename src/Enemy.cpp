#include "Enemy.h"
#include <SDL2/SDL.h>
#include "Constants.h"
#include <SDL2/SDL_image.h> 
#include "System.h"

using namespace std;

Enemy::Enemy(int x, int y, int w, int h, string imagePath):Sprite(x, y, w, h, imagePath) {
    texture = IMG_LoadTexture(sys.renderer, (constants::gResPath + imagePath).c_str() );
}

Enemy::~Enemy() {
    SDL_DestroyTexture(texture);
}

Enemy* Enemy::getInstance(int x, int y, int w, int h, string imagePath) { 
    return new Enemy(x, y, w, h, imagePath);
}

void Enemy::draw() const {
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.renderer, texture, NULL, &rect);
}

void Enemy::tick() {

}

void Enemy::isHit() {

}

void Enemy::shoot() {
    
}