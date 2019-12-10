#include "game.h"

Game::Game() {
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) cout << "Failed at SDL_Init()" << SDL_GetError() << endl;
  if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren) < 0) cout << "Failed at SDL_CreateWindowAndRenderer()" << SDL_GetError() << endl;
  SDL_SetWindowTitle(win, "Rage");
  running=true;
  player.dest.x=player.dest.y=0;
  player.src.x=player.src.y=0;
  player.dest.w=player.dest.h=10;
  player.src.w=player.src.h=10;
  player.img = loadImg("res/player.png");
  u=d=l=r=0;
  player.speed = SPEED;
  loop();
}
Game::~Game() {cout << "close" << endl;}

void Game::loop() {  static int lastTime;
  while(running) {

    lastFrame=SDL_GetTicks();
    if(lastFrame >= (lastTime+1000)) {
      lastTime=lastFrame;
      frameCount=0;
    }

    render();
    input();
    update();
  }
}


void Game::render() {
  SDL_SetRenderDrawColor(ren, 126, 192, 238, 255);
  SDL_Rect rect;
  rect.x=rect.y=0;
  rect.w=WIDTH;
  rect.h=HEIGHT;
  SDL_RenderFillRect(ren, &rect);

  draw(player);

  frameCount++;
  int timerFPS = SDL_GetTicks()-lastFrame;
  if(timerFPS<(1000/60)) {
    SDL_Delay((1000/60)-timerFPS);
  }

  SDL_RenderPresent(ren);
}

void Game::input() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) {running=false; cout << "Quitting" << endl;}
    if(e.type == SDL_KEYDOWN) {
      if(e.key.keysym.sym == SDLK_ESCAPE) running=false;
      if(e.key.keysym.sym == SDLK_w) {u=1; d=0;}
      if(e.key.keysym.sym == SDLK_a) {l=1; r=0;}
      if(e.key.keysym.sym == SDLK_s) {d=1; u=0;}
      if(e.key.keysym.sym == SDLK_d) {r=1; l=0;}
    }
    if(e.type == SDL_KEYUP) {
      if(e.key.keysym.sym == SDLK_w) u=0;
      if(e.key.keysym.sym == SDLK_a) l=0;
      if(e.key.keysym.sym == SDLK_s) d=0;
      if(e.key.keysym.sym == SDLK_d) r=0;
    }
  }
}

void Game::update() {
if(u) player.dest.y=player.dest.y-player.speed;
if(d) player.dest.y=player.dest.y+player.speed;
if(l) player.dest.x=player.dest.x-player.speed;
if(r) player.dest.x=player.dest.x+player.speed;
//player.move();
if(player.dest.x+player.dest.w > WIDTH) player.dest.x = WIDTH-player.dest.w;
if(player.dest.x < 0) player.dest.x = 0;
if(player.dest.y+player.dest.h > HEIGHT) player.dest.y = HEIGHT-player.dest.h;
if(player.dest.y < 0) player.dest.y = 0;
}

void Game::draw(Object o) {
SDL_Rect dest = o.dest;
SDL_Rect src = o.src;
SDL_RenderCopyEx(ren, o.img, &src, &dest, 0, NULL, SDL_FLIP_NONE);
}

SDL_Texture* Game::loadImg(string i) {
  SDL_Surface* surf;
  if(IMG_Load(i.c_str()) < 0) {
    cout << "Failed at IMG_Load()" << IMG_GetError() << endl;
  } else {
    surf= IMG_Load(i.c_str());
  }
  return SDL_CreateTextureFromSurface(ren, surf);
}

