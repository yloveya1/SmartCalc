#include "controller.h"

namespace s21 {
void Controller::set_input(const string& input) { model->set_input(input); }

void Controller::set_x(double x) { model->set_x(x); }

double Controller::get_res() { return model->get_res(); }

void Controller::reset() { model->reset(); }

void Controller::reset_credit() { model->reset_credit(); }

void Controller::set_credit(double credit) { model->set_credit(credit); }

void Controller::set_term(double term) { model->set_term(term); }

void Controller::set_bid(double bid) { model->set_bid(bid); }

// double Controller::get_month() { return model->get_month(); }

// double Controller::get_month_start() { return
// model->get_month_start(); }

// double Controller::get_total() { return model->get_total(); }

// double Controller::get_over() { return model->get_over(); }

double* Controller::get_credit_ann() { return model->get_credit_ann(); }

double* Controller::get_credit_diff() { return model->get_credit_diff(); }
}  // namespace s21
