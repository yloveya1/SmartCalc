#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QRegularExpressionValidator>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ConsoleView;
}
QT_END_NAMESPACE

namespace s21 {
class ConsoleView : public QMainWindow {
  Q_OBJECT
 private:
  Controller *controller;
  Ui::ConsoleView *ui;

 public:
  ConsoleView(){};
  ConsoleView(Controller *controller_, QWidget *parent = nullptr);
  ~ConsoleView() { delete ui; }

 private slots:
  void digits_numbers();
  void on_pushButton_dot_clicked();
  void on_pushButton_CE_clicked();
  void on_pushButton_C_clicked();
  void push_trig();
  void push_operators();
  void on_pushButton_eq_clicked();
  void on_pushButton_graph_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_unar_clicked();
  void on_pushButton_clicked();
};
}  // namespace s21
#endif
