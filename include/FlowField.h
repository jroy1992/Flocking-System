#ifndef FLOWFIELD_H
#define FLOWFIELD_H
#include <ngl/Vec3.h>
#include"noise.h"
#include <iostream>
#include <vector>

class FlowField
{
protected:
    int rows;
    int columns;
    int resolution = 1;
    int m_height;
    int m_width;
    noise::Perlin Pnoise;

    std::vector<std::vector<ngl::Vec3>> m_grid;
public:
    FlowField() {}
    FlowField(int r)
    {
        resolution = r;
        columns = 1024 / resolution;
        //std::cout<<"columns = "<<columns;
        rows = 720 / resolution;
        //std::cout<<"rows = "<<rows;
        //m_grid = new PVector* [rows*columns];
        init();
    }

    void init();
    int constrain(int, int, int);
    ngl::Vec3 lookup(ngl::Vec3);
};
#endif
