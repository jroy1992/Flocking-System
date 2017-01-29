#ifndef BOID_H_
#define BOID_H_

#include <ngl/Vec3.h>
#include "Path.h"
#include "FlowField.h"
#include <vector>
#include "wrapNGL.h"

class Boid
{
public:

    ngl::Vec3 m_position;
    ngl::Vec3 m_velocity;
    ngl::Vec3 m_acceleration;

    // initial light greyish color for the boids
    float m_r = 0.8f;
    float m_g = 0.8f;
    float m_b = 0.8f;

    float m_maxspeed;
    float m_maxforce;

    Path p;
    // for path following: points set on the path at each turning
    int pTargetPoint = 0;

    int ffchoice = 0;

    Boid():m_velocity(1.0f,1.0f,0.0f),m_acceleration(0.0f,0.0f,0.0f){}

    Boid(ngl::Vec3 _pos):m_position(_pos)
    {
        m_maxspeed = 2;
        m_maxforce = 0.1;
    }

    wrapNGL wrap;

    void run(std::vector<Boid> &, char);

    void applyForce(ngl::Vec3);

    void flock(std::vector<Boid> &, char);

    void update();

    void borders();

    ngl::Vec3 seek(ngl::Vec3);

    ngl::Vec3 separate(std::vector<Boid> &);

    ngl::Vec3 align(std::vector<Boid> &);

    ngl::Vec3 cohesion(std::vector<Boid> &);

    ngl::Vec3 swarm(std::vector<Boid> &);

    ngl::Vec3 followPath(Path);

    ngl::Vec3 follow(int);

};

#endif
