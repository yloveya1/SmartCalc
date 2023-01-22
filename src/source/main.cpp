#include <QApplication>

#include "view.h"
using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Model model;
  Controller controller(&model);
  ConsoleView view(&controller);
  view.show();
  return a.exec();
}
