#ifndef IMAGE_H_
#define IMAGE_H_
//#if defined (__linux__) || defined (WIN32)
//  #include <GL/gl.h>
//  #include <GL/glu.h>
//#endif
//#ifdef __APPLE__
//  #include <OpenGL/gl.h>
//  #include <OpenGL/glu.h>
//#endif
#include <memory>
#include <string>
#include <Magick++.h>

class Image
{
  public :

    explicit Image(size_t _width, size_t _height);
    // make sure we can't copy this class as it could be expensive.
    //Image(const Image &)=delete;
    //Image & operator=(const Image &)=delete;
    void setPixel(size_t _x, size_t _y, float _r,
                                        float _g,
                                        float _b, float _a=1.0f);
    void setBackground(float _r,
                       float _g,
                       float _b);
    void saveImage();
    float* get() {return m_data.get();}
    size_t m_width=0;
    size_t m_height=0;
    float m_r = 1.0f;
    float m_g = 1.0f;
    float m_b = 1.0f;
  //private :

   std::unique_ptr< float []> m_data;
//   size_t m_width=0;
//   size_t m_height=0;
};


#endif
