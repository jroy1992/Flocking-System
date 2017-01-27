#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/ShaderLib.h>
#include <ngl/VAOFactory.h>
#include<ngl/SimpleVAO.h>
#include <ngl/NGLInit.h>
#include <iostream>

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Blank NGL");
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
  m_vao->removeVAO();
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_cam.setShape( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}



//void NGLScene::buildMesh(ngl::Real _w, ngl::Real _d, size_t _stepsW, size_t _stepsD)
//{
//  std::vector<ngl::Vec3> data;

//  // plane origin =0,0,0
//  // extents -W / 2 -> +W / 2
//  // -D /2 -> +D/2
//  ngl::Real w2=_w / 0.5f;
//  ngl::Real d2=_d / 0.5f;
//  // now for the steps in w and d
//  ngl::Real wStep=_w/_stepsW;
//  ngl::Real dStep=_d/_stepsD;

//  ngl::Vec3 vert;
//  vert.m_z=0.0f;

//  for(ngl::Real d=-d2; d<d2; d+=dStep)
//  {
//    for(ngl::Real w=-w2; w<w2; w+=wStep)
//    {
//      // first triangle
//      vert.m_x=w; vert.m_y=d+dStep; // V1
//      data.push_back(vert);
//      vert.m_x=w+wStep; vert.m_y=d+dStep; // V2
//      data.push_back(vert);
//      vert.m_x=w; vert.m_y=d; // V3
//      data.push_back(vert);

//      vert.m_x=w+wStep; vert.m_y=d+dStep;
//      data.push_back(vert);
//      vert.m_x=w+wStep; vert.m_y=d;
//      data.push_back(vert);
//      vert.m_x=w; vert.m_y=d;
//      data.push_back(vert);
//    }
//  }

//  m_nVerts=data.size();

//  m_vaoMesh.reset(ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS));
//  m_vaoMesh->bind();
//  m_vaoMesh->setData(ngl::AbstractVAO::VertexData(data.size()*sizeof(ngl::Vec3),
//                                              data[0].m_x));
//  m_vaoMesh->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
//  m_vaoMesh->setNumIndices(data.size());
//  m_vaoMesh->unbind();
//}


//void NGLScene::buildImage()
//{
//    //image.setBackground(1.0f,1.0f,1.0f);
//    m_vaoImage.reset(ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_LINE));
//    m_vaoImage->bind();
//    m_vaoImage->setData(ngl::AbstractVAO::VertexData(image.m_height*image.m_width*sizeof(float),
//                                                image.m_data[0]));
//    m_vaoImage->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
//    m_vaoImage->setNumIndices(image.m_height*image.m_width);
//    m_vaoImage->unbind();
//}


void NGLScene::buildVAO()
{
  std::vector<ngl::Vec3> verts=
  {
    ngl::Vec3(0,1,1),
    ngl::Vec3(0,0,-1),
    ngl::Vec3(-0.5,0,1),
    ngl::Vec3(0,1,1),
    ngl::Vec3(0,0,-1),
    ngl::Vec3(0.5,0,1),
    ngl::Vec3(0,1,1),
    ngl::Vec3(0,0,1.5),
    ngl::Vec3(-0.5,0,1),
    ngl::Vec3(0,1,1),
    ngl::Vec3(0,0,1.5),
    ngl::Vec3(0.5,0,1)

  };
  std::cout<<"Initial "<<verts.size()<<'\n';
  ngl::Vec3 n=ngl::calcNormal(verts[2],verts[1],verts[0]);
  verts.push_back(n);
  verts.push_back(n);
  verts.push_back(n);
  n=ngl::calcNormal(verts[3],verts[4],verts[5]);
  verts.push_back(n);
  verts.push_back(n);
  verts.push_back(n);

  n=ngl::calcNormal(verts[6],verts[7],verts[8]);
  verts.push_back(n);
  verts.push_back(n);
  verts.push_back(n);

  n=ngl::calcNormal(verts[11],verts[10],verts[9]);
  verts.push_back(n);
  verts.push_back(n);
  verts.push_back(n);


//  for(int i=0; i<12*3; ++i)
//    {
//      verts[i]*=0.1;
//    }

  std::cout<<"sizeof(verts) "<<sizeof(verts)<<" sizeof(ngl::Vec3) "<<sizeof(ngl::Vec3)<<"\n";
  // create a vao as a series of GL_TRIANGLES
  m_vao.reset(ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_TRIANGLES) );
  m_vao->bind();

  // in this case we are going to set our data as the vertices above
  m_vao->setData(ngl::SimpleVAO::VertexData(verts.size()*sizeof(ngl::Vec3),verts[0].m_x));
  // now we set the attribute pointer to be 0 (as this matches vertIn in our shader)

  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);

    // now we set the attribute pointer to be 2 (as this matches normal in our shader)
  // as we cast to ngl::Real for offset use 12 * 3 (as in x,y,z is 3 floats)
  //m_vao->setVertexAttributePointer(2,3,GL_FLOAT,0,12*3);
  // divide by 2 as we have both verts and normals
  m_vao->setNumIndices(verts.size()/2);

 // now unbind
  m_vao->unbind();
}


void NGLScene::initializeGL()
{

  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  // Now we will create a basic Camera from the graphics library
  // This is a static camera so it only needs to be set once
  // First create Values for the camera position
  ngl::Vec3 from(0,0,30);
  ngl::Vec3 to(0,0,0);
  ngl::Vec3 up(0,1,0);

  m_cam.set(from,to,up);
  // set the shape using FOV 45 Aspect Ratio based on Width and Height
  // The final two are near and far clipping planes of 0.5 and 10
  m_cam.setShape(60,720.0f/576.0f,0.5f,150);

//  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
//  shader->use("nglColourShader");
//  shader->setUniform("Colour",0.0f,1.0f,1.0f,1.0f);
  //buildMesh(60.0f,60.0f,40,40 );
  //buildImage();
  //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

  startTimer(500);
}


void NGLScene::paintGL()
{


  // clear the screen and depth buffer
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
//  shader->use("nglColourShader");
//  shader->setUniform("Colour",0.0f,0.5f,1.0f,1.0f);

//  for (Boid &b : f.m_boids)
//  {
//      float x = (b.m_position.m_x + 18)/36*1024;
//      float y = (b.m_position.m_y + 12)/24*720;
//      image.setPixel(x,y,b.m_r,b.m_g,b.m_b);
//      std::cout<<"x: "<<x<<"y: "<<y<<'\n';
//      //x *= image
//  }
  //for loop
    //convert boid[x].position.x to 0 -> image._width
    //convert boid[x].position.y to 0 -> image._height
    //image.setPixel(boid[x].x, boid[x].y,R,G,B
//  shader->use("nglColourShader");
//  shader->setUniform("Colour",1.0f,1.0f,1.0f,1.0f);
//  //buildMesh(60.0f,60.0f,40,40 );
//  buildImage();
//  m_vaoImage->bind();
//  m_vaoImage->draw();
//  image.setBackground(1.0f,1.0f,1.0f);
//  m_vaoImage->unbind();





//  m_vaoMesh->bind();
//  m_vaoMesh->draw();
//  m_vaoMesh->unbind();

//  ngl::Mat4 MVPImage;
//  ngl::Mat3 normalMatrixImage;
//  ngl::Mat4 MVImage;
//  ngl::Mat4 MImage;
//  ngl::Vec3 m_posImage;
//  MImage = m_transImage.getMatrix();
//  MVImage = MImage*m_cam.getViewMatrix();
//  MVPImage = MVImage*m_cam.getProjectionMatrix();
//  shader->setShaderParamFromMat4("MVP",MVPImage);

//  for(size_t i=0; i<image.m_width; i++)
//  {
//      for(size_t j=0; j<image.m_height; j++)
//      {
//          shader->use("nglColourShader");
//          shader->setUniform("Colour",1.0f,1.0f,1.0f,1.0f);
//          m_posImage = ;
//      }
//  }


  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 MV;
  ngl::Mat4 M;
  ngl::Vec3 m_pos;
  ngl::VAOPrimitives::instance()->createSphere("sphere",0.05f,10);

  buildVAO();
  m_vao->bind();

  for(size_t i=0; i<f.m_boids.size();i++)
  {

      cP.changeColor(f.m_boids[i].m_position,f.m_boids[i].m_r,f.m_boids[i].m_g,f.m_boids[i].m_b);

      shader->use("nglColourShader");
      shader->setUniform("Colour",f.m_boids[i].m_r,f.m_boids[i].m_g,f.m_boids[i].m_b,1.0f);

      //get the position of the ith boid
      m_pos = f.m_boids[i].m_position;
      // set the tranfrom based on the position of the boid
      m_trans.setPosition(m_pos);
      // get the corr matrix
      M = m_trans.getMatrix();
      MV = M*m_cam.getViewMatrix();
      MVP = MV*m_cam.getProjectionMatrix();
    //      V // get cam view
    //      P // get cam proj;
    //              MV;
    //      MVP;
      //normalMatrix=MV;
      //normalMatrix.inverse();
      //shader->setShaderParamFromMat4("MV",MV);
      shader->setShaderParamFromMat4("MVP",MVP);
      //shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
      //ngl::VAOPrimitives::instance()->draw("sphere");
      m_vao->draw();
      m_trans.setScale(0.25,0.5,0.25);
      m_trans.addRotation(f.m_boids[i].m_velocity.m_x,f.m_boids[i].m_velocity.m_y,0.0);
  }

  m_vao->unbind();

  ngl::Mat4 MVPTar;
  ngl::Mat3 normalMatrixTar;
  ngl::Mat4 MVTar;
  ngl::Mat4 MTar;
  ngl::Vec3 m_posTar;
  ngl::VAOPrimitives::instance()->createSphere("sphereTAR",1.2f,20);
  //shader->use("nglColourShader");

  for(size_t i=0; i<cP.m_targets.size();i++)
  {
      shader->use("nglColourShader");
      shader->setUniform("Colour",cP.m_targets[i].m_tr,cP.m_targets[i].m_tg,cP.m_targets[i].m_tb,1.0f);
      //std::cout<<"R: "<<cP.m_targets[i].m_tr<<"G: "<<cP.m_targets[i].m_tg<<"B: "<<cP.m_targets[i].m_tb;
      //get the position of the ith boid
      m_posTar = cP.m_targets[i].getPos();
      // set the tranfrom based on the position of the boid
      m_transTar.setPosition(m_posTar);
      // get the corr matrix
      MTar = m_transTar.getMatrix();
      MVTar = MTar*m_cam.getViewMatrix();
      MVPTar = MVTar*m_cam.getProjectionMatrix();
//      V // get cam view
//      P // get cam proj;
//              MV;
//      MVP;
      //normalMatrixTar=MVTar;
      //normalMatrixTar.inverse();
      //shader->setShaderParamFromMat4("MV",MVTar);
      shader->setShaderParamFromMat4("MVP",MVPTar);
      //shader->setShaderParamFromMat3("normalMatrix",normalMatrixTar);
      //ngl::VAOPrimitives::instance()->createSphere("sphereTAR",1.2f,10);
      ngl::VAOPrimitives::instance()->draw("sphereTAR");
      //m_vao->draw();
  }

//  m_vao->draw();
//  m_vao->bind();
//  m_vao->unbind();

  f.runflock();
  update();
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());
      break;
  case Qt::Key_S:
      image.saveImage();
      break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    //update();
}

void NGLScene::timerEvent(QTimerEvent *)
{
//    static float time;
//    time += 0.1f;
//    m_absVAO->bind();

//    ngl::Vec3 *ptr =static_cast<ngl::Vec3 *>
//         ( glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE) );



//    glUnmapBuffer(GL_ARRAY_BUFFER);
//    m_absVAO->unbind();
//    std::vector<ngl::Vec3> verts;
//    for(size_t i = 0; i<f.m_boids.size(); i++)
//    {
//        verts.push_back(f.m_boids[i].m_position);
//    }
//    m_vao->bind();

//    m_vao->setData(ngl::SimpleVAO::VertexData(f.m_boids.size()*sizeof(ngl::Vec3),verts[0].m_x));

//    m_vao->unbind();

//    glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
//        glBufferData(GL_ARRAY_BUFFER, maxParticles * 3 * sizeof(GLfloat),NULL,GL_DYNAMIC_DRAW);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, particleCount * sizeof(GLfloat) *3, particle_position_data);
    //f.runflock();
    //update();
}
