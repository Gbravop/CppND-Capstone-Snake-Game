#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <thread>
#include <mutex>

// Enum types representing game objects
enum ObjectType
{
    noObject,
    objectSnake,
    objectFood,
};

class gameObject
{
public:
    // Constructor 
    gameObject();
    // Desctructor
    ~gameObject();

    // Getter and setter
    int getID() { return _id; }
    ObjectType getType() { return _type; }

    // Behaviour method
    virtual void simulate(){};

protected:
    // Class-type Identification
    ObjectType _type;
    // Object id              
    int _id;                       
    // Threads launched within this object
    std::vector<std::thread> threads;
    // Mutex shared by objects for protecting cout 
    static std::mutex _mtx;            

private:
    // Global variable for counting object ids
    static int _idCnt; 
};

#endif