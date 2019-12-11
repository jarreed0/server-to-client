#include "game.h"

Game::Game() {
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) cout << "Failed at SDL_Init()" << SDL_GetError() << endl;
  if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren) < 0) cout << "Failed at SDL_CreateWindowAndRenderer()" << SDL_GetError() << endl;
  SDL_SetWindowTitle(win, "Rage");
  running=true;
  Object p;
  p.src.y=0;
  p.src.h=p.src.w=10;
  p.dest.w=p.dest.h=10;
  //for(int i=0;i<WIDTH/10;i++) {
  //for(int k=0;k<HEIGHT/10;k++) {
  for(int i=0;i<1;i++) {int k=i;
  //p.dest.x=rand() % WIDTH;
  //p.dest.y=rand() % HEIGHT;
  p.dest.x=i*10;
  p.dest.y=k*10;
  p.src.x=(rand() % 6) * 10;
  p.img = loadImg("res/player.png");
  p.speed = SPEED;
  player.push_back(p);
  }//}
  u=d=l=r=0;
  loop();
}
Game::~Game() {cout << "close" << endl;}

void Game::loop() {  static int lastTime;
  while(running) {

    lastFrame=SDL_GetTicks();
    if(lastFrame >= (lastTime+1000)) {
      lastTime=lastFrame;
	cout << frameCount << endl;
      frameCount=0;
    }

    render();
    input();
    update();
  }}


void Game::render() {
  SDL_SetRenderDrawColor(ren, 126, 192, 238, 255);
  SDL_Rect rect;
  rect.x=rect.y=0;
  rect.w=WIDTH;
  rect.h=HEIGHT;
  SDL_RenderFillRect(ren, &rect);

  for(int i=0;i<player.size();i++) draw(player[i]);

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
for(int i=0;i<player.size();i++) {
if(u) player[i].dest.y=player[i].dest.y-player[i].speed;
if(d) player[i].dest.y=player[i].dest.y+player[i].speed;
if(l) player[i].dest.x=player[i].dest.x-player[i].speed;
if(r) player[i].dest.x=player[i].dest.x+player[i].speed;
if(player[i].dest.x+player[i].dest.w > WIDTH) player[i].dest.x = WIDTH-player[i].dest.w;
if(player[i].dest.x < 0) player[i].dest.x = 0;
if(player[i].dest.y+player[i].dest.h > HEIGHT) player[i].dest.y = HEIGHT-player[i].dest.h;
if(player[i].dest.y < 0) player[i].dest.y = 0;}
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

