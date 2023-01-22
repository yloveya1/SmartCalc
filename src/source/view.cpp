
#include "view.h"

#include <math.h>

#include <QDebug>

#include "ui_s21_calculator.h"

namespace s21 {
ConsoleView::ConsoleView(Controller *controller_, QWidget *parent)
    : QMainWindow(parent), controller(controller_), ui(new Ui::ConsoleView) {
  ui->setupUi(this);
  ui->input->setMaxLength(255);
  ui->pushButton_eq->setShortcut(Qt::Key_Return);
  ui->pushButton_dot->setShortcut(QKeySequence(Qt::Key_1));
  ui->x_->setValidator(new QRegularExpressionValidator(
      QRegularExpression("(^[-0-9])([0-9]*)(\\.?)([0-9]*)"), this));
  ui->min->setValidator(new QRegularExpressionValidator(
      QRegularExpression("(^[-0-9])([0-9]*)(\\.?)([0-9]*)"), this));
  ui->max->setValidator(new QRegularExpressionValidator(
      QRegularExpression("(^[-0-9])([0-9]*)(\\.?)([0-9]*)"), this));
  ui->st->setValidator(new QRegularExpressionValidator(
      QRegularExpression("([0-9]*)(\\.?)([0-9]*)"), this));
  ui->sum->setValidator(new QRegularExpressionValidator(
      QRegularExpression("([0-9]*)(\\.?)([0-9]*)"), this));
  ui->credit_term->setValidator(new QRegularExpressionValidator(
      QRegularExpression("([0-9]*)(\\.?)([0-9]*)"), this));
  ui->bid->setValidator(new QRegularExpressionValidator(
      QRegularExpression("([0-9]*)(\\.?)([0-9]*)"), this));

  // button
  connect(ui->pushButton_0, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_open, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_close, SIGNAL(clicked(bool)), this,
          SLOT(digits_numbers()));
  // operators
  connect(ui->pushButton_add, SIGNAL(clicked(bool)), this,
          SLOT(push_operators()));
  connect(ui->pushButton_sub, SIGNAL(clicked(bool)), this,
          SLOT(push_operators()));
  connect(ui->pushButton_mul, SIGNAL(clicked(bool)), this,
          SLOT(push_operators()));
  connect(ui->pushButton_div, SIGNAL(clicked(bool)), this,
          SLOT(push_operators()));
  connect(ui->pushButton_pow, SIGNAL(clicked(bool)), this,
          SLOT(push_operators()));
  connect(ui->pushButton_mod, SIGNAL(clicked(bool)), this,
          SLOT(push_operators()));

  // trigonometry
  connect(ui->pushButton_sin, SIGNAL(clicked(bool)), this, SLOT(push_trig()));
  connect(ui->pushButton_cos, SIGNAL(clicked(bool)), this, SLOT(push_trig()));
  connect(ui->pushButton_tan, SIGNAL(clicked(bool)), this, SLOT(push_trig()));
  connect(ui->pushButton_asin, SIGNAL(clicked(bool)), this, SLOT(push_trig()));
  connect(ui->pushButton_acos, SIGNAL(clicked(bool)), this, SLOT(push_trig()));
  connect(ui->pushButton_atan, SIGNAL(clicked(bool)), this, SLOT(push_trig()));
  connect(ui->pushButton_ln, SIGNAL(clicked(bool)), this, SLOT(push_trig()));
  connect(ui->pushButton_log, SIGNAL(clicked(bool)), this, SLOT(push_trig()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked(bool)), this, SLOT(push_trig()));

  // output
}
void ConsoleView::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString input_eq = (ui->input->text() + button->text());
  ui->input->setText(input_eq);
}

void ConsoleView::on_pushButton_dot_clicked() {
  QString str = ui->input->text();
  std::reverse(str.begin(), str.end());
  int i = 0;
  for (i = 0; i < std::size(str); i++) {
    if (!(str[i].isDigit() || str[i] == '.')) break;
  }
  if (!str.left(i).contains('.')) ui->input->setText(ui->input->text() + '.');
}

void ConsoleView::on_pushButton_CE_clicked() { ui->input->clear(); }

void ConsoleView::on_pushButton_C_clicked() {
  QString text = ui->input->text();
  if (text.endsWith("acos(") || text.endsWith("asin(") ||
      text.endsWith("atan(") || text.endsWith("sqrt(") ||
      text.endsWith(" mod ")) {
    text.chop(5);
  } else if (text.endsWith("cos(") || text.endsWith("sin(") ||
             text.endsWith("tan(") || text.endsWith("log(")) {
    text.chop(4);
  } else if (text.endsWith("ln(")) {
    text.chop(3);
  } else {
    text.chop(1);
  }
  ui->input->setText(text);
}

void ConsoleView::push_trig() {
  QPushButton *button = (QPushButton *)sender();
  QString input_eq = (ui->input->text() + button->text() + '(');
  ui->input->setText(input_eq);
}

void ConsoleView::push_operators() {
  QPushButton *button = (QPushButton *)sender();
  QString input_eq = ui->input->text();
  if (!input_eq.isEmpty()) {
    QChar sa = ui->input->text().back();
    if (sa.isDigit() || input_eq.right(1) == ")" || input_eq.right(1) == "x") {
      input_eq += button->text();
      ui->input->setText(input_eq);
    }
  }
}

void ConsoleView::on_pushButton_eq_clicked() {
  controller->reset();
  controller->set_input(ui->input->text().toStdString());
  controller->set_x(ui->x_->text().toDouble());
  try {
    //      ui->input->setText(QString::number(controller->get_res(), 'f', 7));
    ui->input->setText(QString("%1").arg(controller->get_res(), 0, 'g', 8));
  } catch (const std::exception &e) {
    QMessageBox::critical(this, "Error information", e.what());
  }
}

void ConsoleView::on_pushButton_graph_clicked() {
  controller->reset();
  ui->pushButton_graph->setText("Create graph");
  ui->graph->clearGraphs();
  double a = -10;
  double b = 10;
  double h = 0.01;
  if (!ui->min->text().isEmpty())
    a = ui->min->text()
            .toDouble();  //Начало интервала, где рисуем график по оси Ox
  if (!ui->max->text().isEmpty())
    b = ui->max->text()
            .toDouble();  //Конец интервала, где рисуем график по оси Ox

  if (!ui->st->text().isEmpty() && ui->st->text().toDouble() > 0)
    h = ui->st->text().toDouble();  //Шаг, с которым будем пробегать по оси Ox
  if (b < a) {
    b = a + 10;
  }

  QVector<double> x, y;  //Массивы координат точек
  //Вычисляем наши данные
  int i = 0;
  bool flag = 0;
  //Пробегаем по всем точкам
  controller->set_input(ui->input->text().toStdString());
  for (double X = a; i++, X <= b && !flag; X = a + h * i) {
    controller->set_x(X);
    try {
      y.push_back(controller->get_res());
    } catch (const std::out_of_range &e) {
      continue;
    } catch (const std::invalid_argument &e) {
      flag = 1;
    }
    x.push_back(X);
  }
  if (!flag) {
    ui->graph->addGraph();
    ui->graph->setInteraction(QCP::iRangeZoom, true);
    ui->graph->setInteraction(QCP::iRangeDrag, true);
    ui->graph->graph(0)->setData(x, y);
    ui->graph->graph(0)->setPen(QColor(106, 90, 205));  //задаем цвет точки
    ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);  //убираем линии

    //формируем вид точек
    ui->graph->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    ui->graph->xAxis->setLabel("x");
    ui->graph->yAxis->setLabel("y");

    ui->graph->xAxis->setRange(a, b);  //Для оси Ox
    if (!y.empty()) {
      double minY = y[0], maxY = y[0];
      for (int j = 1; j < y.size(); j++) {
        if (y[j] <= minY) minY = y[j] - 3;
        if (y[j] >= maxY) maxY = y[j] + 3;
      }
      ui->graph->yAxis->setRange(minY, maxY);
    }
  }
  ui->graph->replot();
}

void ConsoleView::on_pushButton_x_clicked() {
  if (ui->input->text().right(1) != "x")
    ui->input->setText(ui->input->text() + "x");
}

void ConsoleView::on_pushButton_unar_clicked() {
  QString str = ui->input->text();
  std::reverse(str.begin(), str.end());
  int i = 0, len = std::size(str);
  for (i = 0; i < len; i++) {
    if (!(str[i].isDigit() || str[i] == '.' || str[i] == 'x')) break;
  }

  if (i < len && str[i] == '-') {
    ui->input->setText(ui->input->text().left(std::size(str) - i - 1) + "+" +
                       ui->input->text().right(i));
  } else if (i < len && str[i] == '+') {
    ui->input->setText(ui->input->text().left(std::size(str) - i - 1) + "-" +
                       ui->input->text().right(i));
  } else if (len == i) {
    ui->input->setText("-" + ui->input->text().left(std::size(str)));
  } else if (i < len && str[i] != ')') {
    if (str[i] == '(') {
      ui->input->setText(ui->input->text().left(std::size(str) - i) + "-" +
                         ui->input->text().right(i));
    } else {
      ui->input->setText(ui->input->text().left(std::size(str) - i) + "(-" +
                         ui->input->text().right(i));
    }
  }
}

void ConsoleView::on_pushButton_clicked() {
  ui->month->clear();
  ui->total->clear();
  ui->overpayment->clear();
  double term = ui->credit_term->text().toDouble();
  double months =
      (ui->year_or_month->currentText() == "лет") ? term * 12 : term;
  double bid = ui->bid->text().toDouble();
  double credit_sum = ui->sum->text().toDouble();
  if (bid && credit_sum && term) {
    controller->set_term(months);
    controller->set_bid(bid);
    controller->set_credit(credit_sum);
    double *res = nullptr;
    if (ui->type->currentText() == "annuity") {
      res = controller->get_credit_ann();
      ui->month->setText(QString::number(res[1]));
    } else {
      res = controller->get_credit_diff();
      ui->month->setText(QString::number(res[3]) + "..." +
                         QString::number(res[1]));
    }
    ui->total->setText(QString::number(res[0]));
    ui->overpayment->setText(QString::number(res[2]));
  }
  controller->reset_credit();
}
}  // namespace s21
