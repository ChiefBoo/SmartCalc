#ifndef SRC_BACKEND_SMARTCALC_H
#define SRC_BACKEND_SMARTCALC_H

#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

//#include <stdio.h> // delete after

#define OK 0
#define ERROR 1

// validation
void skip_spaces(char* expression);
int check_validation(char* expression);
int check_funcs(char* expression, int* idx, int* len);
int is_digit(char* expression, int idx);
int check_digit(char* expression, int* idx);

// parser
int parser(char* expression, Node** stack);
void reverse_stack(Node** old_stack, Node** new_stack);
int get_priority(type_t type);
int get_func(char* func, int* idx);

// notation
int is_func_unary(type_t type);
int is_func_binary(type_t type);
void reverse_polish_notation(Node** stack, Node** output_stack);

// calculate
double binary_func(type_t type, double num1, double num2);
double unary_func(type_t type, double num);
int calculate(Node** notation, double x_value, double* result);

#endif  // SRC_BACKEND_SMARTCALC_H