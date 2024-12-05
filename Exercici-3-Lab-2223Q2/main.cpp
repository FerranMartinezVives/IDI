#include<QApplication>
#include "Cronometre.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  Cronometre form;
  form.show();
  return app.exec();
}