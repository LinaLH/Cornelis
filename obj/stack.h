#ifndef STACK_H
#define STACK_H

// Définir la structure Stack
typedef struct
{
  int top;
  int *elements;
  int size;
  int capacity;
  // Ajoutez d'autres attributs nécessaires pour la pile
} Stack;

void initializeStack(Stack *stack, int capacity);

int isEmpty(Stack *stack);

int isFull(Stack *stack);

// Prototypes des fonctions pour la gestion de la pile
void push(Stack *stack, int value)
    /*@requires stack != NULL && stack->size < stack->capacity;
      @assigns stack;
      @ensures \result != NULL;
    */
    ;
int pop(Stack *stack)
    /*@requires stack != NULL && stack->size > 0;
      @assigns stack;
      @ensures \result is the top value of the stack before the call;
    */
    ;
// Ajoutez d'autres prototypes de fonctions liées à la pile si nécessaire

void freeStack(Stack *stack);

// Fonction pour empiler le code ASCII d'un caractère sur la pile
void pushCharASCII(Stack *stack, char ch);

// Fonction pour dépiler et afficher un entier
void popAndPrintNumber(Stack *stack);

// Fonction pour dépiler et afficher un caractère en utilisant son code ASCII
void popAndPrintChar(Stack *stack);

#endif /* STACK_H */
