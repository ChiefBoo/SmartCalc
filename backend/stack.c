#include "stack.h"
//#include <stdio.h> // remove before deadline

void push(Node **head, type_t type, int priority, double value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node) {
        new_node->lex.priority = priority;
        new_node->lex.type = type;
        new_node->lex.value = value;
        new_node->next = *head;
        *head = new_node;
    }
}

void pop(Node **head) {
    Node *tmp = NULL;
    if (*head) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

Node peek(Node **head) {
    Node* tmp = *head;
    if (*head) {
        tmp = *head;
    }
    return *tmp;
}

void free_stack(Node **head) {
    if (*head) {
        Node *tmp = *head;
        while(tmp) {
            *head = (*head)->next;
            free(tmp);
            tmp = *head;
        }
    }
}

// void print_stack(Node *head) {   // remove before deadline
//     Node *tmp = head;
//     while (tmp) {
//         printf("%d %d %f\n", tmp->lex.priority, tmp->lex.type, tmp->lex.value);
//         tmp = (tmp)->next;
//     }
// }