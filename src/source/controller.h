#ifndef EXAMPLECONTROLLER_H
#define EXAMPLECONTROLLER_H

#include "model.h"

namespace s21 {
class Controller {
 private:
  Model* model;

 public:
  Controller(Model* m) : model(m){};
  void set_input(const std::string& input);
  void set_x(double x);
  void set_credit(double credit);
  void set_term(double term);
  void set_bid(double bid);
  double get_res();
  void reset();

  // Credit
  double* get_credit_ann();
  double* get_credit_diff();
  void reset_credit();
};
}  // namespace s21
#endif
