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

void MyGLWidget::paintGL ()   // Mètode que has de modificar
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  if (showPatr) {
    // Pintem el Patricio
    glBindVertexArray (VAO_Patr);
    modelTransformPatricio ();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }
  else {
    // Pintem el cub petit
    glBindVertexArray(VAO_Cub);
    modelTransformCub (2.0 / 0.5, angleCub1);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Pintem el cub mitjà
    glBindVertexArray(VAO_Cub);
    modelTransformCub (2.5 / 0.5, angleCub2);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //Pintem el cub gran
    glBindVertexArray(VAO_Cub);
    modelTransformCub (3.0 / 0.5, angleCub3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCub (float escala, float angle) 
{
  glm::vec3 centreBase;
  TG = glm::mat4(1.0);
  TG = rotate(TG, angle, glm::vec3(0.0, 1.0, 0.0));
  TG = translate(TG, glm::vec3(5.0, 0.0, 0.0));
  TG = scale(TG, glm::vec3(escala, escala, escala));

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio ()    // Mètode que has de modificar
{
  TG = glm::mat4(1.0);
  TG = rotate(TG, anglePatr, glm::vec3(0.0, 1.0, 0.0));
  TG = translate(TG, glm::vec3(5.0, 0.0, 0.0));
  TG = rotate(TG, float(M_PI) / (-2.0f), glm::vec3(0.0, 1.0, 0.0));
  TG = glm::scale(TG, glm::vec3 (2.0 * escala, 2.0 * escala, 2.0 * escala));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else {
    glm::vec3 OBS(0.0, 6.0, 0.0);
    glm::vec3 VRP(0.0, 0.0, 0.0);
    glm::vec3 UP(1.0, 0.0, 0.0);
    glm::mat4 VM = glm::lookAt(OBS, VRP, UP);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &VM[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else {
    glm::mat4 PM = glm::ortho(-10.0, 10.0, -10.0, 10.0, 3.0, 7.0);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &PM[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
      showPatr = not showPatr;
    break;
	}
  case Qt::Key_1: {
      anglePatr = angleCub1;
    break;
	}
  case Qt::Key_2: {
      anglePatr = angleCub2;
    break;
	}
  case Qt::Key_3: {
      anglePatr = angleCub3;
    break;
	}
  case Qt::Key_F: {
      if (colFoc == glm::vec3(1.0, 1.0, 1.0)) colFoc = glm::vec3(1.0, 1.0, 0.0);
      else colFoc = glm::vec3(1.0, 1.0, 1.0);
      enviaColFocus();
    break;
	}
  case Qt::Key_C: {
      //AQUÍ HI HA UN BUCLE AMB canviaCameraToggle()?
      canviaCamera();
      emetre = false;
      if (camPlanta) emit toggleCamera1();
      else emit toggleCamera2();
      emetre = true;
    break;
	}
  case Qt::Key_Right: {
      angleCub1 += 2.0 * float(M_PI) / 3.0;
      angleCub2 += 2.0 * float(M_PI) / 3.0;
      angleCub3 += 2.0 * float(M_PI) / 3.0;
      anglePatr += 2.0 * float(M_PI) / 3.0;
    break;
	}
  case Qt::Key_Left: {
      angleCub1 -= 2.0 * float(M_PI) / 3.0;
      angleCub2 -= 2.0 * float(M_PI) / 3.0;
      angleCub3 -= 2.0 * float(M_PI) / 3.0;
      anglePatr -= 2.0 * float(M_PI) / 3.0;
    break;
	}
  case Qt::Key_R: {
      showPatr = false;
      anglePatr = 0.0;
      angleCub1 = 0.0;
      angleCub2 = 2.0 * float(M_PI) / 3.0;
      angleCub3 = 4.0 * float(M_PI) / 3.0;
      emetre = true;
      emit toggleCamera1();
      ExamGLWidget::initializeGL();
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::canviaCamera() {
  camPlanta = not camPlanta;
  viewTransform();
  projectTransform();
}

void MyGLWidget::canviaCameraToggle() {
  //QUEDA PODER CANVIAR EL PATRICIO DE LLOC
  if (emetre) {
    makeCurrent();
    canviaCamera();
    update();
  }
}

