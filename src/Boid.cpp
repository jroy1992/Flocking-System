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


void Boid::getNormalClockwise()
{
    float temp;
    temp = m_position.m_x;
    m_position.m_x = m_position.m_y;
    m_position.m_y = temp;
}

void Boid::getNormalAntiClockwise()
{
    float temp;
    temp = m_position.m_x;
    m_position = m_position.m_y;
    m_position.m_y = -temp;
}

void Boid::run(std::vector<Boid> & _boids)
{
    //std::cout<<m_position<<' '<<m_velocity<<' '<<m_acceleration;
    flock(_boids);
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

    //std::cout<<"x_ velocity="<<m_velocity.getX()<<"y_ velocity="<<m_velocity.getY()<<"z_ velocity="<<m_velocity.getZ()<<"\n";
    //std::cout<<"x_ position="<<m_position.getX()<<"y_ position="<<m_position.getY()<<"z_ position="<<m_position.getZ()<<"\n";
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


void Boid::flock(std::vector<Boid> & _boids)
{
    ngl::Vec3 sep = separate(_boids);
    ngl::Vec3 ali = align(_boids);
    ngl::Vec3 coh = cohesion(_boids);
    //ngl::Vec3 swm = swarm(_boids);
    //ngl::Vec3 path = followPath(p);
    //std::cout<<"m in func flock \n";
    //ngl::Vec3 flow = follow();
    /* assigning weights to individual behaviors
     * and applying the returned steering force
     */

    sep*=1.5;//1.5;
    ali*=3.0;
    coh*=3.0;
    //swm*=4;
    //path*=8;

    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
    //applyForce(swm);
    //applyForce(path);
    //applyForce(flow);
}


//void Boid::draw() const
//{
//    //_i.setPixel(m_position.getX(), m_position.getY(), 255,0,0);
//    ngl::VAOPrimitives * prim = ngl::VAOPrimitives::instance();
//    ngl::Transformation trans;
//    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
//    shader->use(m_flock->getShaderName());
//    trans.setPosition(m_boid);
//}


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
        float d = m_position.dist(m_position,other.m_position);

        if((d>0) && (d<desiredSeparation))
        {
            //find the and add the distance between this boid's location and all neighbor boids' location
            ngl::Vec3 diff = m_position - other.m_position;
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
        float d = m_position.dist(m_position, other.m_position);
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
        float d = m_position.dist(m_position, other.m_position);
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

/// End Citation


// method to gather the boids like swarms of flies
ngl::Vec3 Boid::swarm(std::vector<Boid> & _boids)
{
    float lineOfSight = 5;
    float viewAngle = M_PI/4;
    std::vector<Boid>::iterator it;
    ngl::Vec3 target(10.0f,0.0f,0.0f);
    bool isMovingToCenter;
    ngl::Vec3 steer(0.0f,0.0f,0.0f);
    int count = 0;

    //the boid checks other boids within its viewAngle, finds the difference vector from each and directs it clockwise normally
//    for(it=_boids.begin(); it!=_boids.end(); it++)
//    {
//        float dist = m_position.dist(m_position, it->m_position);
//        ngl::Vec3 direction = it->m_position - m_position;
//        float theta = wrap.angleBetween(m_velocity, direction);

//        if((float)abs(theta)<viewAngle && dist>0 && dist<lineOfSight)
//        {
//            /* the direction needs to be changed to getNormalClockwise() if they start moving out of the wi
//             * working on the fix
//             */
//            wrap.getNormalClockwise(direction);
////            isMovingToCenter = wrap.isMovingTowards(center, m_position, m_velocity);
////            if(isMovingToCenter > 0)
////            {
////                wrap.getNormalClockwise(direction);
////            }
//            direction.normalize();
//            direction/=dist;
//            steer+=direction;
//            count++;
//        }
//    }

//    if(count > 0)
//    {
//        steer/=(float)count;
//    }

//    if(steer.length()>0)
//    {
//        steer.normalize();
//        steer*=m_maxspeed;
//        steer-=m_velocity;
//        steer*=m_maxforce;
//    }
    steer = seek(target);
    return steer;
}


/*
PVector Boid:: followPath(Path p)
{
    float worldRec = 100000;
    PVector predict = m_velocity;
    predict.normalise();
    predict.mult(25);

    PVector predictLoc = m_position+predict;
    PVector normal(0.0,0.0);
    PVector target(0.0,0.0);

    for(int i=0; i<p.m_points.size()-1;i++)
    {
        PVector a = p.m_points[i];
        PVector b = p.m_points[i+1];
        PVector normalPnt = predictLoc.normalPoint(predictLoc, a, b);

       // if(i+1 != p.m_points.size()-1)
        //{
            if(normalPnt.getX()<a.getX() || normalPnt.getY()>b.getX())

            //if(normalPnt.getX()>b.getX() || normalPnt.getY()>b.getY()) //||normalPnt.getY()<a.getY()||normalPnt.getY()>b.getY())
                normalPnt = b;
        //}

        float distance = normalPnt.dist(predictLoc, normalPnt);
        if(distance < worldRec)
        {
            worldRec = distance;
            normal = normalPnt;
            PVector dir = b-a;
            dir.normalise();
            dir.mult(25);
            target = normalPnt;
            target = target + dir;
        }
    }
        if(worldRec > p.getRadius())
            return seek(target);
        else
            return PVector(0.0,0.0);
}
*/

ngl::Vec3 Boid::follow()
{
    FlowField floww(8);
    ngl::Vec3 desired = floww.lookup(m_position);
    desired*=25;

    ngl::Vec3 steer = desired - m_velocity;
    steer*=100;

    return steer;
}


ngl::Vec3 Boid::followPath(Path p)
{
//    m_r = 0.99609375;
//    m_g = 0.59765625;
//    m_b = 0.19921875;
    ngl::Vec3 target;
    if( p.m_points.size() > 0)
    {
        std::cout<<"size: "<<p.m_points.size();
        target = p.m_points[pTargetPoint];
        if((m_position.dist(target,m_position)) <= 4)
        {
            pTargetPoint++;

            if(pTargetPoint >= p.m_points.size())
                pTargetPoint = p.m_points.size()-1;
        }

    }
    return seek(target);
}
