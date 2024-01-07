#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../obj/image.h"
#include "../obj/interpreteur.h"
#include "../obj/stack.h"
/*
void executeAction(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    // Comparer les couleurs des blocs d'origine et de destination
    ColorDifference diff = compareColors(sourceBlock->color, destinationBlock->color);

    // Effectuer l'action appropriée en fonction de la différence de couleurs
    switch (diff)
    {
    case NO_COLOR_DIFFERENCE:
        // Aucune différence de couleur, ne rien faire
        break;

    case SAME_COLOR:
        // Les couleurs sont identiques, empiler la taille de l'ancien bloc
        push(&interpreter->stack, sourceBlock->width * sourceBlock->height);
        break;

    case COLOR_ONE_DARKER:
        // La couleur de destination est une fois plus foncée, dépiler
        pop(&interpreter->stack);
        break;

    case COLOR_TWO_DARKER:
        // La couleur de destination est deux fois plus foncée, dépiler et dépiler
        pop(&interpreter->stack);
        pop(&interpreter->stack);
        break;

        // Ajoutez les autres cas ici en fonction de la spécification

    default:
        // Cas par défaut, ne rien faire
        break;
    }
}
*/

void empile(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    push(&interpreter->stack, sourceBlock->width * sourceBlock->height);
}

void depile(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    pop(&interpreter->stack);
}

void plus(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    int a = pop(&interpreter->stack);
    int b = pop(&interpreter->stack);
    push(&interpreter->stack, a + b);
}

void moins(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    int a = pop(&interpreter->stack);
    int b = pop(&interpreter->stack);
    push(&interpreter->stack, b - a);
}

void fois(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    int a = pop(&interpreter->stack);
    int b = pop(&interpreter->stack);
    push(&interpreter->stack, a * b);
}

void divise(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    int a = pop(&interpreter->stack);
    int b = pop(&interpreter->stack);
    push(&interpreter->stack, b / a);
}

void reste(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    int a = pop(&interpreter->stack);
    int b = pop(&interpreter->stack);
    push(&interpreter->stack, b % a);
}

void non(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    int a = pop(&interpreter->stack);
    if (a == 0)
    {
        push(&interpreter->stack, 1);
    }
    else
    {
        push(&interpreter->stack, 0);
    }
}

void plusGrand(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    int a = pop(&interpreter->stack);
    int b = pop(&interpreter->stack);
    if (b > a)
    {
        push(&interpreter->stack, 1);
    }
    else
    {
        push(&interpreter->stack, 0);
    }
}

void direction(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    int a = pop(&interpreter->stack);
    if (a > 0)
    {
        if (interpreter->direction == 'e')
        {
            interpreter->direction = 's';
        }
        else if (interpreter->direction == 's')
        {
            interpreter->direction = 'o';
        }
        else if (interpreter->direction == 'o')
        {
            interpreter->direction = 'n';
        }
        else if (interpreter->direction == 'n')
        {
            interpreter->direction = 'e';
        }
    }
}

void bord(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    int a = pop(&interpreter->stack);
    if (a > 0)
    {
        if (interpreter->bord == 'b')
        {
            interpreter->bord = 't';
        }
        else if (interpreter->bord == 't')
        {
            interpreter->bord = 'b';
        }
    }
}

void duplique(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    int a = pop(&interpreter->stack);
    push(&interpreter->stack, a);
    push(&interpreter->stack, a);
}

void tourne(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    (void)sourceBlock;      // Indique au compilateur que sourceBlock est intentionnellement non utilisé
    (void)destinationBlock; // Indique au compilateur que destinationBlock est intentionnellement non utilisé
    int a = pop(&interpreter->stack);
    if (a > 0)
    {
        if (interpreter->direction == 'e')
        {
            interpreter->direction = 'o';
        }
        else if (interpreter->direction == 's')
        {
            interpreter->direction = 'n';
        }
        else if (interpreter->direction == 'o')
        {
            interpreter->direction = 'e';
        }
        else if (interpreter->direction == 'n')
        {
            interpreter->direction = 's';
        }
    }
}

/*
void executeProgram(Interpreter *interpreter, Image *image)
{
    // Initialiser l'interpréteur
    interpreter->x = 0;
    interpreter->y = 0;
    interpreter->direction = 'e';
    interpreter->bord = 'b';
    initializeStack(&interpreter->stack, 100);

    // Parcourir les blocs de l'image
    for (int i = 0; i < image->blockCount; i++)
    {
        // Check the definition of the Image struct
        typedef struct {
            // ...
            Block *blocks; // Make sure the 'blocks' member is defined
            // ...
        } Image;

        // ...

        // Remove the existing declaration of executeProgram
        // void executeProgram(Interpreter *interpreter, Image *image);

        // Corrected declaration of executeProgram
        void executeProgram(Interpreter *interpreter, Image *image);
        {
            // ...

            // Parcourir les blocs de l'image
            for (int i = 0; i < image->blockCount; i++)
            {
                // Fix the code by declaring the 'block' variable properly
                Block *block = &image->blocks[i];

                // Exécuter l'action appropriée
                executeAction(interpreter, block, block);
            }

            // ...
        }

        // Exécuter l'action appropriée
        executeAction(interpreter, block, block);
    }

    // Libérer la mémoire allouée pour la pile
    freeStack(&interpreter->stack);
}*/

// Lire un entier sur l'entrée standard et l'empiler
void inInt(Stack *stack)
{
    int num;
    scanf("%d", &num);
    push(stack, num);
}

// Lire un caractère sur l'entrée standard, obtenir son code ASCII et l'empiler
void inChar(Stack *stack)
{
    char ch;
    scanf(" %c", &ch);
    int asciiValue = (int)ch;
    push(stack, asciiValue);
}

// Dépiler un élément et l'afficher sur la sortie standard (pour les entiers)
void outInt(Stack *stack)
{
    int value = pop(stack);
    printf("%d\n", value);
}

// Dépiler un élément, obtenir le caractère correspondant au code ASCII et l'afficher
void outChar(Stack *stack)
{
    int asciiValue = pop(stack);
    char ch = (char)asciiValue;
    printf("%c\n", ch);
}

void executeAction(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock)
{
    printf("Executing action: Source Block Color: %d, Luminosity Difference: %d\n",
           sourceBlock->color, sourceBlock->luminosityDifference);

    // Comparer les couleurs des blocs d'origine et de destination
    ColorDifference diff = compareColors(sourceBlock->color, destinationBlock->color);

    printf("Color Difference: %d\n", diff);

    // Effectuer l'action appropriée en fonction de la différence de couleurs
    switch (diff)
    {
    case NO_COLOR_DIFFERENCE:
        switch (sourceBlock->luminosityDifference)
        {
        case NO_LUM_DIFFERENCE:
            // rien
            break;

        case LUM_ONE_DARKER:
            // La couleur de destination est une fois plus foncée, dépiler
            empile(interpreter, sourceBlock, destinationBlock);
            break;

        case LUM_TWO_DARKER:
            // La couleur de destination est deux fois plus foncée, dépiler et dépiler
            depile(interpreter, sourceBlock, destinationBlock);
            break;
        }
        break;

    case COLOR_ONE_DARKER:
        switch (sourceBlock->luminosityDifference)
        {
        case NO_LUM_DIFFERENCE:
            plus(interpreter, sourceBlock, destinationBlock);
            break;

        case LUM_ONE_DARKER:
            moins(interpreter, sourceBlock, destinationBlock);
            break;

        case LUM_TWO_DARKER:
            fois(interpreter, sourceBlock, destinationBlock);
            break;
        }
        break;

    case COLOR_TWO_DARKER:
        switch (sourceBlock->luminosityDifference)
        {
        case NO_LUM_DIFFERENCE:
            divise(interpreter, sourceBlock, destinationBlock);
            break;

        case LUM_ONE_DARKER:
            reste(interpreter, sourceBlock, destinationBlock);
            break;

        case LUM_TWO_DARKER:
            non(interpreter, sourceBlock, destinationBlock);
            break;
        }
        break;

    case COLOR_THREE_DARKER:
        switch (sourceBlock->luminosityDifference)
        {
        case NO_LUM_DIFFERENCE:
            plusGrand(interpreter, sourceBlock, destinationBlock);
            break;

        case LUM_ONE_DARKER:
            direction(interpreter, sourceBlock, destinationBlock);
            break;

        case LUM_TWO_DARKER:
            bord(interpreter, sourceBlock, destinationBlock);
            break;
        }
        break;

    case COLOR_FOUR_DARKER:
        switch (sourceBlock->luminosityDifference)
        {
        case NO_LUM_DIFFERENCE:
            duplique(interpreter, sourceBlock, destinationBlock);
            break;

        case LUM_ONE_DARKER:
            tourne(interpreter, sourceBlock, destinationBlock);
            break;

        case LUM_TWO_DARKER:
            inInt(&interpreter->stack);
            break;
        }
        break;

    case COLOR_FIVE_DARKER:
        switch (sourceBlock->luminosityDifference)
        {
        case NO_LUM_DIFFERENCE:
            inChar(&interpreter->stack);
            break;

        case LUM_ONE_DARKER:
            outInt(&interpreter->stack);
            break;

        case LUM_TWO_DARKER:
            outChar(&interpreter->stack);
            break;
        }
        break;

    default:
        printf("Unhandled color difference\n");
        break;
    }
    printf("Action executed\n");
}
/*
void parcourirImage(Image *image)
{
    // Initialiser l'interpréteur
    Interpreter interpreter;
    interpreter.x = 0;
    interpreter.y = 0;
    interpreter.direction = 'e';
    interpreter.bord = 'b';
    initializeStack(&interpreter.stack, 100);

    // Parcourir la liste chaînée de blocs de l'image
    BlockNode *current = image->blockList;
    while (current != NULL)
    {
        // Exécuter l'action appropriée
        executeAction(&interpreter, &current->block, &current->block);

        current = current->next;
    }

    // Libérer la mémoire allouée pour la pile
    freeStack(&interpreter.stack);
}
*/