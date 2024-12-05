// MyGLWidget.cpp
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

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_A: {
      angleYMorty += 45.0f;
      if (angleYMorty >= 360.0f) angleYMorty -= 360.0f;
    break;
	}
  case Qt::Key_D: {
      angleYFantasmes -= 45.0f;
      if (angleYFantasmes < 0.0f) angleYFantasmes += 360.0f;
    break;
	}
  case Qt::Key_E: {
      if (estatFocusEscena) colorFocusEscena = glm::vec3(0, 0, 0);
      else colorFocusEscena = glm::vec3(0.4, 0.4, 0.4);
      estatFocusEscena = not estatFocusEscena;
      glUniform3fv(colorFocusEscenaLoc, 1, &colorFocusEscena[0]);
    break;
	}
  case Qt::Key_B: {
    canviaFocusColors();
    break;
	}	
  case Qt::Key_R: {
      rotaDiscoBall();
    break;
	}
  case Qt::Key_S: {
      if (not running) timer.start(100);
      else timer.stop();
      running = not running;
    break;
	}	
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::rotaDiscoBall() {
  angleYDiscoBall += 5.0f;
  if (angleYDiscoBall >= 360.0f) angleYDiscoBall -= 360.0f;

  calculaPosicionsFocusColors();
}

void MyGLWidget::calculaPosicionsFocusColors() {
  glm::mat4 TG;
  TG = glm::translate(glm::mat4(1.f), glm::vec3(5,5,5));
  TG = glm::rotate(TG, angleYDiscoBall * float(M_PI) / 180.0f, glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(escalaDiscoBall, escalaDiscoBall, escalaDiscoBall));
  TG = glm::translate(TG, -centreBaseDiscoBall);

  arrayPosicionsFocus[0] = glm::vec3(TG * glm::vec4(1.2, 0.0, 0.0, 1.0));
  arrayPosicionsFocus[1] = glm::vec3(TG * glm::vec4(-1.2, 0.0, 0.0, 1.0));
  arrayPosicionsFocus[2] = glm::vec3(TG * glm::vec4(0.0, 0.0, 1.2, 1.0));
  arrayPosicionsFocus[3] = glm::vec3(TG * glm::vec4(0.0, 0.0, -1.2, 1.0));

  for (int i = 0; i < 4; ++i) glUniform3fv(arrayPosicionsFocusLoc, 4, &arrayPosicionsFocus[0][0]);
}

void MyGLWidget::canviaFocusColors() {
  if (estatFocusColors == 0) arrayColorsFocus[0] = glm::vec3(0.0, 0.0, 0.0);
    else if (estatFocusColors == 1) arrayColorsFocus[1] = glm::vec3(0.0, 0.0, 0.0);
    else if (estatFocusColors == 2) arrayColorsFocus[2] = glm::vec3(0.0, 0.0, 0.0);
    else if (estatFocusColors == 3) arrayColorsFocus[3] = glm::vec3(0.0, 0.0, 0.0);
    else if (estatFocusColors == 4) arrayColorsFocus[0] = glm::vec3(0.4, 0.0, 0.0);
    else if (estatFocusColors == 5) arrayColorsFocus[1] = glm::vec3(0.0, 0.4, 0.0);
    else if (estatFocusColors == 6) arrayColorsFocus[2] = glm::vec3(0.0, 0.0, 0.4);
    else arrayColorsFocus[3] = glm::vec3(0.4, 0.4, 0.0);
    glUniform3fv(arrayColorsFocusLoc, 4, &arrayColorsFocus[0][0]);
    ++estatFocusColors;
    if (estatFocusColors == 8) estatFocusColors = 0;
}

void MyGLWidget::setUpTimer() {
  connect(&timer, SIGNAL(timeout()),this, SLOT(festa()));
}

void MyGLWidget::festa() {
  makeCurrent();
  canviaFocusColors();
  rotaDiscoBall();
  update();
}

void MyGLWidget::modelTransformDiscoBall() {
  glm::mat4 TG;
  TG = glm::translate(glm::mat4(1.f), glm::vec3(5,5,5));
  TG = glm::rotate(TG, angleYDiscoBall * float(M_PI) / 180.0f, glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(escalaDiscoBall, escalaDiscoBall, escalaDiscoBall));
  TG = glm::translate(TG, -centreBaseDiscoBall);
  
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformFantasma(float posX) {
  glm::mat4 TG;
  TG = glm::translate(glm::mat4(1.0f), glm::vec3(posX,0.5,5));
  TG = glm::rotate(TG, angleYFantasmes * float(M_PI) / 180.0f, glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(escalaFantasma, escalaFantasma, escalaFantasma));
  TG = glm::translate(TG, -centreBaseFantasma);
  
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformMorty() {
  glm::mat4 TG;
  TG = glm::translate(glm::mat4(1.f), glm::vec3(5,0,5));
  TG = glm::rotate(TG, angleYMorty * float(M_PI) / 180.0f, glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(escalaMorty, escalaMorty, escalaMorty));
  TG = glm::translate(TG, -centreBaseMorty);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::definirFocusLlum() {
  colorFocusEscena = glm::vec3(0.4, 0.4, 0.4);
  posicioFocusEscena = glm::vec3(5.0, 10.0, 5.0);
  glUniform3fv(colorFocusEscenaLoc, 1, &colorFocusEscena[0]);
  glUniform3fv(posicioFocusEscenaLoc, 1, &posicioFocusEscena[0]);

  arrayColorsFocus[0] = glm::vec3(0.4, 0.0, 0.0);
  arrayColorsFocus[1] = glm::vec3(0.0, 0.4, 0.0);
  arrayColorsFocus[2] = glm::vec3(0.0, 0.0, 0.4);
  arrayColorsFocus[3] = glm::vec3(0.4, 0.4, 0.0);

  glUniform3fv(arrayColorsFocusLoc, 4, &arrayColorsFocus[0][0]);

  calculaPosicionsFocusColors();
}

void MyGLWidget::initializeGL() {
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  setUpTimer();
  
  carregaShaders();
  
  creaBuffersMorty();
  creaBuffersFantasma();
  creaBuffersDiscoBall();
  creaBuffersTerraIParets();

  iniEscena();
  iniCamera();

  definirFocusLlum();
}

void MyGLWidget::paintGL() {
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  // glViewport (0, 0, ample, alt);
  
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // DISCO BALL
  glBindVertexArray (VAO_DiscoBall);
  modelTransformDiscoBall ();
  glDrawArrays(GL_TRIANGLES, 0, discoBall.faces().size()*3);

  // TERRA
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLES, 0, 30);
  
  // MORTY
  glBindVertexArray (VAO_Morty);
  modelTransformMorty ();
  glDrawArrays(GL_TRIANGLES, 0, morty.faces().size()*3);
  
  // FANTASMA1
  glBindVertexArray (VAO_Fantasma);
  modelTransformFantasma (1.0f);
  glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size()*3);

  //FANTASMA2
  glBindVertexArray (VAO_Fantasma);
  modelTransformFantasma(9.0f);
  glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size()*3);
  
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders() {
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("./shaders/basicLlumShader.frag");
  vs.compileSourceFile("./shaders/basicLlumShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “normal” del vertex shader
  normalLoc = glGetAttribLocation (program->programId(), "normal");
  // Obtenim identificador per a l'atribut “matamb” del vertex shader
  matambLoc = glGetAttribLocation (program->programId(), "matamb");
  // Obtenim identificador per a l'atribut “matdiff” del vertex shader
  matdiffLoc = glGetAttribLocation (program->programId(), "matdiff");
  // Obtenim identificador per a l'atribut “matspec” del vertex shader
  matspecLoc = glGetAttribLocation (program->programId(), "matspec");
  // Obtenim identificador per a l'atribut “matshin” del vertex shader
  matshinLoc = glGetAttribLocation (program->programId(), "matshin");

  // Demanem identificadors per als uniforms del vertex shader
  transLoc = glGetUniformLocation (program->programId(), "TG");
  projLoc = glGetUniformLocation (program->programId(), "Proj");
  viewLoc = glGetUniformLocation (program->programId(), "View");

  //Informació dels focus de llum
  colorFocusEscenaLoc = glGetUniformLocation (program->programId(), "colorFocusEscena");
  posicioFocusEscenaLoc = glGetUniformLocation (program->programId(), "posicioFocusEscena");
  arrayColorsFocusLoc = glGetUniformLocation (program->programId(), "arrayColorsFocus");
  arrayPosicionsFocusLoc = glGetUniformLocation (program->programId(), "arrayPosicionsFocus");
}