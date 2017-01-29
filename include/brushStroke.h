#ifndef BRUSHSTROKE _H_
#define BRUSHSTROKE _H_
#include "Boid.h"

class brushStroke
{
public:
    brushStroke(int _bsize, float _spread);

    void allotBrush(std::vector<Boid>);

    void applyColor(std::vector<Boid>);

    void addBrush(int _bsize, float _spread);

private:
    int m_bsize;
    float m_spread;
    std::vector<Boid> m_brushList;

    void startBrushes();
};

#endif
