#ifndef SRC_BACKEND_STACK_H
#define SRC_BACKEND_STACK_H

#include <stdlib.h>



typedef enum type_t {
  NUM = 1,
  X = 2,
  ADD = 3,
  DIF = 4,
  MUL = 5,
  DIV = 6,
  MOD = 7,
  POW = 8,
  COS = 9,
  SIN = 10,
  TAN = 11,
  ACOS = 12,
  ASIN = 13,
  ATAN = 14,
  SQRT = 15,
  LN = 16,
  LOG = 17,
  BRACK_O = 18,
  BRACK_C = 19,
} type_t;


typedef struct lexeme{
  type_t type;
  int priority;
  double value;
} Lexeme;

typedef struct node{
  Lexeme lex;
  struct node* next;
} Node;

void push(Node **head, type_t type, int priority, double value);
void pop(Node **head);
Node peek(Node **head);
void free_stack(Node **head);

//void print_stack(Node *head); // remove before deadline


#endif  // SRC_BACKEND_STACK_H
