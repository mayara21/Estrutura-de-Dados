// Código para uma pilha de operações

#include <stdio.h>
#include <stdlib.h>

#define LINE_MAX_SIZE 1024

typedef struct _operators {
    char op;
    struct _operators *next;
} operators;

typedef struct _factors {
    int value;
    struct _factors *next;
} factors;


operators* push_operator(operators *stack, char op) {
    operators *new;
    new = (operators *) malloc(sizeof(operators));

    new->op = op;
    new->next = stack;

    return new;
}

char pop_operator(operators **stack) {
    char c;
    operators *new;

    c = (*stack)->op;
    new = *stack;

    (*stack) = (*stack)->next;

    free(new);
    return c;
}

factors* push_factor(factors *stack, int value) {
    factors *new;
    new = (factors *) malloc(sizeof(factors));

    new->value = value;
    new->next = stack;

    return new;
}

int pop_factor(factors **stack) {
    int value;
    factors *new;

    value = (*stack)->value;
    new = *stack;

    (*stack) = (*stack)->next;

    free(new);
    return value;
}

int main() {
    char line[LINE_MAX_SIZE], c, operator;
    int i, x, n, result, value1, value2;
    operators *operators_stack;
    factors *factors_stack;

    operators_stack = NULL;
    factors_stack = NULL;

    scanf("%[^\n]", line);
    i = 0;
    while (sscanf(&line[i], "%c", &c) > 0) {
        if (c >= '0' && c <= '9') {
            sscanf(&line[i], "%d %n", &x, &n);
            factors_stack = push_factor(factors_stack, x);
            i += n;
        }
        else {
            if (c == '+' || c == '-' || c == '*' || c == '/') {
                operators_stack = push_operator(operators_stack, c);
            }
            if (c == ')') {
                value1 = pop_factor(&factors_stack);
                value2 = pop_factor(&factors_stack);
                operator = pop_operator(&operators_stack);

                switch(operator) {
                    case '+':
                        result = value2 + value1;
                        break;
                    case '-':
                        result = value2 - value1;
                        break;
                    case '*':
                        result = value2 * value1;
                        break;
                    case '/':
                        result = value2 / value1;
                        break;
                }

                factors_stack = push_factor(factors_stack, result);
            }
            i++;
        }
    }
    printf("%d\n", pop_factor(&factors_stack));
    return 0;
}
