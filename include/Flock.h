#ifndef FLOCK_H_
#define FLOCK_H_

#include <ngl/Vec3.h>
#include"Boid.h"
#include<vector>

class Flock
{
public:
    //to store user's choice for the desired flocking behavior
    char m_choice;

    // storing boids' information
    std::vector<Boid> m_boids;

    Flock(Boid & _b, int _num);

    //calls run func of Boid class for each boid
    void runflock(char);

    //adds num amount of new Boid to the flock
    void addBoid(ngl::Vec3 _pos, int _num);
};

#endif
