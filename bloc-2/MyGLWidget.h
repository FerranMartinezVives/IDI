// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h"
#include "math.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  private:
    int printOglError(const char file[], int line, const char func[]);

    virtual void initializeGL();

    virtual void carregaShaders();

    virtual void creaBuffers();

    virtual void paintGL();

    virtual void resizeGL (int width, int height);

    virtual void projectTransform();

    virtual void viewTransform();

    virtual void modelTransformModel();

    virtual void modelTransformTerra();

    GLuint projLoc, viewLoc;

    GLuint VAO_Model, VAO_Terra;

    glm::vec3 Pmin, Pmax, VRP, OBS;

    float Radi, FOV, ra, zNear, zFar, FOV_nou, ra_nou;

    Model m;
};
