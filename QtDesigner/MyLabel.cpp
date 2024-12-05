º#include "MyLabel.h"

MyLabel::MyLabel(QWidget *parent=0):QLabel(parent)
{
}

void MyLabel::setTextMajuscules(QString s) {
  QString str = s.toUpper();
  setText(str);
}

void MyLabel::obreBarra() {
  QString str = "Obert";
  setText(str);
  setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(255, 255, 255);");
}

void MyLabel::tancaBarra() {
  QString str = "Tancat";
  setText(str);
  setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(255, 255, 255);");
}