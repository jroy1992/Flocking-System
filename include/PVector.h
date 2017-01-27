#ifndef PVector_H_
#define PVector_H_
#include<ostream>

class PVector
{
protected:
    float m_x;
    float m_y;

public:
    PVector(float _x, float _y):m_x(_x),m_y(_y){}

    PVector():m_x(0),m_y(0) {}

    friend std::ostream &operator<<(std::ostream &_o, const PVector _s)
    {
        return _o<<'['<<_s.m_x<<','<<_s.m_y<<"]\n";
    }

    float getX () const;

    float getY () const;

    void setX(float);

    void setY(float);

    void operator += (const PVector &_v)
    {
        m_x += _v.m_x;
        m_y += _v.m_y;
    }

    void operator -=(const PVector &_v)
    {
        m_x -= _v.m_x;
        m_y -= _v.m_y;
    }

    PVector operator +(const PVector &_v)const
    {
        return PVector(m_x+_v.m_x,m_y+_v.m_y);
    }

    PVector operator -(const PVector &_v)const
    {
        return PVector(m_x-_v.m_x,m_y-_v.m_y);
    }

    void mult(float);

    void div(float);

    float min (float, float);

    float max(float, float);

    float mag();

    void normalise();

    void limit(float);

    float dist(PVector, PVector);

    float angleBetween(PVector, PVector);

    void getNormalClockwise();

    void getNormalAntiClockwise();

    bool isMovingTowards(PVector, PVector, PVector);

    PVector normalPoint(PVector, PVector, PVector);
};

#endif
