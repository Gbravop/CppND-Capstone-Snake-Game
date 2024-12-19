#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <random>
#include <vector>
#include <memory>

#include <future>
#include <mutex>
#include <deque>
#include <condition_variable>

#include "SDL.h"
#include "snake.h"
#include "gameObject.h"

// Enum types representing food's phases in game variant 2
enum FoodPhase
{
    red,
    green,
};

// MessageQueue Template
template <class T>
class MessageQueue
{
public:
    // Constructor
    MessageQueue(){};
    // Destructor
    ~MessageQueue(){ // std::cout<<"Msg_Destructor"<<std::endl;
        // std::cout<<"Msg_Destructor "<< _rcvStop <<std::endl;
        };
    // Receive and send methods:
    T receive();
    void send(T &&msg);
    // Get and set methods for flags
    void rcvStop() {_rcvStop=true;}
    bool rcvStop2() {return _rcvStop;}

private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _queue;

    // Flag to quit receive-send methods.
    bool _rcvStop{false};    
};

class Food : public gameObject, public std::enable_shared_from_this<Food> 
{
 public:
  // Constructor / Destructor
  Food(int grid_width, int grid_height)
     : _currentPhase(FoodPhase::red),
       _engine(_dev()),
       _random_w(0, static_cast<int>(grid_width - 1)),
       _random_h(0, static_cast<int>(grid_height - 1)) {}
  ~Food();
  // Getters / Setters
  FoodPhase getPhase() {return _currentPhase;}
  SDL_Point Get() {return _food;}

  // Method to launch "cycleThroughPhases" function in a thread.
  void simulate();
  // Method to launch "signalGreen" function in a thread.
  void simulate2();
  // Methods for placing and updating the food object.
  void Place(std::shared_ptr<Snake> &snake);
  bool Update(std::shared_ptr<Snake> &snake);
  // Methods to signal that the game has ended.
  void cycleStop() { _cycleStop=true;_qmsg.rcvStop();}
  
 private:
  // Method to cycle through food phases in second game variant.
  void cycleThroughPhases();
  // Method to signal the green food phase.
  void signalGreen();
  
  // Food object and phase state:
  SDL_Point _food;
  FoodPhase _currentPhase;

  // Random generators and variables:
  std::random_device _dev;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;

  // Message queue:
  MessageQueue<FoodPhase> _qmsg;

  // Boolean variable to signal that the game has ended.    
  bool _cycleStop{false};

};

#endif