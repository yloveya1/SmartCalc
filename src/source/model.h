#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <stack>
#include <stdexcept>
#include <string>
using std::stack;
using std::string;
namespace s21 {
class Model {
 private:
  std::string input, polish;
  double res_, x_, credit_, term_, bid_;
  double credit_res[4] = {0, 0, 0, 0};
  void calculation();
  void change_names();
  void to_polish();
  int define_priority(char c);
  void simple_calc(char c, stack<double>& stack_double);
  void credit_calc_ann();
  void credit_calc_diff();

 public:
  Model()
      : input(""), polish(""), res_(0), x_(0), credit_(0), term_(0), bid_(0){};

  void set_input(const string& str) { input = str; }

  void set_x(double x) { x_ = x; }

  double get_res() {
    if (polish.empty()) {
      to_polish();
    }
    calculation();
    return res_;
  }

  void reset() {
    res_ = x_ = 0;
    input.clear();
    polish.clear();
  }

  // credit calc
  void set_credit(double credit) { credit_ = credit; }
  void set_term(double term) { term_ = term; }
  void set_bid(double bid) { bid_ = bid; }
  void reset_credit() { credit_ = term_ = bid_ = 0; }
  double* get_credit_ann() {
    credit_calc_ann();
    return credit_res;
  }
  double* get_credit_diff() {
    credit_calc_diff();
    return credit_res;
  }
};
}  // namespace s21
#endif
