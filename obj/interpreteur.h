#ifndef INTERPRETEUR_H
#define INTERPRETEUR_H

#include "image.h"
#include "stack.h"
#include "block.h"
// #include "block.h"

// Définir la structure Interpreter
typedef struct
{
  int x;          // Coordonnée x du pixel courant
  int y;          // Coordonnée y du pixel courant
  char direction; // Direction actuelle (est, sud, ouest, nord)
  char bord;      // Bord actuel (bâbord, tribord)
  Stack stack;    // Pile d'entiers
} Interpreter;

// Définir la structure Stack si elle est utilisée dans l'interpréteur

/*@requires interpreter != NULL && sourceBlock != NULL && destinationBlock != NULL;
      @assigns interpreter, sourceBlock, destinationBlock;
      @ensures postconditions;
    */
// void executeAction(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);
void executeAction(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// Ajoutez d'autres prototypes de fonctions liées à l'interpréteur si nécessaire

// Fonction pour parcourir l'image
void parcourirImage(Image *image);

// empile : on ajoute sur la pile la taille de l'ancien bloc
void empile(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// dépile : on supprime un élément de la pile (on ne fait rien avec)
void depile(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// plus : on dépile deux éléments et on empile leur somme
void plus(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// moins : on dépile deux éléments et on empile la différence entre le second et le premier
void moins(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// fois : on dépile deux éléments et on empile leur produit
void fois(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// divise : on dépile deux éléments et on empile le quotient du second par le premier
void divise(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// reste : on dépile deux éléments et on empile le reste de la division entière du second par le premier
void reste(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// non : on dépile un élément et on empile 1 si l'élément vaut 0 et 0 sinon
void non(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// plus grand : on dépile deux éléments et on empile 1 si le second est plus grand que le premier, 0 sinon
void plusGrand(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// direction : on dépile un élément et on fait tourner ce nombre de fois la direction dans le sens des aiguilles d'une montre
void direction(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// bord : on dépile un élément et on inverse ce nombre de fois le bord
void bord(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// duplique : on dépile un élément et on le rempile deux fois
void duplique(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// tourne : on dépile deux éléments et on va faire "tourner" la pile jusqu'à la profondeur donnée par le second, autant de fois que le premier élément. Faire tourner la pile une fois jusqu'à la profondeur d consiste à enlever l'élément au sommet de la pile et à le remettre à la profondeur d en faisant remonter les autres.
void tourne(Interpreter *interpreter, Block *sourceBlock, Block *destinationBlock);

// Lire un entier sur l'entrée standard et l'empiler
void inInt(Stack *stack);

// Lire un caractère sur l'entrée standard, obtenir son code ASCII et l'empiler
void inChar(Stack *stack);

// Dépiler un élément et l'afficher sur la sortie standard (pour les entiers)
void outInt(Stack *stack);

// Dépiler un élément, obtenir le caractère correspondant au code ASCII et l'afficher
void outChar(Stack *stack);

#endif /* INTERPRETEUR_H */
