#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio ();
    virtual void projectTransform ();
    virtual void viewTransform ();

  private:
    int printOglError(const char file[], int line, const char func[]);

    bool showPatr = false;
    float anglePatr = 0.0;
    float angleCub1 = 0.0;
    float angleCub2 = 2.0 * float(M_PI) / 3.0;
    float angleCub3 = 4.0 * float(M_PI) / 3.0;

    bool emetre = true;

    void canviaCamera();

  public slots:
    void canviaCameraToggle();

  signals:
    void toggleCamera1();
    void toggleCamera2();
};
