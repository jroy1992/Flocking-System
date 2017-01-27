#ifndef FLOCK_H_
#define FLOCK_H_

#include <ngl/Vec3.h>
#include"Boid.h"
#include<vector>
#include<memory>
#include <ngl/Camera.h>

class Flock
{
public:

    std::vector<Boid> m_boids;
    Flock(Boid & _b, int _num);

    //calls run func of Boid class for each boid
    void runflock();

    //adds num amount of new Boid to the flock
    void addBoid(ngl::Vec3 _pos, int _num);
};

#endif
