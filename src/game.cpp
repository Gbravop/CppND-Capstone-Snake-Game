#include "game.h"
#include <iostream>
#include "SDL.h"

// Constructor
Game::Game(std::size_t grid_width, std::size_t grid_height, int nf) : _gv(nf) {
  CreateObjects(grid_width, grid_height, nf);
}
// Destructor
Game::~Game()
{
    // std::cout<<"Game Destructor"<<std::endl;
    // For second game variant, it signals end of game to stop
    // while-loops running in threads.
    if (_gv>=2) {
      food.at(1)->cycleStop();
    }
}

// Run Method
void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, _gv);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

// Method to create objects:
void Game::CreateObjects(int grid_width, int grid_height, int unf) {
  // The method creates shared pointers for the snake and food objects.
  snake = std::make_shared<Snake>(grid_width,grid_height);
  for (size_t nf = 0; nf<unf; nf++) {
    food.push_back(std::make_shared<Food>(grid_width,grid_height));
    // The method places the food object depending on the game variant.
    food.at(nf)->Place(snake);
  }
  // Food's cycle through phases in second game variant:
  if (unf>=2){
    food.at(1)->simulate();
  }   
}

void Game::Update() {
  if (!snake->alive) return;
  // Updating snake's state:
  snake->simulate();
  // Food's signaling of food state in second game variant:
  if (_gv>=2){
    food.at(1)->simulate2();
  }
  // Updating food's state:
  _scflags = {}; // Re-initialize vector
  // For each food object, the method places the food object and updates the 
  // snake state. Also, a score flag is returned and stored for further processing
  // using the "UpdateScore" method.
  std::for_each(food.begin(), food.end(), [&](std::shared_ptr<Food> &f) {
        _scflags.emplace_back(f->Update(snake));});
  // Updating Score:
  UpdateScore(_scflags);
}

void Game::UpdateScore(std::vector<bool> scflags) {
// The method updates the score according to food object and its phase.
 if (scflags.at(0)==true){
   score++;
   snake->speed += 0.02;
 }
 // Below code applies if running second game variant:
 if (_gv>=2){ 
  if (scflags.at(1)==true && food.at(1)->getPhase()==FoodPhase::green){
    score += 2;
    snake->speed -= 0.01;
  }
  else if (scflags.at(1)==true && food.at(1)->getPhase()==FoodPhase::red){
    if (score>=2) 
    {score -= 2;} 
    else {score = 0;}
    snake->speed += 0.03;
  }
 }
}
// Methods to get game's score and snake's size: 
int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }

