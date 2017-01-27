#ifndef PATH_H_
#define PATH_H_

#include <ngl/Vec3.h>
#include <vector>



class Path
{
public:
    std::vector<ngl::Vec3> m_points;
    Path()
    {
        addPoints();
    }

    void addPoints()
    {
        ngl::Vec3 start(0.0,-10,0.0);
        m_points.push_back(start);
        ngl::Vec3 point0(6.0,-8.0,0.0);
        m_points.push_back(point0);
        ngl::Vec3 point1(4.0,-2.0,0.0);
        m_points.push_back(point1);
        ngl::Vec3 point2(-2.0,-4,0.0);
        m_points.push_back(point2);
        ngl::Vec3 point3(7.0,-4.0,0.0);
        m_points.push_back(point3);
        ngl::Vec3 point4(4.0,4.0,0.0);
        m_points.push_back(point4);
        ngl::Vec3 point5(0.0,2.0,0.0);
        m_points.push_back(point5);
        ngl::Vec3 point6(9.0,2.0,0.0);
        m_points.push_back(point6);
        ngl::Vec3 point7(7.0,-10.0,0.0);
        m_points.push_back(point7);
        ngl::Vec3 point8(13.0,-8.0,0.0);
        m_points.push_back(point8);
        ngl::Vec3 point9(11.0,2.0,0.0);
        m_points.push_back(point9);
    }

};

#endif
