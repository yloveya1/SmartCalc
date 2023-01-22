#include "model.h"

namespace s21 {
void Model::change_names() {
  input = std::regex_replace(input, std::regex("asin"), "i");
  input = std::regex_replace(input, std::regex("acos"), "o");
  input = std::regex_replace(input, std::regex("atan"), "a");
  input = std::regex_replace(input, std::regex("sin"), "s");
  input = std::regex_replace(input, std::regex("cos"), "c");
  input = std::regex_replace(input, std::regex("tan"), "t");
  input = std::regex_replace(input, std::regex("ln"), "l");
  input = std::regex_replace(input, std::regex("log"), "g");
  input = std::regex_replace(input, std::regex("sqrt"), "q");
  input = std::regex_replace(input, std::regex("mod"), "m");
  input = std::regex_replace(input, std::regex(" "), "");
  input = std::regex_replace(input, std::regex("e\\-"), "e@");
  input = std::regex_replace(input, std::regex("e\\+"), "e%");
  for (size_t i = 0; i < input.size(); i++) {
    if (input[i] == '-') {
      input[i] = '~';
    } else if (input[i] == '+') {
      input[i] = '$';
    } else {
      break;
    }
  }
  input = std::regex_replace(input, std::regex("([^0-9)xe])\\+"), "$1$");
  input = std::regex_replace(input, std::regex("([^0-9)xe])\\-"), "$1~");
  input = std::regex_replace(input, std::regex("[0-9]?[.][0-9]*[.]"), "k");
}

void Model::to_polish() {
  change_names();
  stack<char> stack;
  polish += '|';
  char c = 0;
  for (size_t i = 0; i < input.size(); i++) {
    c = input[i];
    if (!(define_priority(c) || isdigit(c) || strchr("xe.@%", c) ||
          (define_priority(c) == 5 && input[i + 1] != '(')) ||
        strstr(input.c_str(), "xx") || strstr(input.c_str(), "()")) {
      throw std::invalid_argument("Incorrect input");
    }

    if (!define_priority(c) && c != '\n') {
      polish += c;
    } else {
      if (c == '(') {
        stack.push(c);
        continue;
      }
      if (c == ')') {
        while (!stack.empty() && stack.top() != '(') {  // stack->top != 0 && s
          polish += stack.top();
          stack.pop();
        }
        if (stack.empty()) {
          throw std::invalid_argument("Incorrect input");
        } else if (stack.top() == '(') {
          stack.pop();
        }
        continue;
      }
      while (!stack.empty() &&
             (c == '^' || c == '~' || c == '$'
                  ? define_priority(c) < define_priority(stack.top())
                  : define_priority(c) <= define_priority(stack.top()))) {
        polish += stack.top();
        stack.pop();
      }
      stack.push(c);
      if (define_priority(c) != 5 && define_priority(c) != 4) polish += '|';
    }
  }

  if (!((polish[1] == 'x' || polish[1] == '.' ||
         (polish[1] >= '0' && polish[1] <= '9')))) {
    throw std::invalid_argument("Incorrect input");
  }

  while (!stack.empty()) {
    if (stack.top() == '(') {
      throw std::invalid_argument("Incorrect input");
    }
    polish += stack.top();
    stack.pop();
  }
}

void Model::calculation() {
  setlocale(LC_NUMERIC, "C");
  stack<double> stack_double;
  polish = std::regex_replace(polish, std::regex("e@"), "e-");
  polish = std::regex_replace(polish, std::regex("e%"), "e+");
  char c = 0;
  for (size_t i = 0; i < polish.size(); i++) {
    c = polish[i];
    if (c == '|') {
      if (isdigit(polish[i + 1]) || polish[i + 1] == '.' ||
          polish[i + 1] == 'e') {
        stack_double.push(atof(polish.c_str() + i + 1));
      } else if (polish[i + 1] == 'x') {
        stack_double.push(x_);
      }
    }
    if ((c == '-' || c == '+') && polish[i - 1] == 'e') continue;
    simple_calc(c, stack_double);
  }
  res_ = stack_double.top();
  stack_double.pop();
  if (!std::isfinite(res_)) {  // std::isinf(res_) || std::isnan(res_)
    throw std::out_of_range("Result error");
  }
}

int Model::define_priority(char c) {
  int priority = 0;
  if (c == '(' || c == ')') {
    priority = 1;
  } else if (c == '+' || c == '-') {
    priority = 2;
  } else if (c == 's' || c == 'c' || c == 't' || c == 'o' || c == 'i' ||
             c == 'a' || c == 'q' || c == 'l' || c == 'g') {
    priority = 5;
  } else if (c == '*' || c == '/' || c == 'm') {
    priority = 3;
  } else if (c == '$' || c == '~') {
    priority = 4;
  } else if (c == '^') {
    priority = 6;
  }
  return priority;
}

void Model::simple_calc(char c, stack<double> &stack_double) {
  int pr = define_priority(c);
  if (pr > 1) {
    double a = 0, b = 0;
    if (!stack_double.empty()) {
      a = stack_double.top();
      stack_double.pop();
    }
    if (pr == 2 || pr == 3 || pr == 6) {
      if (stack_double.empty()) {
        throw std::out_of_range("Missing argument");
      } else {
        b = stack_double.top();
        stack_double.pop();
      }
    }
    if (c == '-') stack_double.push(b - a);
    if (c == '*') stack_double.push(b * a);
    if (c == '+') stack_double.push(b + a);
    if (c == '/') {
      if (a == 0) throw std::out_of_range("Division by zero");
      stack_double.push(b / a);
    }
    if (c == '^') stack_double.push(pow(b, a));
    if (c == 'm') {
      if (a == 0) throw std::out_of_range("Division by zero");
      stack_double.push(fmod(b, a));
    }
    if (c == 's') stack_double.push(sin(a));
    if (c == 'c') stack_double.push(cos(a));
    if (c == 't') stack_double.push(tan(a));
    if (std::strchr("oi", c) && (a < -1 || a > 1)) {
      throw std::out_of_range("The abs of argument cannot be more than 1");
    }
    if (c == 'o') stack_double.push(acos(a));
    if (c == 'i') stack_double.push(asin(a));
    if (c == 'a') stack_double.push(atan(a));
    if (std::strchr("qlg", c) && a < 0) {
      throw std::out_of_range("The argument cannot be negative");
    }
    if (c == 'q') stack_double.push(sqrt(a));
    if (c == 'l') stack_double.push(log(a));
    if (c == 'g') stack_double.push(log10(a));
    if (c == '~') stack_double.push(-a);
    if (c == '$') stack_double.push(a);
  }
}

void Model::credit_calc_ann() {
  double eps = bid_ / (100 * 12);
  double res =
      credit_ * (eps * pow((1 + eps), term_)) / (pow(1 + eps, term_) - 1);
  credit_res[1] = res;
  credit_res[0] = res * term_;
  credit_res[2] = res * term_ - credit_;
  credit_res[3] = 0;
}

void Model::credit_calc_diff() {
  double i_month = 0;
  double res = 0;
  double s_t = credit_ / term_;
  for (int i = 0; i < term_; i++) {
    i_month = (credit_ - s_t * i) * bid_ / (100 * 12) + s_t;
    res += i_month;
  }
  credit_res[0] = res;
  credit_res[2] = res - credit_;
  credit_res[1] = i_month;
  credit_res[3] = credit_ * bid_ / (100 * 12) + s_t;
}
}  // namespace s21
