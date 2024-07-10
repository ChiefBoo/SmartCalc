#include "../test_includes/s21_tests.h"

START_TEST(calc_1) {
  char expression[255] = "2+6-8*(7-6";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_2) {
  char expression[255] = "2+6-8*(7-6))-sin(7)";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_3) {
  char expression[255] = "2+6-8*(7-6)-sit(7)";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_4) {
  char expression[255] = "2+2*2";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 0;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, 6, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_5) {
  char expression[255] = "sin(5)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 0;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, -0.9589242747, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_6) {
  char expression[255] = "cos(67)-sin(6)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 0;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, -0.238354301591, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_7) {
  char expression[255] = "cos(67)-sin(6)*ln(x-67)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 68;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, -0.5177697998, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_8) {
  char expression[255] = "(6-8*(6/6 + 6^4 - 1/3))";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 68;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, -10367.3333333333, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_9) {
  char expression[255] = "15mod3 + 9";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 68;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, 9, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_10) {
  char expression[255] = "tan(15)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 68;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, -0.855993400909, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_16) {
  char expression[255] = "asin(0.3)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 68;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, 0.304692654015, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_14) {
  char expression[255] = "acos(0.5)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 68;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, 1.047197551197, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_15) {
  char expression[255] = "atan(0.5)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 68;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, 0.463647609001, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_11) {
  char expression[255] = "sqrt(-4)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 68;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, 0, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_12) {
  char expression[255] = "sqrt(4) + 8";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 68;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, 10, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_13) {
  char expression[255] = "ln(5)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 68;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, 1.6094379124341004, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_17) {
  char expression[255] = "0.6-1,6*7";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 68;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, -10.6, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_18) {
  char expression[255] = "0.6#-1,6*7";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_19) {
  char expression[255] = "-7+(-cos(7) /7 )";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 0;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, -7.107700322049, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_20) {
  char expression[255] = "*9-7+(-cos(7) /7 )";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_21) {
  char expression[255] = "log(10) - 8,7";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 0;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, -7.7, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_22) {
  char expression[255] = "9-7+8*";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_23) {
  char expression[255] = "9-+7+8*";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_24) {
  char expression[255] = "x(7-8)";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_25) {
  char expression[255] = "x78";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_26) {
  char expression[255] = "acos8";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_27) {
  char expression[255] = "sin8+7";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_28) {
  char expression[255] = "5mos8";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_29) {
  char expression[255] = "ln1";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_30) {
  char expression[255] = "lom8";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_31) {
  char expression[255] = "8.3453.6+945";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_32) {
  char expression[255] = "5/(6-6)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 0;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, -7.7, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_33) {
  char expression[255] = "ln(6-7)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 0;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, -7.7, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_34) {
  char expression[255] = "acos(8)";
  Node* stack = NULL;
  Node* rev_stack = NULL;
  double x_val = 0;
  double result = 0;
  int status = 1;
  status = check_validation(expression);
  if (status == OK) {
    parser(expression, &stack);
    reverse_stack(&stack, &rev_stack);
    free_stack(&stack);
    reverse_polish_notation(&rev_stack, &stack);
    free_stack(&rev_stack);
    reverse_stack(&stack, &rev_stack);
    status = calculate(&rev_stack, x_val, &result);
    if (status == OK) {
      ck_assert_double_eq_tol(result, -7.7, 1e-7);
    } else {
      ck_assert_int_eq(status, ERROR);
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    ck_assert_int_eq(status, ERROR);
  }
}
END_TEST

START_TEST(calc_35) {
  char expression[255] = "sqrs(7)";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(calc_36) {
  char expression[255] = "sqrs(7)+78.";
  int status = check_validation(expression);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

Suite* suite_calc_expression(void) {
  Suite* s = suite_create("\033[1;31m--CALC EXPRESSION--\033[m");
  TCase* tc = tcase_create("calc_expression_tc");

  tcase_add_test(tc, calc_1);
  tcase_add_test(tc, calc_2);
  tcase_add_test(tc, calc_3);
  tcase_add_test(tc, calc_4);
  tcase_add_test(tc, calc_5);
  tcase_add_test(tc, calc_6);
  tcase_add_test(tc, calc_7);
  tcase_add_test(tc, calc_8);
  tcase_add_test(tc, calc_9);
  tcase_add_test(tc, calc_10);
  tcase_add_test(tc, calc_11);
  tcase_add_test(tc, calc_12);
  tcase_add_test(tc, calc_13);
  tcase_add_test(tc, calc_14);
  tcase_add_test(tc, calc_15);
  tcase_add_test(tc, calc_16);
  tcase_add_test(tc, calc_17);
  tcase_add_test(tc, calc_18);
  tcase_add_test(tc, calc_19);
  tcase_add_test(tc, calc_20);
  tcase_add_test(tc, calc_21);
  tcase_add_test(tc, calc_22);
  tcase_add_test(tc, calc_23);
  tcase_add_test(tc, calc_24);
  tcase_add_test(tc, calc_25);
  tcase_add_test(tc, calc_26);
  tcase_add_test(tc, calc_27);
  tcase_add_test(tc, calc_28);
  tcase_add_test(tc, calc_29);
  tcase_add_test(tc, calc_30);
  tcase_add_test(tc, calc_31);
  tcase_add_test(tc, calc_32);
  tcase_add_test(tc, calc_33);
  tcase_add_test(tc, calc_34);
  tcase_add_test(tc, calc_35);
  tcase_add_test(tc, calc_36);
  suite_add_tcase(s, tc);

  return s;
}
