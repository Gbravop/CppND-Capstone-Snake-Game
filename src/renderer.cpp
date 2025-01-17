#include "renderer.h"
#include <iostream>
#include <string>
#include <algorithm>

// Constructor
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : sdl_window(nullptr, SDL_DestroyWindow),
      sdl_renderer(nullptr, SDL_DestroyRenderer),
      screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  // Previous version with raw pointer:
  // sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
  //                               SDL_WINDOWPOS_CENTERED, screen_width,
  //                               screen_height, SDL_WINDOW_SHOWN);

  // Modification needed to generate SDL window using unique pointer:
  sdl_window.reset(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN));

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  // Previous version with raw pointer:
  //sdl_renderer = SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED);
  
  // Modification needed to generate SDL renderer using unique pointer:
  sdl_renderer.reset(SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED));
  
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

// Destructor
Renderer::~Renderer() {
  // std::cout<<"Renderer Destructor"<<std::endl;
  
  // Use of unique pointers avoids using destructor methods below:
  //SDL_DestroyWindow(sdl_window.get());
  //SDL_DestroyRenderer(sdl_renderer);
  
  SDL_Quit();
}

// Rendering method
void Renderer::Render(std::shared_ptr<Snake> &snake, std::vector<std::shared_ptr<Food>> &food, const int &gv) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer.get());

  // Render food depending on game variant (gv)
  for (size_t nf = 0; nf<gv; nf++){
    // Standard Food's color:
    std::vector<int> rgb = {255,204,0};
    // Food's color depending on phase:
    if (nf%2!=0){
      if (food.at(nf)->getPhase()==FoodPhase::green){
        rgb= {128,255,0};}
      else{rgb= {255,0,0};}
    }
    // Rendering of shape and color:
    SDL_SetRenderDrawColor(sdl_renderer.get(), (int)rgb[0], (int)rgb[1], (int)rgb[2], 0xFF);
    block.x = food.at(nf)->Get().x * block.w;
    block.y = food.at(nf)->Get().y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  } 

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer.get(), &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer.get());
}

// Updating-Window method
void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window.get(), title.c_str());
}
