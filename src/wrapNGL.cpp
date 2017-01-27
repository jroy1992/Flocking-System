#include "wrapNGL.h"
#include<math.h>

float wrapNGL::angleBetween(ngl::Vec3 _v1, ngl::Vec3 _v2)
{
    float theta = acos( _v1.dot(_v2)/((_v1.length())*(_v2.length())));
    return theta;
}

void wrapNGL::getNormalClockwise(ngl::Vec3 _v)
{
    float temp;
    temp = _v.m_x;
    _v.m_x = _v.m_y;
    _v.m_y = temp;
}

void wrapNGL::getNormalAntiClockwise(ngl::Vec3 _v)
{
    float temp;
    temp = _v.m_x;
    _v.m_x = _v.m_y;
    _v.m_y = -temp;
}

bool wrapNGL::isMovingTowards(ngl::Vec3 _testPt, ngl::Vec3 _objPos, ngl::Vec3 _objVel)
{
    ngl::Vec3 toPt = _testPt - _objPos;
    return(toPt.m_x*_objVel.m_x+toPt.m_y*_objVel.m_y) > 0;
}
