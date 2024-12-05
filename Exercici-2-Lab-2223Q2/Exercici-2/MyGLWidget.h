#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();

  protected:

  private:

    int printOglError(const char file[], int line, const char func[]);

    virtual void initializeGL();

    virtual void iniCamera();
    virtual void iniCamera1aPersona();
    virtual void viewTransform();
    virtual void viewTransform1aPersona();
    virtual void projectTransform();
    virtual void projectTransform1aPersona();

    virtual void RickTransform();
    virtual void MortyTransform();
    virtual void VideoCameraTransform();

    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);

    virtual void carregaShaders();

    glm::vec3 pmin, pmax, vrp1aPersona, filtre;
    float fov_nou, angleYVideoCamera, angleX, angleY, znear1aPersona, zfar1aPersona, fov1aPersona, ra1aPersona;
    GLuint filtreLoc, invisibilitatLoc;
    bool camera1aPersona, invisibilitatRick;
};
