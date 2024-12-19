# CPPND: Capstone Snake Game Example

This is a modified repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

This project solution extends the Snake game, following the principles learned throughout the Udacity C++ Nanodegree Program.

## New Features
* The user has the option to choose between two game variants: (1) standard game, (2) modified game.
* The modified game includes an additional food block, which toggles between two phases: red and green.
  * Red Phase: Reduces the score by 2 points and increases the speed by 0.03.
  * Green Phase: Increases the score by 2 points and decreases the speed by 0.01.
  * The food phases change randomly every 3 to 6 seconds.
  * The terminal prints a message when the green phase is active.

<img src="snake_game_v2.gif"/>

## Addressed Rubric Points
* README modified and covering all required points: instructions, new features, and rubric.
* Compiling and Testing: The project uses cmake and make as provided in the starter repo.
* Loops, Functions, I/O: The project
  1. Adds control structures and is organized into functions: food.h, food.cpp, gameObject.h, gameObject.cpp.
  2. Accepts user input and processes the input: main.cpp - line 17; game.h - line 19; game.cpp - lines 6, 15, 71, 81, 102.
  3. Uses data structures and immutable variables: game.h - lines 34, 40.  
* Object Oriented Programming:
  1. Classes added: food.h, gameObject.h.
  2. Class constructors use member initialization lists: food.h - line 56; renderer.cpp - lines 10, 11.
  3. Class implementation details provided via function names and comments: food.h, food.cpp, gameObject.h, gameObject.cpp.
  4. Classes follow inheritance hierarchy: gameObject.h, snake.h, food.h.
  5. Template generalizes functions or classes: food.h - line 26.   
* Memomry Management: The project uses
  1. References in function declarations: food.h - lines 71, 72; food.cpp - lines 116, 128.
  2. Destructors appropriately: gameObject.h - line 22; gameObject.cpp - line 18.
  3. Move semantics to move data instead of copying it: food.cpp - lines 17, 29, 104.
  4. Smart pointers instead of raw pointers: food.h - lines 71, 72; food.cpp - lines 116, 128; game.h - lines 32, 34; game.cpp - lines 64, 66; renderer.h - lines 29, 30; renderer.cpp - lines 29, 43.         
* Concurrency: The project uses
  1. Multiple threads to update the snake state and to cycle through the food phases: game.cpp - lines 72, 79, 82; snake.cpp - line 94; food.cpp - lines 60, 67; gameObject.h - line 37.
  2. Uses a mutex or lock to protect data shared across threads: food.h - line 33; food.cpp - lines 12, 26.
  3. A condition variable to synchronize thread execution: food.h - line 45; food.cpp - lines 14, 31.

Other than the dependencies identified below, no additional libraries are needed to run the project.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
