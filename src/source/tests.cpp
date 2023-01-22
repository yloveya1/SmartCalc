#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "model.h"

using namespace s21;

TEST(SmartCalc, combo_1) {
  Model model;
  for (int i = 0; i < 5000; i++) {
    double x = i / 2;
    double test_result = (pow(asin(-0.556 * 0.556) + acos(0.98545) + atan(x) +
                                  log(x + 5) + 5 % 2,
                              2)) *
                         (3 * sin(-3));
    model.set_input(
        "((asin(-0.556^2) + acos(0.98545) + atan(x) + ln(x + 5) + 5 mod 2) ^ "
        "2) * (3 * sin(-3))");
    model.set_x(x);
    double my_result = model.get_res();
    EXPECT_EQ(fabs(my_result - test_result) < 1000, 1);
  }
}

TEST(SmartCalc, asin) {
  Model model;

  double x = -0.26546;
  double test_result = asin(x);
  model.set_input("asin(x)");
  model.set_x(x);
  double my_result = model.get_res();
  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, acos) {
  Model model;

  double x = -0.26546;
  double test_result = acos(x);
  model.set_input("acos(x)");
  model.set_x(x);
  double my_result = model.get_res();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, atan) {
  Model model;

  double x = 10000;
  double test_result = atan(x);
  model.set_input("atan(x)");
  model.set_x(x);
  double my_result = model.get_res();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, log) {
  Model model;

  double x = 0.1;
  double test_result = log10l(x);
  model.set_input("log(x)");
  model.set_x(x);
  double my_result = model.get_res();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, sin) {
  Model model;

  double x = -1000;
  double test_result = sin(x);
  model.set_input("sin(x)");
  model.set_x(x);
  double my_result = model.get_res();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, cos) {
  Model model;

  double x = 102654;
  double test_result = cos(x);
  model.set_input("cos(x)");
  model.set_x(x);
  double my_result = model.get_res();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, tan) {
  Model model;

  double x = -1.9999;
  double test_result = tan(x);
  model.set_input("tan(x)");
  model.set_x(x);
  double my_result = model.get_res();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, ln) {
  Model model;

  double x = 0.1;
  double test_result = logl(x);
  model.set_input("ln(x)");
  model.set_x(x);
  double my_result = model.get_res();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}
TEST(SmartCalc, sqrt) {
  Model model;

  double x = 25468;
  double test_result = sqrt(x);
  model.set_input("sqrt(x)");
  model.set_x(x);
  double my_result = model.get_res();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}
TEST(SmartCalc, pow) {
  Model model;

  double x = 6;
  double test_result = 1 + pow(2, x);
  model.set_input("1 + 2^(x)");
  model.set_x(x);
  double my_result = model.get_res();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, arifmetic_test) {
  Model model;
  model.set_input("-1 + 2 - 4 * (+10 / 2 + 5 mod 2)");
  double my_result = model.get_res();

  EXPECT_EQ(fabs(my_result - (-23.0)) < 1e-6, 1);
}

TEST(SmartCalcThrow, incorrect_test) {
  Model model;
  model.set_input("2^(3)) + 4");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, incorrect_input_1) {
  Model model;
  model.set_input("san(5)");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, incorrect_input_2) {
  Model model;
  model.set_input("f");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, incorrect_input_3) {
  Model model;
  model.set_input("");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, incorrect_input_4) {
  Model model;
  model.set_input("()");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, incorrect_input_5) {
  Model model;
  model.set_input("1+");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, incorrect_input_6) {
  Model model;
  model.set_input("1/0");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, incorrect_input_7) {
  Model model;
  model.set_input("+");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, incorrect_input_8) {
  Model model;
  model.set_input("((2+3)");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalc, repeat_input_1) {
  Model model;
  model.set_input("2+3");
  double result = model.get_res();
  result = model.get_res();
  EXPECT_EQ(fabs(result - 5.0) < 1e-6, 1);
}

TEST(SmartCalc, exp_negative) {
  Model model;
  model.set_input("2e-3");
  double my_result = model.get_res();
  double test_result = 0.002;
  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, unar_and_op) {
  Model model;
  model.set_input("3/-3 - 6/-2");
  double my_result = model.get_res();
  EXPECT_EQ(fabs(my_result - 2.0) < 1e-6, 1);
}

TEST(SmartCalcThrow, asin_throw) {
  Model model;
  model.set_input("asin(-5)");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, acos_throw) {
  Model model;
  model.set_input("acos(5)");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, missing_argument) {
  Model model;
  model.set_input("-");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, isfinite) {
  Model model;
  model.set_input("100000e1000");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, missing_one_argument) {
  Model model;
  model.set_input("/-");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(SmartCalcThrow, sqrt_throw) {
  Model model;
  model.set_input("sqrt(-4)");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(Credit_calc, credit1) {
  Model model;
  model.set_input("sqrt(-4)");
  EXPECT_ANY_THROW(model.get_res());
}

TEST(Credit_calc, credit2) {
  Model model;
  model.set_credit(50000);
  model.set_term(60);
  model.set_bid(15);
  double res_ann[4] = {71369.8, 1189.5, 21369.8, 0};
  double res_diff[4] = {69062.5, 843.75, 19062.5, 1458.33};
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(fabs(res_ann[i] - model.get_credit_ann()[i]) < 1e-1, 1);
    EXPECT_EQ(fabs(res_diff[i] - model.get_credit_diff()[i]) < 1e-1, 1);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}