#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[])
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502:
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::initializeGL() {
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)

  camera1aPersona = invisibilitatRick = false;
  angleYVideoCamera = float(M_PI) / 4.0f;
  angleMorty = 0.0;
  posMorty = glm::vec3(1.0, 0.0, 0.0);

  carregaShaders();
  creaBuffersModels();
  creaBuffersTerra();
  iniEscena();
  iniCamera();
}

void MyGLWidget::iniCamera() {
  filtre = glm::vec3(1.0, 1.0, 1.0);
  glUniform3fv(filtreLoc, 1, &filtre[0]);

  pmin = glm::vec3(-4.0, 0.0, -4.0);
  pmax = glm::vec3(4.0, 3.0, 4.0);
  vrp = glm::vec3((pmin.x + pmax.x) / 2.0f, (pmin.y + pmax. y) / 2.0f, (pmin.z + pmax.z) / 2.0f);
  fov = fov_nou = float(M_PI) / 4.0f;
  ra = 1.0;
  znear = distance(pmin, vrp);
  zfar = 3 * znear;
  angleX = 0.0;
  angleY = float(M_PI) / -4.0f;
}

void MyGLWidget::iniCamera1aPersona() {
  filtre = glm::vec3(0.0, 1.0, 0.0);
  glUniform3fv(filtreLoc, 1, &filtre[0]);

  obs = glm::vec3(-4.0, 3.0, -4.0);
  vrp1aPersona = glm::vec3(-4.0 + sqrt(32) * sin(angleYVideoCamera), 0.0, -4.0 + sqrt(32) * cos(angleYVideoCamera));
  up = glm::vec3(0.0, 1.0, 0.0);
  znear1aPersona = 0.3; //Amb un zNear de 0.25 es veu la lent de la càmera
  zfar1aPersona = 20;
  fov1aPersona = float(M_PI) / 3.0f;
  ra1aPersona = 1.0;
  viewTransform1aPersona();
  projectTransform1aPersona();
}

void MyGLWidget::viewTransform() {
  glm::mat4 VM(1.0f);
  VM = glm::translate(VM, glm::vec3(0.0, 0.0, -2.0f * distance(pmin, vrp)));
  VM = glm::rotate(VM, -angleY, glm::vec3(1.0, 0.0, 0.0));
  VM = glm::rotate(VM, angleX, glm::vec3(0.0, 1.0, 0.0));
  VM = glm::translate(VM, glm::vec3(-vrp.x, -vrp.y, -vrp.z));
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &VM[0][0]);
}

void MyGLWidget::viewTransform1aPersona() {
  glm::mat4 VM(1.0f);
  VM = glm::lookAt(obs, vrp1aPersona, up);
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &VM[0][0]);
}

void MyGLWidget::projectTransform() {
  //perspective(FOV, ra, zN, zF);
  glm::mat4 PM(1.0f);
  if (ra < 1.0) PM = glm::perspective(fov_nou, ra, znear, zfar);
  else PM = glm::perspective(fov, ra, znear, zfar);
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &PM[0][0]);
}

void MyGLWidget::projectTransform1aPersona() {
  glm::mat4 PM(1.0f);
  PM = glm::perspective(fov1aPersona, ra1aPersona, znear1aPersona, zfar1aPersona);
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &PM[0][0]);
}

void MyGLWidget::RickTransform() {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, glm::vec3(-2.0, 0.0, -2.0));
  TG = glm::rotate(TG, float(M_PI), glm::vec3(0.0, 1.0, 0.0));
  TG = glm::scale(TG, glm::vec3(escalaModels[RICK]));
  TG = glm::translate(TG, -centreBaseModels[RICK]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::MortyTransform() {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, posMorty);
  TG = glm::rotate(TG, angleMorty * float(M_PI) / 180.0f, glm::vec3(0.0, 1.0, 0.0));
  TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
  TG = glm::translate(TG, -centreBaseModels[MORTY]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::VideoCameraTransform() {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, glm::vec3(-4.0, 3.0, -4.0));
  TG = glm::rotate(TG, angleYVideoCamera, glm::vec3(0.0, 1.0, 0.0));
  TG = glm::rotate(TG, float(M_PI) / 4.0f, glm::vec3(1.0, 0.0, 0.0));
  TG = glm::scale(TG, glm::vec3(escalaModels[VIDEOCAMERA]));
  TG = glm::translate(TG, -centreBaseModels[VIDEOCAMERA]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::paintGL() {
  // descomentar per canviar paràmetres
  //glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  filtre = glm::vec3(1.0, 1.0, 1.0);
  glUniform3fv(filtreLoc, 1, &filtre[0]);
  viewTransform();
  projectTransform();

  // Rick
  glUniform1i(invisibilitatLoc, invisibilitatRick);
  glBindVertexArray (VAO_models[RICK]);
  RickTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[RICK].faces().size()*3);
  glUniform1i(invisibilitatLoc, false);

  // Morty
  glBindVertexArray (VAO_models[MORTY]);
  MortyTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);

  // VideoCamera
  glBindVertexArray (VAO_models[VIDEOCAMERA]);
  VideoCameraTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[VIDEOCAMERA].faces().size()*3);

  // Terra
  glBindVertexArray (VAO_Terra);
  identTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  // Paret
  ParetTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  if (camera1aPersona) {  //FALTA EL MOVIMENT AMB L'ANGLE DE LA CÀMERA!
    glViewport (ample - ample / 4, alt - alt / 4, ample / 4, alt / 4);
    iniCamera1aPersona();

    glUniform1i(invisibilitatLoc, invisibilitatRick);
    glBindVertexArray(VAO_models[RICK]);
    RickTransform();
    glDrawArrays(GL_TRIANGLES, 0, models[RICK].faces().size()*3);
    glUniform1i(invisibilitatLoc, false);

    glBindVertexArray(VAO_models[MORTY]);
    MortyTransform();
    glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);

    glBindVertexArray(VAO_models[VIDEOCAMERA]);
    VideoCameraTransform();
    glDrawArrays(GL_TRIANGLES, 0, models[VIDEOCAMERA].faces().size()*3);

    glBindVertexArray(VAO_Terra);
    identTransform();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //Paret
    ParetTransform();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }

  glBindVertexArray (0);
}

void MyGLWidget::resizeGL(int w, int h) {
  // Aquest codi és necessari únicament per a MACs amb pantalla retina.
  #ifdef __APPLE__
    GLint vp[4];
    glGetIntegerv (GL_VIEWPORT, vp);
    ample = vp[2];
    alt = vp[3];
  #else
    ample = w;
    alt = h;
  #endif

  ra = float(ample)/float(alt);
  fov_nou = 2 * atan(tan(fov / 2) / ra);
  factorAngleY = M_PI / ample;
  factorAngleX = M_PI / alt;
  projectTransform();
}

void MyGLWidget::mousePressEvent(QMouseEvent *e)
{
  makeCurrent();
  xClick = e->x();
  yClick = e->y();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e) {
  makeCurrent();
  angleX += (e->x() - xClick) * factorAngleX;
  angleY -= (e->y() - yClick) * factorAngleY;
  xClick = e->x();
  yClick = e->y();
  viewTransform();
  update();
}

void MyGLWidget::keyPressEvent(QKeyEvent *e) {
  makeCurrent();
  switch (e->key()) {
    case Qt::Key_Up: {
      if (angleMorty > 0.0 and angleMorty < 180.0) posMorty += glm::vec3(0.1, 0.0, 0.0);  //semicercle est
      else if (angleMorty > 180.0 and angleMorty < 360.0) posMorty += glm::vec3(-0.1, 0.0, 0.0);  //semicercle oest
      if (angleMorty > 270.0 or angleMorty < 90.0) posMorty += glm::vec3(0.0, 0.0, 0.1);  //semicercle sud
      else if (angleMorty > 90.0 and angleMorty < 270.0) posMorty += glm::vec3(0.0, 0.0, -0.1); //semicercle nord
      break;
    }
    case Qt::Key_Down: {
      if (angleMorty > 0.0 and angleMorty < 180.0) posMorty -= glm::vec3(0.1, 0.0, 0.0);  //semicercle est
      else if (angleMorty > 180.0 and angleMorty < 360.0) posMorty -= glm::vec3(-0.1, 0.0, 0.0);  //semicercle oest
      if (angleMorty > 270.0 or angleMorty < 90.0) posMorty -= glm::vec3(0.0, 0.0, 0.1);  //semicercle sud
      else if (angleMorty > 90.0 and angleMorty < 270.0) posMorty -= glm::vec3(0.0, 0.0, -0.1); //semicercle nord
      break;
    }
    case Qt::Key_Left: {
      angleMorty += 45.0;
      if (angleMorty == 360.0) angleMorty = 0.0;
      break;
    }
    case Qt::Key_Right: {
      if (angleMorty == 0.0) angleMorty = 360.0;
      angleMorty -= 45.0;
      break;
    }
    case Qt::Key_Q: {
      if (angleYVideoCamera < float(M_PI) / 2.0f) angleYVideoCamera += float(M_PI) / 180.f;
      break;
    }
    case Qt::Key_E: {
      if (angleYVideoCamera > 0.0) angleYVideoCamera -= float(M_PI) / 180.0f;
      break;
    }
    case Qt::Key_C: {
      camera1aPersona = not camera1aPersona;
      break;
    }
    case Qt::Key_G: {
      invisibilitatRick = not invisibilitatRick;
      break;
    }
    case Qt::Key_R: {
      initializeGL();
      break;
    }
    default: e->ignore(); break;
  }
  update();
}

void MyGLWidget::carregaShaders() {
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Identificador per als  atributs
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  colorLoc = glGetAttribLocation (program->programId(), "color");

  // Identificadors dels uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc  = glGetUniformLocation (program->programId(), "Proj");
  viewLoc  = glGetUniformLocation (program->programId(), "View");
  filtreLoc = glGetUniformLocation(program->programId(), "Filtre");
  invisibilitatLoc = glGetUniformLocation(program->programId(), "InvisibilitatRick");
}
