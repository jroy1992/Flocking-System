#ifndef COLORPALETTE_H_
#define COLORPALETTE_H_
#include "Target.h"
#include<vector>
#include "wrapNGL.h"

class colorPalette
{
public:
    colorPalette();
    colorPalette(Target _tar, size_t num);

    wrapNGL wrapp;

    // to change the color of the boids as they encounter a color source
    void changeColor(ngl::Vec3 &, float &, float &, float &);

    // to add new targets
    void addTarget(Target _tar, size_t num);

    std::vector<Target> m_targets;

};

#endif
