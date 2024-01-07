#ifndef IMAGE_H
#define IMAGE_H

// Définir la structure Pixel
typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

// je veux creer un type luminosité qui determine s'il y a une difference de luminosité.la différence de luminosité est dans le cycle clair -> normal -> foncé -> clair
typedef enum
{
    NO_LUM_DIFFERENCE,
    LUM_ONE_DARKER,
    LUM_TWO_DARKER,
} LuminosityDifference;

// Définir la structure Block
typedef struct
{
    int x;
    int y;
    int width;
    int height;
    Pixel color;
    LuminosityDifference luminosityDifference;
    // Ajoutez d'autres attributs nécessaires pour représenter un bloc
} Block;

// Définir la structure d'un nœud de liste chaînée pour les blocs
typedef struct BlockNode
{
    Block block;
    struct BlockNode *next;
} BlockNode;

// Définir la structure Image
typedef struct
{
    Pixel **pixels;
    int width;
    int height;
    BlockNode *blockList; // Liste chaînée de blocs
    int blockCount;
} Image;

typedef enum
{
    NO_COLOR_DIFFERENCE,
    SAME_COLOR,
    COLOR_ONE_DARKER,
    COLOR_TWO_DARKER,
    COLOR_THREE_DARKER,
    COLOR_FOUR_DARKER,
    COLOR_FIVE_DARKER,
} ColorDifference;

// Définition des directions
enum Direction
{
    EAST,
    SOUTH,
    WEST,
    NORTH
};

// Prototypes des fonctions pour la gestion de l'image

int isSameColor(Pixel pixel1, Pixel pixel2);

ColorDifference compareColors(Pixel color1, Pixel color2);

int normalizeLuminosity(int luminosity);

LuminosityDifference compareLuminosities(int lum1, int lum2);

/*@requires x >= 0 && y >= 0 && image != NULL && x < image->width && y < image->height;
@ensures \result is a valid pixel in the image;
*/
Pixel *getPixel(Image *image, int x, int y);

// Fonction pour obtenir le pixel adjacent dans une direction donnée
/*@requires x >= 0 && y >= 0 && image != NULL && x < image->width && y < image->height;
@ensures \result is a valid pixel in the image;
*/
Pixel getAdjacentPixel(Image *image, int x, int y, enum Direction direction);

void exploreBlock(Image *image, int x, int y, Pixel targetColor, Pixel replacementColor, int visited[image->width][image->height]);

// void addBlockToList(int x, int y, int width, int height, Pixel color);

int shouldBeAddedToBlock(Block *block, int x, int y, Pixel color);

void updateBlock(Block *block, int x, int y);

void initializeNewBlock(Block *block, int x, int y, Pixel color);

void addPixelToBlock(Image *image, int x, int y, Pixel color);

/*@requires image != NULL;
      @assigns \result;
      @ensures \result != NULL && \result contains valid blocks;
    */
// BlockNode *detectBlocks(Image *image);
void detectBlocks(Image *image);

// Fonction principale pour détecter les blocs
// void detectAllBlocks(Image *image);

// Ajouter une fonction pour libérer la mémoire de la liste chaînée
void freeBlockList(BlockNode *head);

/*@requires filename != NULL;
      @assigns \result;
      @ensures \result.pixels != NULL && \result.width > 0 && \result.height > 0;
    */
Image readPPM(char *filename);

/*@requires image != NULL;
      @assigns image->pixels;
      @ensures image->pixels == NULL;
    */
void freeImage(Image *image);

// void addBlockToList(Image *image, int x, int y, int width, int height, Pixel color);

/*@requires image != NULL;
@ensures \result >= 0;
*/
int numBlocks(Image *image);

// Création de la liste chaînée de blocs
BlockNode *createBlockList(Image *image);

// countBlocks
int countBlocks(BlockNode *blockList);

#endif /* IMAGE_H */
