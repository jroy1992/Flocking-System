#ifndef BEHAVIOR_H
#define BEHAVIOR_H
#include"Boid.h"
#include"PVector.h"
#include<array>

template<class Boid>
class Behavior
{
public:
    Behavior(){}

    Behavior(std::array<Boid, 50>){}

    PVector seek(PVector);

    PVector separate(std::array<Boid, 50>);

    PVector align(std::array <Boid, 50>);

    PVector cohesion(std::array<Boid, 50>);
};

#endif
