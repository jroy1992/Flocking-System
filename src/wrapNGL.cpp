#include "wrapNGL.h"
#include<math.h>

// angle between two vectors
float wrapNGL::angleBetween(ngl::Vec3 _v1, ngl::Vec3 _v2)
{
    float theta = acos( _v1.dot(_v2)/((_v1.length())*(_v2.length())));
    return theta;
}

// clockwise normal of a vector
void wrapNGL::getNormalClockwise(ngl::Vec3 _v)
{
    float temp;
    temp = _v.m_x;
    _v.m_x = _v.m_y;
    _v.m_y = temp;
}

// anti clockwise normal of a vector
void wrapNGL::getNormalAntiClockwise(ngl::Vec3 _v)
{
    float temp;
    temp = _v.m_x;
    _v.m_x = _v.m_y;
    _v.m_y = -temp;
}

// check is a point is moving towards the centre
bool wrapNGL::isMovingTowards(ngl::Vec3 _testPt, ngl::Vec3 _objPos, ngl::Vec3 _objVel)
{
    ngl::Vec3 toPt = _testPt - _objPos;
    return(toPt.m_x*_objVel.m_x+toPt.m_y*_objVel.m_y) > 0;
}

// distance between two vectors
float wrapNGL::dist(ngl::Vec3 _v1, ngl::Vec3 _v2)
{
    float dx = _v1.m_x - _v2.m_x;
    float dy = _v1.m_y - _v2.m_y;
    return sqrt(dx*dx+dy*dy);
}
