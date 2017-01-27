#include "colorPalette.h"
#include<vector>
#include <random>

static std::mt19937 gen;

colorPalette::colorPalette()
{
    Target _tar;

    _tar.setPos(ngl::Vec3(-16.0f,9.0f,0.0f));
    _tar.m_tr = 0.9765625f;
    _tar.m_tg = 0.96875f;
    _tar.m_tb = 0.6640625f;
     m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(-16.0f,6.0f,0.0f));
    _tar.m_tr = 0.6640625f;
    _tar.m_tg = 0.9765625f;
    _tar.m_tb = 0.77734375f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(-16.0f,3.0f,0.0f));
    _tar.m_tr = 0.25f;
    _tar.m_tg = 0.8046875f;
    _tar.m_tb = 0.75f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(-16.0f,0.0f,0.0f));
    _tar.m_tr = 0.5f;
    _tar.m_tg = 0.99609375f;
    _tar.m_tb = 0.19921875f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(-16.0f,-3.0f,0.0f));
    _tar.m_tr = 0.09375f;
    _tar.m_tg = 0.6015625f;
    _tar.m_tb = 0.56640625f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(-16.0f,-6.0f,0.0f));
    _tar.m_tr = 0.125f;
    _tar.m_tg = 0.3359375f;
    _tar.m_tb = 0.49609375f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(-16.0f,-9.0f,0.0f));
    _tar.m_tr = 0.01953125f;
    _tar.m_tg = 0.18359375f;
    _tar.m_tb = 0.43359375f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(16.0f,9.0f,0.0f));
    _tar.m_tr = 0.3984375f;
    _tar.m_tg = 0.0f;
    _tar.m_tb = 0.19921875f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(16.0f,6.0f,0.0f));
    _tar.m_tr = 0.59765625f;
    _tar.m_tg = 0.0f;
    _tar.m_tb = 0.59765625f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(16.0f,3.0f,0.0f));
    _tar.m_tr = 0.99609375f;
    _tar.m_tg = 0.0f;
    _tar.m_tb = 0.49609375f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(16.0f,0.0f,0.0f));
    _tar.m_tr = 0.99609375f;
    _tar.m_tg = 0.59765625f;
    _tar.m_tb = 0.19921875f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(16.0f,-3.0f,0.0f));
    _tar.m_tr = 0.796875f;
    _tar.m_tg = 0.0;
    _tar.m_tb = 0.3984375f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(16.0f,-6.0f,0.0f));
    _tar.m_tr = 0.99609375f;
    _tar.m_tg = 0.3984375f;
    _tar.m_tb = 0.6953125f;
    m_targets.push_back(_tar);

    _tar.setPos(ngl::Vec3(16.0f,-9.0f,0.0f));
    _tar.m_tr = 0.99609375f;
    _tar.m_tg = 0.3984375f;
    _tar.m_tb = 0.99609375f;
    m_targets.push_back(_tar);
}

colorPalette::colorPalette(Target _tar, size_t num)
{
    for(size_t i=0; i<num; i++)
        m_targets.push_back(_tar);
}

//void colorPalette::allotBrush(int &_size)
//{
//    std::uniform_int_distribution<int> randSize(0.25,1.5);
//    _size = randSize(gen);

//    if(_size >= 1 && _size <= 2)
//    {
//        _size = 1.5;
//    }
//    if(_size > 2 && _size <= 3)
//    {
//        _size = 3;
//    }
//    if(_size > 3 && _size <= 5)
//    {
//        _size = 4.5;
//    }
//    if(_size > 5 && _size <= 7)
//    {
//        _size = 6;
//    }
//    if(_size > 7)
//    {
//        _size = 9;
//    }
//}

void colorPalette::changeColor(ngl::Vec3 & _pos, float &_r, float &_g, float &_b)
{
    //allotBrush(_size);

    for(size_t i=0; i<m_targets.size(); i++)
    {
        float d = _pos.dist(_pos,m_targets[i].getPos());
        if((d>0) && (d<m_targets[i].getBoundary()))
        {
             _r = m_targets[i].getR();
             _g = m_targets[i].getG();
             _b = m_targets[i].getB();
        }
    }
}

void colorPalette::addTarget(Target _tar, size_t num)
{
    for(size_t i=0; i<num; i++)
        m_targets.push_back(_tar);
}
