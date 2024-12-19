#include <iostream>
#include <cstdlib>
#include <ctime>

#include "SDL.h"
#include "food.h"

template <class FoodPhase>
FoodPhase MessageQueue<FoodPhase>::receive()
{
    // Perform queue modification under the lock
    std::unique_lock<std::mutex> uLock(_mutex);
    // Wait until the queue is not empty
    _cond.wait(uLock, [this] { return !_queue.empty() || _rcvStop; }); // pass unique lock to condition variable
          
    // Remove last vector element from queue
    FoodPhase msg = std::move(_queue.back());
    _queue.pop_back();
    return msg;   
}

template <class FoodPhase>
void MessageQueue<FoodPhase>::send(FoodPhase &&msg)
{
    // Perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // Add vector to queue
    _queue.push_back(std::move(msg));
    // Notify client
    _cond.notify_one(); 
}

Food::~Food() {
  // std::cout<<"Food Destructor"<<std::endl;
  // std::cout<<"Food Destructor "<< _qmsg.rcvStop2()<<std::endl;
  // std::cout<<"Food Destructor "<< _cycleStop <<std::endl;
}

// Virtual function which is executed in a thread
void Food::signalGreen()
{
    // Implementation with a while-loop that signals the phase state of the second
    // food block. The loop calls the receive function on the message queue repeatedly.
    // The method returns once it receives FoodPhase::green. 
    while(!_cycleStop){
      FoodPhase message = _qmsg.receive();
      // FoodPhase message = FoodPhase::green;
      if (message==FoodPhase::green){
        std::cout << "GREEN Phase! GO for it!" << std::endl;
        return;
      }
    }
}

// Method to start thread
void Food::simulate()
{
    // "cycleThroughPhases" is started in a thread when the public method "simulate“ is called. 
    threads.emplace_back(std::thread(&Food::cycleThroughPhases, this));
}

// Method to start thread
void Food::simulate2()
{
    // "signalGreen" is started in a thread when the public method "simulate2“ is called. 
    threads.emplace_back(std::thread(&Food::signalGreen, this)); 
}

// Virtual function which is executed in a thread
void Food::cycleThroughPhases()
{
    // Implementation with a while-loop that measures the time between two loop cycles 
    // and toggles the food phase between red and green sending an update method 
    // to the message queue using move semantics.

    // The cycle duration is a random value between 1 and 5 seconds. 
    // The while-loop uses std::this_thread::sleep_for to wait 1ms between two cycles.
    
    // Timing Settings:
    std::random_device dev;
    std::mt19937 engine(dev()); 
    std::uniform_int_distribution<int> dist(3, 6); 
    int rand_dt = dist(engine);
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dt_loop;
    // Time Loop:    
    while(!_cycleStop)
    {
        // Update Time reading:
        endTime = std::chrono::high_resolution_clock::now();
        dt_loop = endTime - startTime;

        if (dt_loop.count() >= rand_dt) {
            if (_currentPhase==FoodPhase::green)
            {
                _currentPhase = FoodPhase::red;
            } else
            {
                _currentPhase = FoodPhase::green;
            } 
            // Send update:
            _qmsg.send(std::move(_currentPhase));
            // Update Time metrics:
            std::mt19937 engine(dev());
            std::uniform_int_distribution<int> dist(3, 6);
            int rand_dt = dist(engine);
            startTime = std::chrono::high_resolution_clock::now();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Method to place food depending on snake position
void Food::Place(std::shared_ptr<Snake> &snake){
  int x, y;
  x = _random_w(_engine);
  y = _random_w(_engine);
  // Check location
  if (!snake->SnakeCell(x, y)){
    _food.x = x;
    _food.y = y;
  }
}

// Method to update food location, score, and snake's body 
bool Food::Update(std::shared_ptr<Snake> &snake){
  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);
  bool score = false;
  if (_food.x == new_x && _food.y == new_y) {
    // Place food;
    Place(snake);
    // Grow snake:
    snake->GrowBody();
    // Score update
    score = true;
  }
  return score;
}