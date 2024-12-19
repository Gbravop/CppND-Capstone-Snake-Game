#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "snake.h"
#include "food.h"

class Renderer 
{
 public:
  // Constructor
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  // Destructor
  ~Renderer();

  // Method to Launch Renderer
  void Render(std::shared_ptr<Snake> &snake, std::vector<std::shared_ptr<Food>> &food, const int &gv);
  // Method to Update Title Window
  void UpdateWindowTitle(int score, int fps);

 private:
  // SDL_Window *sdl_window;
  // SDL_Renderer *sdl_renderer;
  
  // Using unique pointers instead of raw pointers:
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sdl_window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif