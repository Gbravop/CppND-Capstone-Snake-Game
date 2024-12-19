#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <memory>

#include "SDL.h"
#include "gameObject.h"

class Snake : public gameObject, public std::enable_shared_from_this<Snake>  
{
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  // Constructor
  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}
  // Destructor
  ~Snake();      

  // Standard methods
  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);

  // Method to launch update function in a thread
  void simulate();

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif