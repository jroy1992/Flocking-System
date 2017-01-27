#include"FlowField.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

static std::mt19937 gen;

int FlowField::constrain(int amt, int low, int high)
{
    if (amt < low)
        amt=low;

    if(amt > high)
        amt = low;

    return amt;
}


void FlowField::init()
{
    std::uniform_real_distribution<> randTheta(-M_PI,M_PI);
    float xoff = 0;
    for (int i = 0; i < rows; i++)
    {
        float yoff = 0;
        std::vector<ngl::Vec3> ro;
        for (int j = 0; j < columns; j++)
        {            
            //m_grid.push_back(ngl::Vec3(1.0f,0.0f,0.0f));
//            float theta = M_PI/4;
//            ro.push_back(ngl::Vec3(cos(theta),sin(theta)*2,0.0f));
            float phi;
            //Pnoise.noise(xoff,yoff,0.0);
            phi = (Pnoise.noise(xoff,yoff)/ 2)*M_PI/4;
            ro.push_back(ngl::Vec3(phi,phi*2,0.0f));
            yoff += 0.1;
        }
        m_grid.push_back(ro);
        xoff += 0.1;
    }
}


ngl::Vec3 FlowField::lookup(ngl::Vec3 _position)
{
    int col = constrain(_position.getX()/resolution, 0, columns - 1);
    int row = constrain(_position.getY()/resolution, 0, rows - 1);
    return m_grid[row][col];
}

