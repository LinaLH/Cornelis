#include "../obj/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialiser la pile
void initializeStack(Stack *stack, int capacity)
{
    stack->elements = malloc(capacity * sizeof(int));
    if (stack->elements == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de la pile.\n");
        exit(1);
    }
    stack->size = 0; // La pile est vide initialement
    stack->capacity = capacity;
}

// Vérifier si la pile est vide
int isEmpty(Stack *stack)
{
    return stack->size == 0;
}

// Vérifier si la pile est pleine
int isFull(Stack *stack)
{
    return stack->size == stack->capacity;
}

// Ajouter un élément à la pile (push)
void push(Stack *stack, int value)
{
    if (isFull(stack))
    {
        fprintf(stderr, "Erreur : la pile est pleine.\n");
        exit(1);
    }
    stack->elements[stack->size++] = value;
}

// Retirer un élément de la pile (pop)
int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        fprintf(stderr, "Erreur : la pile est vide.\n");
        exit(1);
    }
    return stack->elements[--stack->size];
}

// Libérer la mémoire allouée pour la pile
void freeStack(Stack *stack)
{
    free(stack->elements);
}

// Fonction pour empiler le code ASCII d'un caractère sur la pile
void pushCharASCII(Stack *stack, char ch)
{
    push(stack, (int)ch);
}

// Fonction pour dépiler et afficher un entier
void popAndPrintNumber(Stack *stack)
{
    if (isEmpty(stack))
    {
        fprintf(stderr, "Erreur : la pile est vide.\n");
        exit(1);
    }
    printf("%d\n", pop(stack));
}

// Fonction pour dépiler et afficher un caractère en utilisant son code ASCII
void popAndPrintChar(Stack *stack)
{
    if (isEmpty(stack))
    {
        fprintf(stderr, "Erreur : la pile est vide.\n");
        exit(1);
    }
    printf("%c\n", (char)pop(stack));
}