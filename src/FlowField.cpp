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


void FlowField::init(int _ffchoice)
{
    // flow field setup for random orientation
    if(_ffchoice == 0)
    {
        std::uniform_real_distribution<> randTheta(-M_PI,M_PI);

        for (int i = 0; i < rows; i++)
        {
            std::vector<ngl::Vec3> ro;
            for (int j = 0; j < columns; j++)
            {
                ro.push_back(ngl::Vec3(randTheta(gen),randTheta(gen),0.0f));
            }
            m_random.push_back(ro);
        }
    }

    // flow field setup for cos sin wave orientation
    else if(_ffchoice == 1)
    {
        for(int i=0; i<rows; i++)
        {
            std::vector<ngl::Vec3> row;
            for(int j=0; j<columns; j++)
            {
                float theta = M_PI/4;
                row.push_back(ngl::Vec3(cos(theta), sin(theta)*2,0.0f));
            }
            m_csWave.push_back(row);
        }
    }
}

// The following section is from :-
/// Daniel Shiffman (2016). Nature of Code Examples [online]. [Accessed 2016]
/// Available from: "https://github.com/shiffman/The-Nature-of-Code-Examples/tree/master/chp06_agents/NOC_6_09_Flocking".
ngl::Vec3 FlowField::lookup(ngl::Vec3 _position, int _ffchoice)
{
    int col = constrain(_position.m_x/resolution, 0, columns - 1);
    int row = constrain(_position.m_y/resolution, 0, rows - 1);

    if(_ffchoice == 0)
        return m_random[row][col];
    else
        return m_csWave[row][col];
}

///End Citation
