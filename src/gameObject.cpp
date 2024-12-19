#include <algorithm>
#include <iostream>
#include <chrono>
#include "gameObject.h"

// Initialize static variables
int gameObject::_idCnt = 0;
std::mutex gameObject::_mtx;

// Constructor
gameObject::gameObject()
{
    _type = ObjectType::noObject;
    _id = _idCnt++;
}

// Destructor
gameObject::~gameObject()
{
    // std::cout<<"gameObject Destructor"<<std::endl; 
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}