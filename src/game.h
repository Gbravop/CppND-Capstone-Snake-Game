#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include <mutex>
#include <algorithm>

#include "SDL.h"

#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "food.h"

class Game {
 public:
  // Constructor
  Game(std::size_t grid_width, std::size_t grid_height, int nf);
  // Destructor
  ~Game();
  
  // Run Method
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  // Get score and get size methods
  int GetScore() const;
  int GetSize() const;

 private:
  // Snake object
  std::shared_ptr<Snake> snake;
  // Food object
  std::vector<std::shared_ptr<Food>> food;
  // Game score
  int score{0};
  // Game flag to update score depending on Food phase
  std::vector<bool> _scflags{};
  // Game variant
  const int _gv;

  // Method to create objects
  void CreateObjects(int grid_width, int grid_height, int nf);
  // Game Update method
  void Update();
  // Score Update method
  void UpdateScore(std::vector<bool> scflags);

};

#endif