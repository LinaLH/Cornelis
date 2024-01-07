#include "../obj/image.h"
#include "../obj/interpreteur.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isSameColor(Pixel pixel1, Pixel pixel2)
{
    return pixel1.red == pixel2.red && pixel1.green == pixel2.green && pixel1.blue == pixel2.blue;
}

ColorDifference compareColors(Pixel color1, Pixel color2)
{
    if (isSameColor(color1, color2))
    {
        return SAME_COLOR;
    }

    // Ajoutez ici les autres cas de comparaison en fonction de vos règles
    // par exemple, la différence de luminosité, etc.

    return NO_COLOR_DIFFERENCE;
}

int normalizeLuminosity(int luminosity)
{
    if (luminosity < 85)
    {
        return 0;
    }
    else if (luminosity < 170)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

LuminosityDifference compareLuminosities(int lum1, int lum2)
{
    int normalizedLum1 = normalizeLuminosity(lum1);
    int normalizedLum2 = normalizeLuminosity(lum2);

    if (normalizedLum1 == normalizedLum2)
    {
        return NO_LUM_DIFFERENCE;
    }
    else if (normalizedLum1 == normalizedLum2 + 1 || normalizedLum1 == normalizedLum2 - 2)
    {
        return LUM_ONE_DARKER;
    }
    else
    {
        return LUM_TWO_DARKER;
    }
}

Pixel *getPixel(Image *image, int x, int y)
{
    return &image->pixels[y][x];
}

Pixel getAdjacentPixel(Image *image, int x, int y, enum Direction direction)
{
    switch (direction)
    {
    case EAST:
        return *getPixel(image, x + 1, y);
    case SOUTH:
        return *getPixel(image, x, y + 1);
    case WEST:
        return *getPixel(image, x - 1, y);
    case NORTH:
        return *getPixel(image, x, y - 1);
    default:
        return *getPixel(image, x, y);
    }
}
/*
BlockNode *detectBlocks(Image *image)
{
    int width = image->width;
    int height = image->height;
    Pixel **pixels = image->pixels;

    BlockNode *head = NULL; // Tête de la liste chaînée
    BlockNode *current = NULL;

    for (int y = 0; y < height; y++)
    {
        Pixel *previousPixel = NULL;
        for (int x = 0; x < width; x++)
        {
            Pixel pixel = pixels[y][x];
            if (previousPixel == NULL || !isSameColor(pixel, *previousPixel))
            {
                // Créer un nouveau nœud de bloc
                BlockNode *newNode = malloc(sizeof(BlockNode));
                if (!newNode)
                {
                    fprintf(stderr, "Erreur lors de l'allocation de mémoire pour un bloc.\n");
                    // Libérer la mémoire des blocs déjà créés
                    while (head != NULL)
                    {
                        BlockNode *temp = head;
                        head = head->next;
                        free(temp);
                    }
                    return NULL;
                }

                // Initialiser le bloc dans le nœud
                newNode->block.color = pixel;
                newNode->block.x = x;
                newNode->block.y = y;
                newNode->block.width = 1;
                newNode->block.height = 1;

                newNode->next = NULL;

                // Ajouter le nœud à la liste chaînée
                if (head == NULL)
                {
                    head = newNode;
                    current = head;
                }
                else
                {
                    current->next = newNode;
                    current = newNode;
                }
            }
            else
            {
                // Mettre à jour le bloc existant
                current->block.width++;
            }

            previousPixel = &pixel;
        }
    }

    // Afficher des messages de débogage pour chaque bloc détecté
    current = head;
    printf("Number of Blocks: %d\n", image->blockCount);
    while (current != NULL)
    {
        printf("Block - Color: (%d, %d, %d), Position: (%d, %d), Size: %d x %d\n",
               current->block.color.red, current->block.color.green, current->block.color.blue,
               current->block.x, current->block.y,
               current->block.width, current->block.height);
        current = current->next;
    }

    return head; // Retourner la tête de la liste chaînée
}
*/
/*
void detectBlocks(Image *image, int x, int y, Pixel initColor, int **visited, int *blockCount)
{
    if (x < 0 || x >= image->width || y < 0 || y >= image->height || visited[x][y] != 0)
    {
        // La case est hors des limites ou déjà visitée
        return;
    }

    visited[x][y] = 1; // Marquer la case comme visitée

    // Stocker le bloc détecté dans une structure de données appropriée
    // Ne compter le bloc que s'il n'a pas encore été ajouté à la liste
    // ...

    // Exploration en profondeur des pixels adjacents
    detectBlocks(image, (x + 1) % image->width, y, initColor, visited, blockCount);
    detectBlocks(image, (x - 1 + image->width) % image->width, y, initColor, visited, blockCount);
    detectBlocks(image, x, (y + 1) % image->height, initColor, visited, blockCount);
    detectBlocks(image, x, (y - 1 + image->height) % image->height, initColor, visited, blockCount);
}
*/

/*
// Fonction pour ajouter un bloc à une liste
void addBlockToList(Image *image, int x, int y, int width, int height, Pixel color)
{
    // Ajoutez votre logique pour stocker le bloc, par exemple, imprimer les informations
    printf("Block detected: x=%d, y=%d, width=%d, height=%d, color=(%d, %d, %d)\n",
           x, y, width, height, color.red, color.green, color.blue);
}*/
/*
// Fonction pour ajouter un bloc à la liste chaînée
void addBlockToList(Image *image, int x, int y, int width, int height, Pixel color)
{
    BlockNode *newNode = malloc(sizeof(BlockNode));
    newNode->block.x = x;
    newNode->block.y = y;
    newNode->block.width = width;
    newNode->block.height = height;
    newNode->block.color = color;
    newNode->next = image->blockList;
    image->blockList = newNode;
    image->blockCount++;
}*/
/*
void addBlockToList(int x, int y, int width, int height, Pixel color)
{
    // Ajoutez votre logique pour stocker le bloc, par exemple, imprimer les informations
    // printf("Block detected: x=%d, y=%d, width=%d, height=%d, color=(%d, %d, %d)\n",
    //       x, y, width, height, color.red, color.green, color.blue);
}*/
/* version envoyée à gpt 4
// Fonction pour détecter un bloc en utilisant DFS
void detectBlocks(Image *image)
{
   // Étape 1 : Allouer et initialiser la matrice visited
   int **visited = malloc(image->width * sizeof(int *));
   for (int i = 0; i < image->width; i++)
   {
       visited[i] = malloc(image->height * sizeof(int));
       for (int j = 0; j < image->height; j++)
       {
           visited[i][j] = 0;
       }
   }
   // Étape 2 : Parcourir chaque pixel de l'image
   for (int i = 0; i < image->width; i++)
   {
       for (int j = 0; j < image->height; j++)
       {
           if (!visited[i][j])
           {
               // Étape 3 : Afficher les coordonnées du pixel en cours
               printf("Processing pixel at [%d][%d]\n", i, j);

               // Étape 4 : Accéder à la couleur du pixel
               if (i >= 0 && i < image->width && j >= 0 && j < image->height)
               {
                   Pixel color = image->pixels[i][j];
                   printf("RGB values at [%d][%d]: %d, %d, %d\n", i, j, color.red, color.green, color.blue);

                   // Étape 5 : Marquer le pixel comme visité
                   visited[i][j] = 1;

                   // Étape 6 : Ajouter le pixel au bloc
                   addBlockToList(i, j, 1, 1, color);

                   // Étape 7 : Balayer horizontalement
                   for (int k = i + 1; k < image->width && image->pixels[k][j].red == color.red &&
                                       image->pixels[k][j].green == color.green && image->pixels[k][j].blue == color.blue;
                        k++)
                   {
                       visited[k][j] = 1;
                       // Ajouter le pixel au bloc
                       addBlockToList(k, j, 1, 1, color);
                   }

                   // Étape 8 : Balayer verticalement
                   for (int k = j + 1; k < image->height && image->pixels[i][k].red == color.red &&
                                       image->pixels[i][k].green == color.green && image->pixels[i][k].blue == color.blue;
                        k++)
                   {
                       visited[i][k] = 1;
                       // Ajouter le pixel au bloc
                       addBlockToList(i, k, 1, 1, color);
                   }
               }
               else
               {
                   printf("Invalid indices: i=%d, j=%d\n", i, j);
               }
           }
       }

       // Étape 9 : Libérer la mémoire de visited
       for (int i = 0; i < image->width; i++)
       {
           free(visited[i]);
       }
       free(visited);
   }
}*/

int shouldBeAddedToBlock(Block *block, int x, int y, Pixel color)
{
    // Vérifier si la couleur est la même
    if (!isSameColor(block->color, color))
    {
        return 0; // Equivalent à 'false'
    }

    // Vérifier la proximité (par exemple, le pixel est adjacent au bloc)
    // Cette partie dépend de votre logique de formation de bloc
    if (x >= block->x && x <= block->x + block->width &&
        y >= block->y && y <= block->y + block->height)
    {
        return 1; // Equivalent à 'true'
    }

    return 0; // Equivalent à 'false'
}

// Met à jour les dimensions d'un bloc existant pour inclure un nouveau pixel
void updateBlock(Block *block, int x, int y)
{
    // Étendre les dimensions du bloc si nécessaire
    // Cette logique dépend de comment vous voulez que votre bloc grandisse
    if (x < block->x)
    {
        block->width += (block->x - x);
        block->x = x;
    }
    else if (x > block->x + block->width)
    {
        block->width = x - block->x;
    }

    if (y < block->y)
    {
        block->height += (block->y - y);
        block->y = y;
    }
    else if (y > block->y + block->height)
    {
        block->height = y - block->y;
    }
}

// Initialise un nouveau bloc avec un pixel donné
void initializeNewBlock(Block *block, int x, int y, Pixel color)
{
    block->x = x;
    block->y = y;
    block->width = 1;
    block->height = 1;
    block->color = color;
}

void addPixelToBlock(Image *image, int x, int y, Pixel color)
{
    // Chercher un bloc existant à mettre à jour
    BlockNode *current = image->blockList;
    while (current != NULL)
    {
        // Vérifiez si le pixel peut être ajouté à un bloc existant
        // Cette logique dépend de vos critères pour regrouper les pixels dans un bloc
        if (shouldBeAddedToBlock(&current->block, x, y, color))
        {
            updateBlock(&current->block, x, y);
            return;
        }
        current = current->next;
    }

    // Aucun bloc existant trouvé, créer un nouveau bloc
    BlockNode *newNode = malloc(sizeof(BlockNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }
    initializeNewBlock(&newNode->block, x, y, color);
    newNode->next = image->blockList;
    image->blockList = newNode;
    image->blockCount++;
}

// Vous devez implémenter shouldBeAddedToBlock, updateBlock et initializeNewBlock
// en fonction de la logique spécifique de votre projet.
/**/
void detectBlocks(Image *image)
{
    // Parcourir chaque pixel de l'image
    for (int i = 0; i < image->width; i++)
    {
        for (int j = 0; j < image->height; j++)
        {
            Pixel currentPixel = image->pixels[i][j];

            // Utilisez addPixelToBlock pour ajouter le pixel à un bloc existant
            // ou créez un nouveau bloc si nécessaire
            addPixelToBlock(image, i, j, currentPixel);
        }
    }
}

/*
// correction de gpt4
void detectBlocks(Image *image)
{
    // Étape 1 : Allouer et initialiser la matrice visited
    int **visited = malloc(image->width * sizeof(int *));
    for (int i = 0; i < image->width; i++)
    {
        visited[i] = malloc(image->height * sizeof(int));
        for (int j = 0; j < image->height; j++)
        {
            visited[i][j] = 0;
        }
    }

    // Étape 2 : Parcourir chaque pixel de l'image
    for (int i = 0; i < image->width; i++)
    {
        for (int j = 0; j < image->height; j++)
        {
            if (!visited[i][j])
            {
                // Étape 3 : Afficher les coordonnées du pixel en cours
                printf("Processing pixel at [%d][%d]\n", i, j);

                // Étape 4 : Accéder à la couleur du pixel
                Pixel color = image->pixels[i][j];
                printf("RGB values at [%d][%d]: %d, %d, %d\n", i, j, color.red, color.green, color.blue);

                // Étape 5 : Marquer le pixel comme visité
                visited[i][j] = 1;

                // Étape 6 : Ajouter le pixel au bloc
                addBlockToList(i, j, 1, 1, color);

                // Étape 7 : Balayer horizontalement
                for (int k = i + 1; k < image->width && image->pixels[k][j].red == color.red &&
                                    image->pixels[k][j].green == color.green && image->pixels[k][j].blue == color.blue;
                     k++)
                {
                    visited[k][j] = 1;
                    // Ajouter le pixel au bloc
                    addBlockToList(k, j, 1, 1, color);
                }

                // Étape 8 : Balayer verticalement
                for (int k = j + 1; k < image->height && image->pixels[i][k].red == color.red &&
                                    image->pixels[i][k].green == color.green && image->pixels[i][k].blue == color.blue;
                     k++)
                {
                    visited[i][k] = 1;
                    // Ajouter le pixel au bloc
                    addBlockToList(i, k, 1, 1, color);
                }
            }
        }
    }

    // Étape 9 : Libérer la mémoire de visited
    for (int i = 0; i < image->width; i++)
    {
        free(visited[i]);
    }
    free(visited);
}*/

/*
void detectBlock(Image *image, int x, int y, Pixel targetColor, int (*visited)[image->height])
{
    printf("Entering detectBlock at (%d, %d)\n", x, y);

    // Assurer que les indices sont dans les limites de l'image
    if (x < 0 || x >= image->width || y < 0 || y >= image->height || visited[x][y] != 0)
    {
        printf("Exiting detectBlock due to invalid indices or visited pixel\n");
        return; // La case est hors des limites ou déjà visitée
    }

    visited[x][y] = 1; // Marquer la case comme visitée

    if (image->pixels[x][y].red == targetColor.red &&
        image->pixels[x][y].green == targetColor.green &&
        image->pixels[x][y].blue == targetColor.blue)
    {
        // Le pixel a la couleur cible, donc il fait partie du bloc
        // Ajouter le bloc à la liste
        addBlockToList(image, x, y, 1, 1, targetColor);

        printf("Pixel at (%d, %d) has the target color\n", x, y);

        // Explorer le reste du bloc
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                {
                    printf("Exploring neighbor at (%d, %d)\n", (x + i + image->width) % image->width, (y + j + image->height) % image->height);
                    detectBlock(image, (x + i + image->width) % image->width, (y + j + image->height) % image->height, targetColor, visited);
                }
            }
        }
    }
    printf("Exiting detectBlock normally\n");
}*/

/*
int detectAllBlocks(Image *image)
{
    int **visited = malloc(image->width * sizeof(int *));
    for (int i = 0; i < image->width; i++)
    {
        visited[i] = malloc(image->height * sizeof(int));
        for (int j = 0; j < image->height; j++)
        {
            visited[i][j] = 0;
        }
    }

    int totalBlockCount = 0;

    for (int i = 0; i < image->width; i++)
    {
        for (int j = 0; j < image->height; j++)
        {
            if (visited[i][j] == 0)
            {
                // Détecter les blocs non visités
                int blockCount = 0;
                detectBlocks(image, i, j, image->pixels[i][j], visited, &blockCount);

                if (blockCount > 0)
                {
                    // Incrémenter le nombre total de blocs
                    totalBlockCount++;
                }
            }
        }
    }

    // Libérer la mémoire allouée pour le tableau visited
    for (int i = 0; i < image->width; i++)
    {
        free(visited[i]);
    }
    free(visited);

    return totalBlockCount;
}
*/
/*
void detectAllBlocks(Image *image)
{

    int visited[image->width][image->height];

    for (int i = 0; i < image->width; i++)
    {
        for (int j = 0; j < image->height; j++)
        {
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i < image->width; i++)
    {
        for (int j = 0; j < image->height; j++)
        {
            if (visited[i][j] == 0)
            {
                // Détecter les blocs non visités
                detectBlock(image, i, j, image->pixels[i][j], visited);
            }
        }
    }
}
*/
/*
// Fonction pour détecter tous les blocs dans une image
void detectAllBlocks(Image *image)
{
    for (int i = 0; i < image->width; i++)
    {
        for (int j = 0; j < image->height; j++)
        {
            Pixel currentColor = image->pixels[i][j];
            if (currentColor.red != 0 || currentColor.green != 0 || currentColor.blue != 0)
            {
                // Détecter un nouveau bloc à partir de ce pixel
                detectBlock(image, i, j, currentColor);
            }
        }
    }
}*/

// Ajouter une fonction pour libérer la mémoire de la liste chaînée
void freeBlockList(BlockNode *head)
{
    while (head != NULL)
    {
        BlockNode *temp = head;
        head = head->next;
        free(temp);
    }
}

Image readPPM(char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", filename);
        Image emptyImage = {NULL, 0, 0, NULL, 0};
        return emptyImage;
    }

    // Lire l'en-tête PPM
    char magic[3];
    if (fscanf(file, "%2s", magic) != 1 || strcmp(magic, "P6") != 0)
    {
        fclose(file);
        fprintf(stderr, "Le fichier %s n'est pas au format P6 (image binaire).\n", filename);
        Image emptyImage = {NULL, 0, 0, NULL, 0};
        return emptyImage;
    }

    int width, height, maxColor;
    if (fscanf(file, "%d %d %d", &width, &height, &maxColor) != 3)
    {
        fclose(file);
        fprintf(stderr, "Erreur lors de la lecture des dimensions de l'image.\n");
        Image emptyImage = {NULL, 0, 0, NULL, 0};
        return emptyImage;
    }

    int newline = fgetc(file);
    if (newline != '\n')
    {
        fclose(file);
        fprintf(stderr, "Caractère de retour à la ligne manquant après les dimensions de l'image.\n");
        Image emptyImage = {NULL, 0, 0, NULL, 0};
        return emptyImage;
    }

    // Allouer de la mémoire pour les pixels
    Pixel **pixels = malloc(height * sizeof(Pixel *));
    if (!pixels)
    {
        fclose(file);
        fprintf(stderr, "Erreur d'allocation de mémoire pour les lignes de pixels.\n");
        Image emptyImage = {NULL, 0, 0, NULL, 0};
        return emptyImage;
    }

    for (int i = 0; i < height; i++)
    {
        pixels[i] = malloc(width * sizeof(Pixel));
        if (!pixels[i])
        {
            fclose(file);
            fprintf(stderr, "Erreur d'allocation de mémoire pour les pixels de la ligne %d.\n", i);

            // Libérer la mémoire déjà allouée
            for (int j = 0; j < i; j++)
                free(pixels[j]);
            free(pixels);

            Image emptyImage = {NULL, 0, 0, NULL, 0};
            return emptyImage;
        }

        fread(pixels[i], sizeof(Pixel), width, file);
    }

    fclose(file);

    // Afficher des informations pour débogage
    printf("Successfully read the PPM image.\n");
    printf("Width: %d\n", width);
    printf("Height: %d\n", height);
    printf("Max color value: %d\n", maxColor);

    Image image = {pixels, width, height, NULL, 0};
    return image;
}

/*
void freeImage(Image *image)
{
    printf("Fonction free image");
    if (image != NULL)
    {
        // Libérer la mémoire allouée pour les pixels
        for (int i = 0; i < image->height; i++)
        {
            if (image->pixels[i] != NULL)
            {
                printf("Freeing pixels of row %d\n", i);
                free(image->pixels[i]);
            }
            else
            {
                fprintf(stderr, "Error: Trying to free a NULL pointer at row %d\n", i);
            }
        }
        free(image->pixels);
    }
    else
    {
        fprintf(stderr, "Error: Trying to free a NULL image pointer\n");
    }
}
*/
void freeImage(Image *image)
{
    for (int i = 0; i < image->width; i++)
    {
        free(image->pixels[i]);
    }
    free(image->pixels);

    // Libérer la liste chaînée de blocs
    BlockNode *current = image->blockList;
    while (current != NULL)
    {
        BlockNode *next = current->next;
        free(current);
        current = next;
    }

    image->blockList = NULL;
    image->blockCount = 0;
}
/*
int numBlocks(Image *image)
{
    int width = image->width;
    int height = image->height;
    Pixel **pixels = image->pixels;

    int blockCount = 0;
    for (int y = 0; y < height; y++)
    {
        Pixel *previousPixel = NULL;
        for (int x = 0; x < width; x++)
        {
            Pixel pixel = pixels[y][x];
            if (previousPixel == NULL || !isSameColor(pixel, *previousPixel))
            {
                blockCount++;
            }

            previousPixel = &pixel;
        }
    }

    return blockCount;
}


BlockNode *createBlockList(Image *image)
{
    // Vérifier si l'image et les pixels sont valides
    if (image == NULL || image->pixels == NULL)
    {
        fprintf(stderr, "Image ou pixels non valides.\n");
        return NULL;
    }

    // Vérifier si la largeur et la hauteur de l'image sont valides
    int width = image->width;
    int height = image->height;

    if (width <= 0 || height <= 0)
    {
        fprintf(stderr, "Largeur ou hauteur d'image non valides.\n");
        return NULL;
    }

    Pixel **pixels = image->pixels;

    BlockNode *head = NULL; // Tête de la liste chaînée
    BlockNode *current = NULL;

    for (int y = 0; y < height; y++)
    {
        Pixel *previousPixel = NULL;
        Pixel *currentPixelRow = pixels[y];

        // Vérifier si la ligne de pixels est valide
        if (currentPixelRow == NULL)
        {
            fprintf(stderr, "Ligne de pixels non valide. y: %d\n", y);
            return NULL;
        }

        for (int x = 0; x < width; x++)
        {
            // Vérifier si le pointeur currentPixel est nul ou si l'index dépasse la largeur de l'image
            if (currentPixelRow == NULL || x >= width)
            {
                fprintf(stderr, "Pointeur currentPixel nul ou index x hors limites. y: %d, x: %d\n", y, x);
                return NULL;
            }

            Pixel pixel = *currentPixelRow;
            for (int y = 0; y < height; y++)
            {
                Pixel *previousPixel = NULL;
                Pixel *currentPixelRow = pixels[y];

                // Vérifier si la ligne de pixels est valide
                if (currentPixelRow == NULL)
                {
                    fprintf(stderr, "Ligne de pixels non valide. y: %d\n", y);
                    return NULL;
                }

                for (int x = 0; x < width; x++)
                {
                    // Vérifier si le pointeur currentPixel est nul ou si l'index dépasse la largeur de l'image
                    if (currentPixelRow == NULL || x >= width)
                    {
                        fprintf(stderr, "Pointeur currentPixel nul ou index x hors limites. y: %d, x: %d\n", y, x);
                        return NULL;
                    }

                    Pixel pixel = *currentPixelRow;
                    // Créer un nouveau nœud de bloc
                    BlockNode *newNode = malloc(sizeof(BlockNode));
                    if (!newNode)
                    {
                        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour un bloc.\n");
                        // Libérer la mémoire des blocs déjà créés
                        while (head != NULL)
                        {
                            BlockNode *temp = head;
                            head = head->next;
                            free(temp);
                        }
                        return NULL;
                    }

                    // Initialiser le bloc dans le nœud
                    newNode->block.color = pixel;
                    newNode->block.x = x;
                    newNode->block.y = y;
                    newNode->block.width = 1;
                    newNode->block.height = 1;

                    newNode->next = NULL;

                    // Ajouter le nœud à la liste chaînée
                    if (head == NULL)
                    {
                        head = newNode;
                        current = head;
                    }
                    else
                    {
                        current->next = newNode;
                        current = newNode;
                    }

                    // Mettre à jour le bloc existant
                    if (previousPixel != NULL && !isSameColor(pixel, *previousPixel))
                    {
                        // Vérifier si la largeur du bloc existant est positive avant de mettre à jour
                        if (current->block.width > 0)
                        {
                            current->block.width++;
                        }
                        else
                        {
                            // Si la largeur est nulle, initialiser un nouveau bloc
                            current->block.color = pixel;
                            current->block.x = x;
                            current->block.y = y;
                            current->block.width = 1;
                            current->block.height = 1;
                        }
                    }

                    previousPixel = &pixel;
                    currentPixelRow++;
                }
            }

            // Afficher des messages de débogage pour chaque bloc détecté
            current = head;
            printf("Nombre de blocs : %d\n", image->blockCount);

            while (current != NULL)
            {
                printf("Bloc - Couleur : (%d, %d, %d), Position : (%d, %d), Taille : %d x %d\n",
                       current->block.color.red, current->block.color.green, current->block.color.blue,
                       current->block.x, current->block.y,
                       current->block.width, current->block.height);
                current = current->next;
            }

            // Retourner la tête de la liste des blocs créée
            return head;
        }
    }
}

int countBlocks(BlockNode *blockList)
{
    int count = 0;
    BlockNode *current = blockList;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}
*/