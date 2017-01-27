#include "Boid.h"
#include "PVector.h"
#include "Behavior.h"

PVector Behavior::seek(PVector target)
{
    PVector desired = position.sub(target,position);
    desired.normalise();
    desired.limit(maxspeed);

    PVector steer = velocity.sub(desired,velocity);
    steer.limit(maxforce);
    return steer;
}


PVector Behavior::separate(std::array<Boid, 50> boids)
{
    float desiredseparation = 25.0f;
    PVector steer(0.0,0.0);
    int count = 0;

    for(Boid other : boids)
    {
        float d = position.dist(position,other.position);
        if((d>0) && (d<desiredseparation))
        {
            PVector diff = position.sub(position,other.position);
            diff.normalise();
            diff.div(d);
            steer.add(steer,diff);
            count++;
        }
    }

    if(count > 0)
    {
        steer.div((float)count);
    }

    if(steer.mag() > 0)
    {
        steer.normalise();
        steer.mult(maxspeed);
        steer.sub(steer,velocity);
        steer.limit(maxforce);
    }
    return steer;
}


PVector Behavior::align(std::array<Boid, 50> boids)
{
    float neighbourdist = 50;
    PVector sum(0,0);
    int count = 0;
    for(Boid other : boids)
    {
        float d = position.dist(position, other.position);
        if((d>0) && (d<neighbourdist))
        {
            sum.add(sum,other.velocity);
            count++;
        }
    }
    if(count>0)
    {
        sum.div((float)count);
        sum.normalise();
        sum.mult(maxspeed);
        PVector steer = sum.sub(sum,velocity);
        steer.limit(maxforce);
        return steer;
    }
    else
        return PVector(0.0,0.0);
}


PVector Behavior::cohesion(std::array<Boid, 50> boids)
{
    float neighbordist = 50;
    PVector sum(0,0);
    int count = 0;
    for(Boid other : boids)
    {
        float d = position.dist(position,other.position);
        if((d>0) && (d<neighbordist))
        {
            sum.add(sum,other.position);
            count++;
        }
    }
    if(count>0)
    {
        sum.div(count);
        return seek(sum);
    }
    else
        return PVector(0.0,0.0);
}


