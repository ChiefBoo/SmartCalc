#include "smartcalc.h"

// validation
void skip_spaces(char* expression) {
  setlocale(LC_ALL, "C");
  char* skip_values = " \n\t";
  char clean_expression[255];
  size_t j = 0;
  for (size_t i = 0; i < strlen(expression); i++) {
    if (!strchr(skip_values, expression[i]))
      clean_expression[j++] = expression[i];
  }
  clean_expression[j] = '\0';
  for (size_t i = 0; i < strlen(clean_expression); i++)
    expression[i] = clean_expression[i];
  expression[strlen(clean_expression)] = '\0';
}

int check_validation(char* expression) {
  setlocale(LC_ALL, "C");
  int status = OK;
  skip_spaces(expression);
  int brace_count = 0;
  char* available_characters = "0123456789.,+-*%/^()cosintalgmdqrx";
  int len_expression = strlen(expression);
  int min_len = 1;
  // if (strchr(expression, 'x')) min_len = 1;
  for (int i = 0; i < len_expression && brace_count >= 0 &&
                  len_expression > min_len && status == OK;
       i++) {
    if (!strchr(available_characters, expression[i])) {
      status = ERROR;
    }
    if (expression[i] == ',') {
      expression[i] = '.';
    }
    if (strchr("%.*/^+-(", expression[len_expression - 1])) {
      status = ERROR;
      break;
    } else if (i == 0 && (expression[i] == '+' || expression[i] == '-')) {
      memmove(expression + 1, expression, strlen(expression) + 1);
      memset(expression, '0', 1);
      len_expression++;
      i++;
    } else if (expression[i] == '(') {
      brace_count += 1;
    } else if (expression[i] == ')') {
      brace_count -= 1;
    } else if (is_digit(expression, i)) {
      status = check_digit(expression, &i);
    } else if (i == 0 && (strchr(")%.*/^", expression[0]))) {
      status = ERROR;
    } else if (i > 0 && strchr("(%.*/^+-", expression[i - 1]) &&
               strchr(")%.*/^", expression[i])) {
      status = ERROR;
    } else if (strchr("sctlam", expression[i])) {
      status = check_funcs(expression, &i, &len_expression);
    } else if (strchr("+-", expression[i]) && i > 0 &&
               strchr("%.*/^+-", expression[i - 1])) {
      status = ERROR;
    } else if ((strchr("+-", expression[i]) && i > 0 &&
                expression[i - 1] == '(')) {
      memmove(expression + i + 1, expression + i, strlen(expression + i) + 1);
      memset(expression + i, '0', 1);
      len_expression++;
      i++;
    } else if (expression[i] == 'x') {
      if (i == 0 && (strchr("().sctal", expression[i + 1]) ||
                     is_digit(expression, i + 1))) {
        status = ERROR;
      } else if (i > 0 && (i != (len_expression - 1)) &&
                 (strchr("(.sctal", expression[i + 1]) ||
                  strchr(").", expression[i - 1]) ||
                  is_digit(expression, i + 1) || is_digit(expression, i - 1))) {
        status = ERROR;
      } else if (i == (len_expression - 1) &&
                 (strchr("().", expression[i - 1]) ||
                  is_digit(expression, i - 1))) {
        status = ERROR;
      }
    }
  }
  if (len_expression < min_len || abs(brace_count) > 0 || status == ERROR)
    status = ERROR;
  return status;
}

int check_funcs(char* expression, int* idx, int* len) {
  setlocale(LC_ALL, "C");
  int status = OK;
  char dest[5] = "";
  char new_dest[5] = "";
  strncpy(dest, expression + *idx, 5);
  if (dest[0] == 'a') {
    strncpy(new_dest, dest, 5);
    if (!strncmp(new_dest, "asin(", 5) || !strncmp(new_dest, "acos(", 5) ||
        !strncmp(new_dest, "atan(", 5)) {
      *idx += 3;
    } else {
      status = ERROR;
    }
  } else if (strchr("sct", dest[0])) {
    if (strlen(dest) > 2 && dest[0] == 's' && dest[1] == 'q') {
      strncpy(new_dest, dest, 5);
      if (!strncmp(new_dest, "sqrt(", 4)) {
        *idx += 3;
      } else {
        status = ERROR;
      }
    } else {
      strncpy(new_dest, dest, 4);
      if (!strncmp(new_dest, "sin(", 4) || !strncmp(new_dest, "cos(", 4) ||
          !strncmp(new_dest, "tan(", 4)) {
        *idx += 2;
      } else {
        status = ERROR;
      }
    }
  } else if (dest[0] == 'm') {
    strncpy(new_dest, dest, 3);
    if (!strncmp(new_dest, "mod", 3)) {
      expression[*idx] = '%';
      memmove(expression + (*idx) + 1, expression + (*idx) + 3,
              strlen(expression + (*idx) + 3) + 1);
      *len = *len - 2;
    } else {
      status = ERROR;
    }
  } else if (dest[0] == 'l') {
    if (strlen(dest) > 2) {
      if (dest[1] == 'n') {
        strncpy(new_dest, dest, 3);
        if (!strncmp(new_dest, "ln(", 3)) {
          *idx += 1;
        } else {
          status = ERROR;
        }
      } else if (dest[1] == 'o') {
        strncpy(new_dest, dest, 4);
        if (!strncmp(new_dest, "log(", 4)) {
          *idx += 2;
        } else {
          status = ERROR;
        }
      } else {
        status = ERROR;
      }
    }
  }
  return status;
}

int check_digit(char* expression, int* idx) {
  setlocale(LC_ALL, "C");
  int status = OK;
  while (is_digit(expression, *idx)) {
    (*idx)++;
  }
  if (expression[*idx] == '.') {
    (*idx)++;
    if (!is_digit(expression, *idx)) {
      status = ERROR;
    } else {
      while (is_digit(expression, *idx)) {
        (*idx)++;
      }
      if (expression[*idx] == '.') {
        status = ERROR;
      }
    }
  }
  (*idx)--;
  return status;
}

int is_digit(char* expression, int idx) {
  return (expression[idx] >= '0' && expression[idx] <= '9');
}

// parser
void reverse_stack(Node** old_stack, Node** new_stack) {
  setlocale(LC_ALL, "C");
  while (*old_stack) {
    push(new_stack, (*old_stack)->lex.type, (*old_stack)->lex.priority,
         (*old_stack)->lex.value);
    pop(old_stack);
  }
}

int parser(char* expression, Node** stack) {
  int status = OK;
  setlocale(LC_ALL, "C");
  int len_expression = strlen(expression);
  char number_type[] = "1234567890.";
  char arithmetic_type[] = "+-*/%^";
  char func_type[] = "sctal";
  for (int i = 0; i < len_expression; i++) {
    if (strchr(number_type, expression[i])) {
      char number[255];
      int j = 0;
      while (strchr(number_type, expression[i]) && expression[i] != '\0') {
        number[j] = expression[i];
        j++;
        i++;
      }
      number[j] = '\0';
      double vl = atof(number);
      push(stack, NUM, get_priority(NUM), vl);
      number[0] = '\0';
      i--;
    } else if (strchr(arithmetic_type, expression[i])) {
      if (expression[i] == '+')
        push(stack, ADD, get_priority(ADD), expression[i]);
      else if (expression[i] == '-')
        push(stack, DIF, get_priority(DIF), expression[i]);
      else if (expression[i] == '*')
        push(stack, MUL, get_priority(MUL), expression[i]);
      else if (expression[i] == '/')
        push(stack, DIV, get_priority(DIV), expression[i]);
      else if (expression[i] == '%')
        push(stack, MOD, get_priority(MOD), expression[i]);
      else if (expression[i] == '^')
        push(stack, POW, get_priority(POW), expression[i]);
    } else if (strchr(func_type, expression[i])) {
      int func = get_func(expression, &i);
      if (func == 's')
        push(stack, SIN, get_priority(SIN), 's');
      else if (func == 'c')
        push(stack, COS, get_priority(COS), 'c');
      else if (func == 't')
        push(stack, TAN, get_priority(TAN), 't');
      else if (func == 'S')
        push(stack, ASIN, get_priority(ASIN), 'S');
      else if (func == 'C')
        push(stack, ACOS, get_priority(ACOS), 'C');
      else if (func == 'T')
        push(stack, ATAN, get_priority(ATAN), 'T');
      else if (func == 'L')
        push(stack, LOG, get_priority(LOG), 'L');
      else if (func == 'n')
        push(stack, LN, get_priority(LN), 'l');
      else if (func == 'q')
        push(stack, SQRT, get_priority(SQRT), 'q');
    } else if (expression[i] == '(')
      push(stack, BRACK_O, get_priority(BRACK_O), '(');
    else if (expression[i] == ')')
      push(stack, BRACK_C, get_priority(BRACK_C), ')');
    else if (expression[i] == 'x')
      push(stack, X, get_priority(X), 'x');
    else
      status = ERROR;
  }
  return status;
}

int get_priority(type_t type) {
  setlocale(LC_ALL, "C");
  int priority = 0;
  if (type == ADD || type == DIF) priority = 1;
  if (type == MUL || type == DIV || type == MOD) priority = 2;
  if (type == POW) priority = 3;
  if (type == COS || type == SIN || type == TAN || type == ACOS ||
      type == ASIN || type == ATAN || type == SQRT || type == LN || type == LOG)
    priority = 0;
  return priority;
}

int get_func(char* func, int* idx) {
  setlocale(LC_ALL, "C");
  int type = 0;
  char dest[5] = "";
  strncpy(dest, func + *idx, 4);
  if (!strncmp("asin", dest, 4)) {
    *idx += 3;
    type = 'S';
  } else if (!strncmp("acos", dest, 4)) {
    *idx += 3;
    type = 'C';
  } else if (!strncmp("atan", dest, 4)) {
    *idx += 3;
    type = 'T';
  } else if (!strncmp("sin", dest, 3)) {
    *idx += 2;
    type = 's';
  } else if (!strncmp("cos", dest, 3)) {
    *idx += 2;
    type = 'c';
  } else if (!strncmp("tan", dest, 3)) {
    *idx += 2;
    type = 't';
  } else if (!strncmp("log", dest, 3)) {
    *idx += 2;
    type = 'L';
  } else if (!strncmp("ln", dest, 2)) {
    *idx += 1;
    type = 'n';
  } else if (!strncmp("sqrt", dest, 4)) {
    *idx += 3;
    type = 'q';
  }
  return type;
}

// notation
int is_func_unary(type_t type) {
  setlocale(LC_ALL, "C");
  int is_unary = 0;
  if (type == SIN || type == COS || type == TAN || type == ASIN ||
      type == ACOS || type == ATAN || type == LN || type == LOG || type == SQRT)
    is_unary = 1;
  return is_unary;
}

int is_func_binary(type_t type) {
  setlocale(LC_ALL, "C");
  int is_binary = 0;
  if (type == ADD || type == DIF || type == MUL || type == DIV || type == MOD ||
      type == POW)
    is_binary = 1;
  return is_binary;
}

void reverse_polish_notation(Node** stack, Node** output_stack) {
  setlocale(LC_ALL, "C");
  // int status = OK;
  Node* help_stack = NULL;
  while ((*stack) != NULL) {
    if ((*stack)->lex.type == NUM || (*stack)->lex.type == X) {
      push(output_stack, (*stack)->lex.type, (*stack)->lex.priority,
           (*stack)->lex.value);
      pop(stack);
    } else if (is_func_unary((*stack)->lex.type) ||
               (*stack)->lex.type == BRACK_O) {
      push(&help_stack, (*stack)->lex.type, (*stack)->lex.priority,
           (*stack)->lex.value);
      pop(stack);
    } else if ((is_func_binary((*stack)->lex.type))) {
      while (help_stack != NULL && (is_func_binary((help_stack)->lex.type)) &&
             help_stack->lex.priority >= (*stack)->lex.priority) {
        push(output_stack, help_stack->lex.type, help_stack->lex.priority,
             help_stack->lex.value);
        pop(&help_stack);
      }
      push(&help_stack, (*stack)->lex.type, (*stack)->lex.priority,
           (*stack)->lex.value);
      pop(stack);
    } else if ((*stack)->lex.type == BRACK_C) {
      while (help_stack != NULL && help_stack->lex.type != BRACK_O) {
        push(output_stack, help_stack->lex.type, help_stack->lex.priority,
             help_stack->lex.value);
        pop(&help_stack);
      }
      if (help_stack->lex.type == BRACK_O) {
        pop(&help_stack);
        pop(stack);
      }
      while (help_stack != NULL && is_func_unary((help_stack)->lex.type)) {
        push(output_stack, help_stack->lex.type, help_stack->lex.priority,
             help_stack->lex.value);
        pop(&help_stack);
      }
    }
  }
  while (help_stack != NULL) {
    push(output_stack, help_stack->lex.type, help_stack->lex.priority,
         help_stack->lex.value);
    pop(&help_stack);
  }
  free_stack(&help_stack);
}

// calculate
double binary_func(type_t type, double num1, double num2) {
  setlocale(LC_ALL, "C");
  double result = 0.0;
  if (type == ADD)
    result = num1 + num2;
  else if (type == DIF)
    result = num1 - num2;
  else if (type == MUL)
    result = num1 * num2;
  else if (type == DIV)
    result = num1 / num2;
  else if (type == MOD)
    result = fmod(num1, num2);
  else if (type == POW)
    result = pow(num1, num2);
  return result;
}

double unary_func(type_t type, double num) {
  setlocale(LC_ALL, "C");
  double result = 0.0;
  if (type == SIN)
    result = sin(num);
  else if (type == COS)
    result = cos(num);
  else if (type == TAN)
    result = tan(num);
  else if (type == ACOS)
    result = acos(num);
  else if (type == ASIN)
    result = asin(num);
  else if (type == ATAN)
    result = atan(num);
  else if (type == LN)
    result = log(num);
  else if (type == LOG)
    result = log10(num);
  else if (type == SQRT)
    result = sqrt(num);
  return result;
}

int calculate(Node** notation, double x_value, double* result) {
  setlocale(LC_ALL, "C");
  // double eps = 1e-14;
  Node* number_stack = NULL;
  int status = OK;
  while ((*notation) != NULL && status == OK) {
    if ((*notation)->lex.type == NUM || (*notation)->lex.type == X) {
      if ((*notation)->lex.type == X) {
        (*notation)->lex.value = x_value;
        (*notation)->lex.type = NUM;
      }
      push(&number_stack, (*notation)->lex.type, (*notation)->lex.priority,
           (*notation)->lex.value);
      pop(notation);
    } else {
      if (is_func_binary((*notation)->lex.type)) {
        double num2 = number_stack->lex.value;
        pop(&number_stack);
        double num1 = number_stack->lex.value;
        pop(&number_stack);
        if (((*notation)->lex.type == MOD || (*notation)->lex.type == DIV) &&
            num2 == 0) {  // fabs(num2) < eps) {
          status = ERROR;
        } else {
          double answer = binary_func((*notation)->lex.type, num1, num2);
          pop(notation);
          push(&number_stack, NUM, 0, answer);
        }
      } else {
        double num1 = number_stack->lex.value;
        pop(&number_stack);
        if (((*notation)->lex.type == SQRT) &&
            (num1 < 0)) {  // fabs(num1) < eps
          status = ERROR;
        } else if (((*notation)->lex.type == LN ||
                    (*notation)->lex.type == LOG) &&
                   (num1 <= 0)) {
          status = ERROR;
        } else if (((*notation)->lex.type == ACOS ||
                    (*notation)->lex.type == ASIN) &&
                   (num1 > 1 || num1 < -1)) {
          status = ERROR;
        } else if (((*notation)->lex.type == TAN) && (cos(num1) == 0)) {
          status = ERROR;
        } else {
          double answer = unary_func((*notation)->lex.type, num1);
          pop(notation);
          push(&number_stack, NUM, 0, answer);
        }
      }
    }
  }
  if (number_stack != NULL) *result = number_stack->lex.value;
  free_stack(&number_stack);
  return status;
}
