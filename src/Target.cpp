#include "Target.h"

void Target::setTColor(float _r, float _g, float _b)
{
    m_tr = _r;
    m_tg = _g;
    m_tb = _b;
}


void Target::changePosition(ngl::Vec3 _newPos)
{
    m_tposition = _newPos;
}


float Target::getR()const
{
    return m_tr;
}


float Target::getG()const
{
    return m_tg;
}


float Target::getB()const
{
    return m_tb;
}
