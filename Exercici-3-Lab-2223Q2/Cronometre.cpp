#include "Cronometre.h"

Cronometre::Cronometre(QWidget* parent): QWidget(parent) {
  ui.setupUi(this);
  setWindowTitle(tr("Cronòmetre"));
  runningChrono = false;
}

void Cronometre::keyPressEvent(QKeyEvent *e) {
  if (e->modifiers() & Qt::AltModifier) {
    switch(e->key()) {
      case Qt::Key_R:
        emit emitRestart();
        break;
      case Qt::Key_S:
        if (runningChrono) emit emitStop();
        else emit emitStart();
        break;
      case Qt::Key_Q:
        emit emitQuit();
        break;
      default: e->ignore();
    }
  }
}

void Cronometre::changeRunningState(bool runningState) {
  runningChrono = runningState;
}