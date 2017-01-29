#ifndef FLOWFIELD_H_
#define FLOWFIELD_H_

#include <ngl/Vec3.h>
#include <vector>

class FlowField
{
protected:
    int rows;
    int columns;
    int resolution = 1;

    // 2D vectors to store grid information where the flow fields will be laid out
    std::vector<std::vector<ngl::Vec3>> m_random;
    std::vector<std::vector<ngl::Vec3>> m_csWave;

public:
    FlowField() {}
    FlowField(int r, int choice)
    {
        resolution = r;
        columns = 1024 / resolution;
        rows = 720 / resolution;

        init(choice);
    }

    // initialize the flow field
    void init(int);

    // to constrain the position of the boid between window boundaries
    int constrain(int, int, int);

    // returns vector on the grid at the boid's position
    ngl::Vec3 lookup(ngl::Vec3, int);
};
#endif
