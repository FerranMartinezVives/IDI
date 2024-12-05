// MyGLWidget.h
#include "LL4GLWidget.h"
#include<QTimer>

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();
  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
  private:
    int printOglError(const char file[], int line, const char func[]);

    QTimer timer;
    bool running = false;

    virtual void setUpTimer();

    float angleYDiscoBall = 0.0f;
    float angleYFantasmes = 0.0f;
    float angleYMorty = 0.0f;

    bool estatFocusEscena = true;
    int estatFocusColors = 0;

    glm::vec3 colorFocusEscena, posicioFocusEscena;
    glm::vec3 arrayColorsFocus[4];
    glm::vec3 arrayPosicionsFocus[4];

    virtual void definirFocusLlum();
    virtual void calculaPosicionsFocusColors();

    virtual void modelTransformDiscoBall();
    virtual void modelTransformFantasma(float posX);
    virtual void modelTransformMorty();

    virtual void rotaDiscoBall();
    virtual void canviaFocusColors();

    virtual void initializeGL();
    virtual void paintGL();
    virtual void carregaShaders();

    GLuint colorFocusEscenaLoc, posicioFocusEscenaLoc;
    GLuint arrayColorsFocusLoc, arrayPosicionsFocusLoc;

  public slots:
    void festa();
};
