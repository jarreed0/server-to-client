#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cstdlib>

#define WIDTH 1280
#define HEIGHT 720
#define SPEED 5

struct Object {
SDL_Rect dest, src;
SDL_Texture* img;
int h, v, speed;
void setSpeed(int h, int v) {this->h=h; this->v=v;}
void move() {
 dest.x=dest.x+h;
 dest.y=dest.y+v;
}
};


class Game {
private:
bool running;
int frameCount, timerFPS, lastFrame;
SDL_Renderer* ren;
SDL_Window* win;
vector<Object> player;
int speed;
bool u,d,r,l;
public:
Game();
~Game();
void loop();
void render();
void input();
void update();
void draw(Object o);
SDL_Texture* loadImg(string i);
};

#endif
