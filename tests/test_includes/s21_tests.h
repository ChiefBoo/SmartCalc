#ifndef SRC_TESTS_INCLUDES_S21_TESTS_H_
#define SRC_TESTS_INCLUDES_S21_TESTS_H_

#include <check.h>
#include <stdio.h>

#include "../../backend/smartcalc.h"
#include "../../backend/stack.h"

Suite *suite_calc_expression(void);

void run_tests(void);
void run_testcase(Suite *testcase);

#endif  // SRC_TESTS_INCLUDES_S21_TESTS_H_
