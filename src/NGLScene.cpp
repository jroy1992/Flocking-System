#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/ShaderLib.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
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

  // create a vao as a series of GL_TRIANGLES
  m_vao.reset(ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_TRIANGLES) );
  m_vao->bind();

  // in this case we are going to set our data as the vertices above
  m_vao->setData(ngl::SimpleVAO::VertexData(verts.size()*sizeof(ngl::Vec3),verts[0].m_x));
  // now we set the attribute pointer to be 0 (as this matches vertIn in our shader)

  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);

  // now we set the attribute pointer to be 2 (as this matches normal in our shader)
  // as we cast to ngl::Real for offset use 12 * 3 (as in x,y,z is 3 floats)
  // m_vao->setVertexAttributePointer(2,3,GL_FLOAT,0,12*3);
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
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			   // White Background
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
}


void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glViewport(0,0,m_win.width,m_win.height);
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  ngl::Mat4 MVP;
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

      shader->setShaderParamFromMat4("MVP",MVP);

      m_vao->draw();
      m_trans.setScale(0.25,0.5,0.25);
      m_trans.addRotation(f.m_boids[i].m_velocity.m_x,f.m_boids[i].m_velocity.m_y,0.0);
  }

  m_vao->unbind();

  ngl::Mat4 MVPTar;
  ngl::Mat4 MVTar;
  ngl::Mat4 MTar;
  ngl::Vec3 m_posTar;
  ngl::VAOPrimitives::instance()->createSphere("sphereTAR",1.2f,20);

  for(size_t i=0; i<cP.m_targets.size();i++)
  {
      shader->use("nglColourShader");
      shader->setUniform("Colour",cP.m_targets[i].m_tr,cP.m_targets[i].m_tg,cP.m_targets[i].m_tb,1.0f);
      //get the position of the ith boid
      m_posTar = cP.m_targets[i].getPos();
      // set the tranfrom based on the position of the boid
      m_transTar.setPosition(m_posTar);
      // get the corr matrix
      MTar = m_transTar.getMatrix();
      MVTar = MTar*m_cam.getViewMatrix();
      MVPTar = MVTar*m_cam.getProjectionMatrix();
      shader->setShaderParamFromMat4("MVP",MVPTar);
      ngl::VAOPrimitives::instance()->draw("sphereTAR");
  }

  if(f.m_choice == 's')         // activate separation
      f.runflock('s');
  else if(f.m_choice == 'a')    // activate alignment
      f.runflock('a');
  else if(f.m_choice == 'c')    // activate cohesion
      f.runflock('c');
  else if(f.m_choice == 'f')    // activate flocking
      f.runflock('f');

  // would see the path following with clarity when choosen as the first option.
  else if(f.m_choice == 'p')    // activate path following.
      f.runflock('p');

  /*  Preferable to choose both the flowfields after all other behaviors have been worked with
   * as it might slow down the program.
   * These both for the moment have been commented out in the Boid flock().
  */
  else if(f.m_choice == 'l')    // activate random flow field following. Prefer to choose both the flowfields after all other behaviors
      f.runflock('l');
  else if(f.m_choice == 'm')    // acticate cos sin wave flow field following
      f.runflock('m');

  else if(f.m_choice == 'q')    // clear the screen
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    case Qt::Key_S:
        f.m_choice = 's';
        break;
    case Qt::Key_A:
        f.m_choice = 'a';
        break;
    case Qt::Key_C:
        f.m_choice = 'c';
        break;
    case Qt::Key_F:
        f.m_choice = 'f';
        break;
    case Qt::Key_P:
        f.m_choice = 'p';
        break;
    case Qt::Key_L:
        f.m_choice = 'l';
        break;
    case Qt::Key_M:
        f.m_choice = 'm';
        break;
    case Qt::Key_Q:
        f.m_choice = 'q';
        break;
    default : break;
    }
}

