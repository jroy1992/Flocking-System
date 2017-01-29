#include "Boid.h"
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Transformation.h>
#include <cmath>
#define _USE_MATH_DEFINES
#include <iostream>

/// Modified from:
/// Daniel Shiffman (July, 2016). The-Nature-of-Code-Examples [online]
/// [Accessed 2016]. Available from: "https://github.com/shiffman/The-Nature-of-Code-Examples/tree/master/chp06_agents/NOC_6_09_Flocking".


void Boid::run(std::vector<Boid> & _boids, char _choice)
{
    flock(_boids, _choice);
    borders();
    update();
}

void Boid::update()
{
    //updating the varying attributes of the boid
    m_velocity+=m_acceleration;
    m_velocity.normalize();
    m_velocity*=m_maxspeed;
    m_position+=m_velocity;

    // resetting acceleration to 0 after each cycle
    m_acceleration*=0.0f;
}

void Boid::applyForce(ngl::Vec3 _force)
{
    /* applying force to make the boid move.
     * F = ma Can have "m" in case the boids are of diff sizes.
     */
    m_acceleration+=_force;
}

void Boid::borders()
{
    if(m_position.m_x < -13.5)
        m_position.m_x = 13.5;
    if(m_position.m_y < -10)
        m_position.m_y = 10;
    if(m_position.m_x > 13.5)
        m_position.m_x = -13.5;
    if(m_position.m_y > 10)
        m_position.m_y = -10;
}


void Boid::flock(std::vector<Boid> & _boids, char _choice)
{
    ngl::Vec3 sep = separate(_boids);
    ngl::Vec3 ali = align(_boids);
    ngl::Vec3 coh = cohesion(_boids);
    ngl::Vec3 path = followPath(p);
    //ngl::Vec3 flow1 = follow(0);
    //ngl::Vec3 flow2 = follow(1);

    switch(_choice)
    {
    case 's':
    case 'S':
            m_maxspeed = 1;
            sep*=1.5;
            applyForce(sep);
            break;
    case 'a':
    case 'A':
            m_maxspeed = 1;
            ali*=3.0;
            applyForce(ali);
            break;
    case 'c':
    case 'C':m_maxspeed = 1;
            coh*=3.0;
            applyForce(coh);
            break;
    case 'f':
    case 'F':
            m_maxspeed = 2;
            sep*=1.5;
            ali*=3.0;
            coh*=3.0;
            applyForce(sep);
            applyForce(ali);
            applyForce(coh);
            break;
     case 'p':
     case 'P':
            m_maxspeed = 1;
            path*=8;
            applyForce(path);
            break;
//     case 'l':
//     case 'L':
//            m_maxspeed = 2;
//            applyForce(flow1);
//            break;
//    case 'm':
//    case 'M':
//           m_maxspeed = 2;
//           applyForce(flow2);
           break;
     default:
            break;
    }
}



//find the distance between boid location and target and steer towards target with maxForce
ngl::Vec3 Boid::seek(ngl::Vec3 _target)
{
    ngl::Vec3 desired = _target - m_position;
    desired.normalize();
    desired*=m_maxspeed;

    ngl::Vec3 steer = desired - m_velocity;
    steer*=m_maxforce;
    return steer;
}


// method to move away if a neighboring boid is within the line of sight
ngl::Vec3 Boid::separate(std::vector<Boid> & _boids)
{
    float desiredSeparation = 5.0f;
    ngl::Vec3 steer(0.0f,0.0f,0.0f);
    int count = 0;

    for(Boid &other : _boids)
    {
        float d = wrap.dist(m_position,other.m_position);

        if((d>0) && (d<desiredSeparation))
        {
            //find the and add the distance between this boid's location and all neighbor boids' location
            ngl::Vec3 diff = m_position - other.m_position;
            if((diff.m_x != 0.0f) && (diff.m_y != 0.0f) && (diff.m_z != 0.0f))
                diff.normalize();
            diff/=d;
            steer+=diff;
            count++;
        }
    }

    if(count > 0)
    {
        //the average will be used as desired velocity for steering in opp direction to neighbors
        steer/=(float)count;
    }

    if(steer.length() > 0)
    {
        steer.normalize();
        steer*=m_maxspeed;
        steer-=m_velocity;
        steer.normalize();
        steer*=m_maxforce;
    }
    return steer;
}


// method to match a boid's velocity with that of its neighbors
ngl::Vec3 Boid::align(std::vector<Boid> & _boids)
{
    float neighbourdist = 5.0f;
    ngl::Vec3 sum(0.0f,0.0f,0.0f);
    int count = 0;
    //desired velocity = avg velocity of all the boids
    for(Boid &other : _boids)
    {
        float d = wrap.dist(m_position, other.m_position);
        if((d>0) && (d<neighbourdist))
        {
            sum+=other.m_velocity;
            count++;
        }
    }
    if(count>0)
    {
        sum/=(float)count;
        sum.normalize();
        sum*=m_maxspeed;
        ngl::Vec3 steer = sum-m_velocity;
        steer.normalize();
        steer*=m_maxforce;
        return steer;
    }
    else
    {
        sum.null();
        return sum;
    }
}


// boids ability to group together
ngl::Vec3 Boid::cohesion(std::vector<Boid> & _boids)
{
    float neighbordist = 5.0f;
    ngl::Vec3 sum(0.0f,0.0f,0.0f);
    int count = 0;

    // add the positions of all the neigbors and seek the avg position
    for(Boid &other : _boids)
    {
        float d = wrap.dist(m_position, other.m_position);
        if((d>0) && (d<neighbordist))
        {
            sum+=other.m_position;
            count++;
        }
    }
    if(count>0)
    {
        sum/=(float)count;
        return seek(sum);
    }
    else
    {
        sum.null();
        return sum;
    }
}

// flow field following based on the choice which field to set up
ngl::Vec3 Boid::follow(int _ffchoice)
{
    FlowField floww(8, _ffchoice);
    ngl::Vec3 desired = floww.lookup(m_position,_ffchoice);
    desired*=25;

    ngl::Vec3 steer = desired - m_velocity;
    steer*=100;

    return steer;
}

/// End Citation


/// Modified from:
/// Fernando Bevilacqua (July, 2013). Understanding Steering Behaviors: Path Following [online]
/// [Accessed 2017]. Available from: "https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-path-following--gamedev-8769".
ngl::Vec3 Boid::followPath(Path p)
{
    ngl::Vec3 target;
    if( p.m_points.size() > 0)
    {
        target = p.m_points[pTargetPoint];
        if((wrap.dist(target,m_position)) <= 4)
        {
            pTargetPoint++;

            if(pTargetPoint >= p.m_points.size())
                pTargetPoint = p.m_points.size()-1;
        }

    }
    return seek(target);
}
/// End Citation
