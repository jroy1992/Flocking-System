#include"PVector.h"
#include<math.h>

float PVector::getX() const
{
    return m_x;
}

float PVector::getY() const
{
    return m_y;
}

void PVector::setX(float _x)
{
    m_x = _x;
}

void PVector::setY(float _y)
{
    m_y = _y;
}

void PVector::mult(float _n)
{
    m_x = m_x*_n;
    m_y = m_y*_n;
}

void PVector::div(float _n)
{
    if (_n != 0.0)
    {
        m_x = m_x / _n;
        m_y = m_y / _n;
    }
}

float PVector::mag()
{
    return sqrt(m_x*m_x + m_y*m_y);
}

void PVector::normalise()
{
    float m = mag();
    if (m >0)
    {
        div(m);
    }
}

void PVector::limit(float _max)
{
    if (_max < mag())
    {
        normalise();
        mult(_max);
    }
}

float PVector::dist(PVector _v1, PVector _v2)
{
    float dx = _v1.m_x - _v2.m_x;
    float dy = _v1.m_y - _v2.m_y;
    return sqrt(dx*dx+dy*dy);
}

float PVector::angleBetween(PVector _v1, PVector _v2)
{
    float dot = _v1.m_x*_v2.m_x + _v1.m_y*_v2.m_y;
    float theta = acos(dot/((_v1.mag())*(_v2.mag())));
    return theta;
}

void PVector::getNormalClockwise()
{
    float temp;
    temp = m_x;
    setX(m_y);
    setY(temp);
}

void PVector::getNormalAntiClockwise()
{
    float temp;
    temp = m_x;
    setX(m_y);
    setY(-temp);
}

PVector PVector::normalPoint(PVector _p, PVector _a, PVector _b)
{
    PVector ap = _p - _a;
    PVector ab = _b - _a;

    ab.normalise();
    float dot = ap.m_x*ab.m_x + ap.m_y*ab.m_y;
    ab.mult(dot);

    PVector np = _a + ab;

    return np;
}

float PVector::min(float _a, float _b)
{
    if(_a<_b)
        return _a;
    else
        return _b;
}

float PVector::max(float _a, float _b)
{
    if(_a>_b)
        return _a;
    else
        return _b;
}

bool PVector::isMovingTowards(PVector _testPt, PVector _objectPos, PVector _objectVel)
{
    PVector toPt = _testPt - _objectPos;
    return (toPt.m_x*_objectVel.m_x+toPt.m_y*_objectVel.m_y) > 0;
}

