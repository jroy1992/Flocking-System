#include"Flock.h"
#include <random>

static std::mt19937 gen;

Flock::Flock(Boid & _b, int _num)
{
    std::uniform_real_distribution<> randPos(-2,2);
    for(size_t i=0; i<_num; i++)
    {
        _b.m_position.set(ngl::Vec3(randPos(gen),randPos(gen),0.0f));
        m_boids.push_back(_b);
    }
}

/// The following section is from :-
/// Daniel Shiffman (2016). Nature of Code Examples [online]. [Accessed 2016]
/// Available from: "https://github.com/shiffman/The-Nature-of-Code-Examples/tree/master/chp06_agents/NOC_6_09_Flocking".
void Flock::runflock(char _choice)
{
    //passing the boid list to each boid
    for(Boid &b : m_boids)
    {
        b.run(m_boids, _choice);
    }
}

void Flock::addBoid(ngl::Vec3 _pos, int _num)
{
    Boid b(_pos);
    for(size_t i=0; i<_num; i++)
        m_boids.push_back(b);
}
/// End citation
