#ifndef WRAPNGL_H_
#define WRAPBGL_H_
#include <ngl/Vec3.h>

class wrapNGL
{
public:
    float angleBetween(ngl::Vec3, ngl::Vec3);

    void getNormalClockwise(ngl::Vec3);

    void getNormalAntiClockwise(ngl::Vec3);

    bool isMovingTowards(ngl::Vec3, ngl::Vec3, ngl::Vec3);
};

#endif
