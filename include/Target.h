#ifndef TARGET_H_
#define TARGET_H_

#include<ngl/Vec3.h>

class Target
{
public:
    Target() {}

    Target(ngl::Vec3 _pos, float _r, float _g, float _b)
    {
        m_tposition = _pos;
        m_tr = _r;
        m_tg = _g;
        m_tb = _b;
    }

    void setTColor(float _r, float _g, float _b);

    void changePosition(ngl::Vec3 _newPos);

    float getR() const;
    float getG() const;
    float getB() const;

    ngl::Vec3 getPos()
    {
        return m_tposition;
    }

    void setPos(ngl::Vec3 _pos)
    {
        m_tposition.m_x = _pos.m_x;
        m_tposition.m_y = _pos.m_y;
        m_tposition.m_z = _pos.m_z;
    }

    float getBoundary()
    {
        return m_tboundary;
    }

    float m_tr;
    float m_tg;
    float m_tb;
private:
    ngl::Vec3 m_tposition;
    float m_tboundary = 3.0f;
};

#endif
