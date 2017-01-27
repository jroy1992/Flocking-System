#ifndef BOID_H_
#define BOID_H_

#include <ngl/Vec3.h>
#include "Path.h"
#include "FlowField.h"
#include <vector>
#include <iostream>
#include "wrapNGL.h"

class Boid
{
public:

    ngl::Vec3 m_position;
    ngl::Vec3 m_velocity;
    ngl::Vec3 m_acceleration;
    float m_r = 0.8f;
    float m_g = 0.8f;
    float m_b = 0.8f;

    float m_maxspeed;
    float m_maxforce;
    int pTargetPoint = 0;
    Path p;
    //const Flock *m_flock;

    Boid():m_velocity(1.0f,1.0f,0.0f),m_acceleration(0.0f,0.0f,0.0f){}

    Boid(ngl::Vec3 _pos):m_position(_pos)
    {
        m_maxspeed = 2;
        m_maxforce = 0.1;
    }

    wrapNGL wrap;

    void run(std::vector<Boid> &);

    void applyForce(ngl::Vec3);

    void flock(std::vector<Boid> &);

    void update();

    void borders();

    //void draw() const;

    ngl::Vec3 seek(ngl::Vec3);

    ngl::Vec3 separate(std::vector<Boid> &);

    ngl::Vec3 align(std::vector<Boid> &);

    ngl::Vec3 cohesion(std::vector<Boid> &);

    ngl::Vec3 swarm(std::vector<Boid> &);

    void view(std::vector<Boid> &);

    ngl::Vec3 followPath(Path);

    ngl::Vec3 follow();

    void getNormalClockwise();

    void getNormalAntiClockwise();

    float angleBetween(ngl::Vec3,ngl::Vec3);

};

#endif
