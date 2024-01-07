#include <stdio.h>
#include <stdlib.h>
#include "../obj/image.h"
#include "../obj/interpreteur.h"
#include "../obj/stack.h"

#define MAX_PATH_LENGTH 256
// SANS LISTE CHAINEE
/*
int main(int argc, char *argv[])
{
    // Vérifier le nombre d'arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <image_file.ppm>\n", argv[0]);
        return 1;
    }

    char *imageFileName = argv[1];

    // Ajouter le chemin du dossier "cornelis" au nom du fichier
    char imagePath[MAX_PATH_LENGTH];
    snprintf(imagePath, sizeof(imagePath), "cornelis/%s", imageFileName);

    // Lire l'image depuis le fichier PPM
    Image image = readPPM(imagePath);

    // Vérifier si la lecture de l'image a échoué
    if (image.pixels == NULL)
    {
        fprintf(stderr, "Erreur lors de la lecture de l'image.\n");
        // Libération de la mémoire en cas d'échec
        freeImage(&image);
        return 1;
    }

    size_t pixelSize = sizeof(Pixel);
    size_t imageSize = sizeof(Image);
    size_t pixelsArraySize = image.width * image.height * pixelSize;

    printf("Size of Pixel structure: %zu bytes\n", pixelSize);
    printf("Size of Image structure: %zu bytes\n", imageSize);
    printf("Size of pixels array: %zu bytes\n", pixelsArraySize);

    printf("Image width * Image height: %d\n", image.width * image.height);

    for (int i = 0; i < image.width * image.height; ++i)
    {
        printf("Itération %d\n", i);

        // Vérifier si l'index est valide
        if (i >= 0 && i < image.width * image.height)
        {
            // Vérifier si le pointeur est non nul avant d'accéder aux valeurs
            if (image.pixels[i] != NULL)
            {
                printf("Pixel %d: Red=%d, Green=%d, Blue=%d\n", i, image.pixels[i]->red, image.pixels[i]->green, image.pixels[i]->blue);
            }
            else
            {
                fprintf(stderr, "Pointeur de pixel nul à l'itération %d.\n", i);
                // Gestion de l'erreur, libération de la mémoire, etc.
                freeImage(&image);
                return 1;
            }
        }
        else
        {
            fprintf(stderr, "Index d'itération hors limites : %d.\n", i);
            // Gestion de l'erreur, libération de la mémoire, etc.
            freeImage(&image);
            return 1;
        }
    }

    // Libération du tableau de pixels
    free(image.pixels);

    Interpreter *interpreter = malloc(sizeof(Interpreter));
    // Initialiser l'interpréteur
    interpreter->x = 0;
    interpreter->y = 0;
    interpreter->direction = 'e';
    interpreter->bord = 'b';
    initializeStack(&interpreter->stack, 100);

    // Détecter les blocs dans l'image
    Block *blocks = detectBlocks(&image);

    // Vérifier si la détection des blocs a échoué
    if (blocks == NULL)
    {
        fprintf(stderr, "Erreur lors de la détection des blocs.\n");
        freeImage(&image);
        return 1;
    }

    int blockCount = numBlocks(&image);

    // Exécuter les actions pour chaque paire de blocs
    for (int i = 0; i < blockCount; i += 2)
    {
        executeAction(interpreter, &blocks[i], &blocks[i + 1]);
    }

    // Libérer la mémoire
    free(blocks);
    freeImage(&image);
    freeStack(&interpreter->stack);
    free(interpreter);

    return 0;
}
*/

/*
int main(int argc, char *argv[])
{
    // Vérifier le nombre d'arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <image_file.ppm>\n", argv[0]);
        return 1;
    }

    char *imageFileName = argv[1];

    // Ajouter le chemin du dossier "cornelis" au nom du fichier
    char imagePath[MAX_PATH_LENGTH];
    snprintf(imagePath, sizeof(imagePath), "cornelis/%s", imageFileName);

    // Lire l'image depuis le fichier PPM
    Image image = readPPM(imagePath);

    // Vérifier si la lecture de l'image a échoué
    if (image.pixels == NULL)
    {
        fprintf(stderr, "Erreur lors de la lecture de l'image.\n");
        // Libération de la mémoire en cas d'échec
        freeImage(&image);
        return 1;
    }

    // Afficher des informations sur la taille de la structure Image et du tableau de pixels
    size_t pixelSize = sizeof(Pixel);
    size_t imageSize = sizeof(Image);
    size_t pixelsArraySize = image.width * image.height * pixelSize;

    printf("Size of Pixel structure: %zu bytes\n", pixelSize);
    printf("Size of Image structure: %zu bytes\n", imageSize);
    printf("Size of pixels array: %zu bytes\n", pixelsArraySize);

    printf("Image width * Image height: %d\n", image.width * image.height);

    // Création de la liste chaînée de blocs
    BlockNode *blockList = createBlockList(&image);

    // Parcourir la liste chaînée de blocs
    BlockNode *current = blockList;

    while (current != NULL)
    {
        // Vérifier si le pointeur est non nul avant d'accéder aux valeurs (débogage)
        -- if (current != NULL)
        {
            printf("Block - Color: (%d, %d, %d), Position: (%d, %d), Size: %d x %d\n",
                   current->block.color.red, current->block.color.green, current->block.color.blue,
                   current->block.x, current->block.y,
                   current->block.width, current->block.height);
        }
        else
        {
            fprintf(stderr, "Pointeur de bloc nul.\n");
            // Gestion de l'erreur, libération de la mémoire, etc.
            freeBlockList(blockList);
            freeImage(&image);
            return 1;
        } --

        current = current->next;
    }

    // Libération de la liste chaînée de blocs
    freeBlockList(blockList);

    // Libération du tableau de pixels
    free(image.pixels);

    // Initialiser l'interpréteur
    Interpreter interpreter;
    interpreter.x = 0;
    interpreter.y = 0;
    interpreter.direction = 'e';
    interpreter.bord = 'b';
    initializeStack(&interpreter.stack, 100);

        // Détecter les blocs dans l'image
        //blockList = createBlockList(&image); // Utiliser createBlockList au lieu de detectBlocks
// Vérifier si la détection des blocs a échoué
if (blockList == NULL)
{
    fprintf(stderr, "Erreur lors de la détection des blocs.\n");
    freeImage(&image);
    return 1;

    // Exécuter les actions pour chaque paire de blocs
    current = blockList;

    while (current != NULL && current->next != NULL)
    {
        executeAction(&interpreter, &current->block, &current->next->block); // Ajouter des adresses (&) ici
        current = current->next->next;
    }

    // Libérer la mémoire
    freeBlockList(blockList);
    freeImage(&image);
    freeStack(&interpreter.stack);
}
return 0;
}
*/

int main(int argc, char *argv[])
{
    // Vérifier le nombre d'arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <image_file.ppm>\n", argv[0]);
        return 1;
    }

    char *imageFileName = argv[1];

    // Ajouter le chemin du dossier "cornelis" au nom du fichier
    char imagePath[MAX_PATH_LENGTH];
    snprintf(imagePath, sizeof(imagePath), "cornelis/%s", imageFileName);

    // Lire l'image depuis le fichier PPM
    Image image = readPPM(imagePath);
    printf("Address of image: %p\n", (void *)&image);
    printf("Address of pixel: %p\n", (void *)image.pixels);
    // Vérifier si la lecture de l'image a échoué
    if (image.pixels == NULL)
    {
        fprintf(stderr, "Erreur lors de la lecture de l'image.\n");
        return 1;
    }

    // Afficher des informations sur la taille de la structure Image et du tableau de pixels
    size_t pixelSize = sizeof(Pixel);
    size_t imageSize = sizeof(Image);
    size_t pixelsArraySize = image.width * image.height * pixelSize;

    // printf("Size of Pixel structure: %zu bytes\n", pixelSize);
    printf("Size of Image structure: %zu bytes\n", imageSize);
    printf("Size of pixels array: %zu bytes\n", pixelsArraySize);

    printf("Image width * Image height: %d\n", image.width * image.height);

    // Détecter les blocs dans l'image
    detectBlocks(&image);
    printf("Nombre de blocs : %d\n", image.blockCount);

    // Libération du tableau de pixels
    free(image.pixels);

    // Initialiser l'interpréteur
    Interpreter interpreter;
    interpreter.x = 0;
    interpreter.y = 0;
    interpreter.direction = 'e';
    interpreter.bord = 'b';
    initializeStack(&interpreter.stack, 100);

    // Exécuter les actions pour chaque paire de blocs
    BlockNode *current = image.blockList;

    while (current != NULL && current->next != NULL)
    {
        executeAction(&interpreter, &current->block, &current->next->block);
        current = current->next;
    }

    // Libérer la mémoire
    freeBlockList(image.blockList);
    freeStack(&interpreter.stack);

    return 0;
}
