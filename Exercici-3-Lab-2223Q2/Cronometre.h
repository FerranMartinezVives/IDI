#include "ui_Cronometre.h"
#include<QKeyEvent>

class Cronometre : public QWidget {
  Q_OBJECT

  public:
    Cronometre(QWidget *parent = 0);

  private:
    Ui::Cronometre ui;
    bool runningChrono;

  protected:
    void keyPressEvent(QKeyEvent *e) override;
  
  public slots:
    void changeRunningState(bool runningState);
  
  signals:
    void emitStart();
    void emitStop();
    void emitRestart();
    void emitQuit();
};
