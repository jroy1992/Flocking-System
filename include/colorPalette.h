#ifndef COLORPALETTE_H_
#define COLORPALETTE_H_
#include "Target.h"
#include<vector>

class colorPalette
{
public:
    colorPalette();
    colorPalette(Target _tar, size_t num);

    void changeColor(ngl::Vec3 &, float &, float &, float &);

    void addTarget(Target _tar, size_t num);

    std::vector<Target> m_targets;

private:
    //std::vector<Target> m_targets;
    int m_brushSize;
    float m_spread;
};

#endif
