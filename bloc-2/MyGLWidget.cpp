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

void MyGLWidget::modelTransformModel() {
  glm::mat4 TG(1.0f);
  float minX, minY, minZ, maxX, maxY, maxZ;
  minX = minY = minZ = maxX = maxY = maxZ = 0.0;
  for (int i = 0; i < m.vertices().size(); i += 3) {
    if (m.vertices()[i] < minX) minX = m.vertices()[i];
    else if (m.vertices()[i] > maxX) maxX = m.vertices()[i];
    if (m.vertices()[i + 1] < minY) minY = m.vertices()[i + 1];
    else if (m.vertices()[i + 1] > maxY) maxY = m.vertices()[i + 1];
    if (m.vertices()[i + 2] < minZ) minZ = m.vertices()[i + 2];
    else if (m.vertices()[i + 2] > maxZ) maxZ = m.vertices()[i + 2];
  }
  //El model s'ha de moure per tenir el terra a la base -> amb alçada 4 s'hauria de moure +2 -> +0.5
  TG = glm::translate(TG, glm::vec3(0.0, 0.5, 0.0));
  //El model ha de fer alçada 4 i té alçada maxY - minY -> escalat = 4 / (maxY - minY)
  TG = glm::scale(TG, glm::vec3(4.0f / (maxY - minY), 4.0f / (maxY - minY), 4.0f / (maxY - minY)));
  //Movem el centre del model al centre de coordenades
  TG = glm::translate(TG, glm::vec3(-(minX + maxX) / 2.0f, -(minY + maxY) / 2.0f, -(minZ + maxZ) / 2.0f));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformTerra() {
  glm::mat4 TG(1.0f);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform() {
  zNear = Radi;
  zFar = 3 * Radi;

  //perspective(FOV, ra, zN, zF);
  glm::mat4 ProjM;
  if (ra_nou == ra) ProjM = glm::perspective(FOV, ra, zNear, zFar);
  else if (ra_nou < 1.0) ProjM = glm::perspective(FOV_nou, ra_nou, zNear, zFar);
  else ProjM = glm::perspective(FOV, ra_nou, zNear, zFar);
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &ProjM[0][0]);
}

void MyGLWidget::viewTransform() {
  //Inicialització de les variables de càmara
  Pmin = glm::vec3(-2.5, 0.0, -2.5);
  Pmax = glm::vec3(2.5, 4.0, 2.5);
  VRP = glm::vec3(0.0, 0.0, 0.0);
  Radi = distance(VRP, Pmin);
  OBS = glm::vec3(VRP.x, VRP.y + 0.5, VRP.z) + 2*Radi*glm::vec3(0.0, 0.0, 1.0);  //d = 2R

  //lookAt(OBS, VRP, UP);
  glm::mat4 ViewM = glm::lookAt(OBS, VRP, glm::vec3(0.0, 1.0, 0.0));
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &ViewM[0][0]);
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glEnable(GL_DEPTH_TEST);
  //AIXÒ CALDRÀ CANVIAR-HO!!!
  m.load("/home/ferran/Documentos/IDI/bloc-2/Model/Patricio.obj");

  CHECK();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
  escala = 1.0f;

  FOV = FOV_nou = float(M_PI) / 3.0f;
  ra = ra_nou = 1.0;
}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  modelTransformModel();
  projectTransform();
  viewTransform();

  // Activem el VAO per a pintar la caseta
  glBindVertexArray(VAO_Model);

  // pintem
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size() * 3);

  modelTransformTerra();

  // Activem el VAO per a pintar la caseta
  glBindVertexArray(VAO_Terra);

  // pintem
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindVertexArray (0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  ra_nou = float(w) / float(h);
  FOV_nou = 2 * atan(tan(FOV / 2) / ra_nou);

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
}

void MyGLWidget::creaBuffers() {
  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Model);
  glBindVertexArray(VAO_Model);

  GLuint VBO_Model[2];
  glGenBuffers(2, VBO_Model);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Model[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_vertices(), GL_STATIC_DRAW); //posició
  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  CHECK();

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Model[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_matdiff(), GL_STATIC_DRAW);  //color
  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  CHECK();

  glm::vec3 posicio_Terra[6] = {
    glm::vec3(-2.5, 0.0, -2.5),
    glm::vec3(-2.5, 0.0, 2.5),
    glm::vec3(2.5, 0.0, 2.5),
    glm::vec3(2.5, 0.0, 2.5),
    glm::vec3(-2.5, 0.0, -2.5),
    glm::vec3(2.5, 0.0, -2.5),
  };
  glm::vec3 color_Terra[6] = {
    glm::vec3(1.0, 0.0, 1.0),
    glm::vec3(1.0, 0.0, 1.0),
    glm::vec3(1.0, 0.0, 1.0),
    glm::vec3(1.0, 0.0, 1.0),
    glm::vec3(1.0, 0.0, 1.0),
    glm::vec3(1.0, 0.0, 1.0),
  };

  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra[2];
  glGenBuffers(2, VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posicio_Terra), posicio_Terra, GL_STATIC_DRAW);
  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  CHECK();

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color_Terra), color_Terra, GL_STATIC_DRAW);
  // Activem l'atribut vertexLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  CHECK();

  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
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

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");

  projLoc = glGetUniformLocation(program->programId(), "ProjM");
  viewLoc = glGetUniformLocation(program->programId(), "ViewM");
}
