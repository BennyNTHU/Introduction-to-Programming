/* EE231002 Lab14. Image Processing
   106061218 Cheng-En Lee
   Date: 2025/02/10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro definitions for bounding box coordinates
#define DOWN_LEFT_CORNER_X 446
#define DOWN_LEFT_CORNER_Y 1221
#define DOWN_RIGHT_CORNER_X 646
#define DOWN_RIGHT_CORNER_Y 1221
#define UP_LEFT_CORNER_X 446
#define UP_LEFT_CORNER_Y 951
#define UP_RIGHT_CORNER_X 646
#define UP_RIGHT_CORNER_Y 951
#define BORDER_THICKNESS 10 // Define border thickness in pixels

// Define pixel and image structures
typedef struct sPIXEL {
    unsigned char r, g, b; // Red, Green, Blue components
} PIXEL;

typedef struct sIMG {
    char header[3]; // PPM header (P6)
    int W, H;      // Image width and height
    int level;     // Color intensity level
    PIXEL **PX;   // 2D array of pixels
} IMG;

// Function prototypes
IMG *PPMin(char *inFile);
void PPMout(IMG *p1, char *outFile);
IMG *PPMcvt(IMG *p1, IMG *ee, IMG *nthu);
void freeImage(IMG *img);
void addBoundingBox(IMG *img);

int main(int argc, char *argv[]) 
{
    if (argc != 5) 
	{
        printf("Usage: %s <input.ppm> <EE.ppm> <NTHU.ppm> <output.ppm>\n", argv[0]);
        return 1;
    }
    
    // Load images
    IMG *mainImg = PPMin(argv[1]);
    IMG *eeLogo = PPMin(argv[2]);
    IMG *nthuLogo = PPMin(argv[3]);
    if (!mainImg || !eeLogo || !nthuLogo) 
	{
        printf("Error: Unable to read images.\n");
        return 1;
    }
    
    // Process image
    IMG *outputImg = PPMcvt(mainImg, eeLogo, nthuLogo);

    // Add bounding box
    addBoundingBox(outputImg);

    // Save processed image
    PPMout(outputImg, argv[4]);

    // Free allocated memory
    freeImage(mainImg);
    freeImage(eeLogo);
    freeImage(nthuLogo);
    freeImage(outputImg);
    
    return 0;
}

// Read PPM image from file
IMG *PPMin(char *inFile) 
{
    FILE *fp = fopen(inFile, "rb");
    if (!fp) 
		return NULL;
    
    IMG *img = (IMG *)malloc(sizeof(IMG));
    fscanf(fp, "%s\n%d %d\n%d\n", img->header, &img->W, &img->H, &img->level);
    
    img->PX = (PIXEL **)malloc(img->H * sizeof(PIXEL *));
    for (int i = 0; i < img->H; i++) 
	{
        img->PX[i] = (PIXEL *)malloc(img->W * sizeof(PIXEL));
        fread(img->PX[i], sizeof(PIXEL), img->W, fp);
    }
    fclose(fp);
    return img;
}

// Write PPM image to file
void PPMout(IMG *p1, char *outFile) 
{
    FILE *fp = fopen(outFile, "wb");

    if (!fp) 
		return;
    
    fprintf(fp, "%s\n%d %d\n%d\n", p1->header, p1->W, p1->H, p1->level);

    for (int i = 0; i < p1->H; i++)
        fwrite(p1->PX[i], sizeof(PIXEL), p1->W, fp);
    
    fclose(fp);
}

// Convert image: grayscale + add EE/NTHU logos + add border
IMG *PPMcvt(IMG *p1, IMG *ee, IMG *nthu) 
{
    IMG *newImg = (IMG *)malloc(sizeof(IMG));
    *newImg = *p1;
    newImg->PX = (PIXEL **)malloc(newImg->H * sizeof(PIXEL *));
    
    for (int i = 0; i < newImg->H; i++) 
	{
        newImg->PX[i] = (PIXEL *)malloc(newImg->W * sizeof(PIXEL));
        for (int j = 0; j < newImg->W; j++) 
		{
            // Convert to grayscale
            unsigned char gray = p1->PX[i][j].r * 0.2126 + p1->PX[i][j].g * 0.7152 + p1->PX[i][j].b * 0.0722;
            newImg->PX[i][j].r = gray;
            newImg->PX[i][j].g = gray;
            newImg->PX[i][j].b = gray;
        }
    }
    
    // Add EE logo at lower right corner
    for (int i = 0; i < ee->H; i++) 
	{
        for (int j = 0; j < ee->W; j++) 
		{
            int x = newImg->H - ee->H + i;
            int y = newImg->W - ee->W + j;
            if (x < newImg->H && y < newImg->W && ee->PX[i][j].r != 255 && ee->PX[i][j].g != 255 && ee->PX[i][j].b != 255)
                newImg->PX[x][y] = ee->PX[i][j];
        }
    }
    
    // Add NTHU logo at center with purple tone
    int centerX = newImg->H / 2 - nthu->H / 2;
    int centerY = newImg->W / 2 - nthu->W / 2;
    for (int i = 0; i < nthu->H; i++) 
	{
        for (int j = 0; j < nthu->W; j++) 
		{
            int x = centerX + i;
            int y = centerY + j;
            if (x < newImg->H && y < newImg->W && nthu->PX[i][j].r != 255 && nthu->PX[i][j].g != 255 && nthu->PX[i][j].b != 255) 
			{
                newImg->PX[x][y].r = 255;
                newImg->PX[x][y].b = 255;
            }
        }
    }
    
    // Add border around the image
    for (int i = 0; i < newImg->H; i++) 
	{
        newImg->PX[i][0].r = newImg->PX[i][0].g = newImg->PX[i][0].b = 0;
        newImg->PX[i][newImg->W - 1].r = 0;
    }
    for (int j = 0; j < newImg->W; j++) 
	{
        newImg->PX[0][j].r = newImg->PX[0][j].g = newImg->PX[0][j].b = 0;
        newImg->PX[newImg->H - 1][j].r = 0;
    }
    
    return newImg;
}

// Free allocated memory
void freeImage(IMG *img) 
{
    for (int i = 0; i < img->H; i++)
        free(img->PX[i]);

    free(img->PX);
    free(img);
}

// Function to add a white bounding box with thickness around a specified region
void addBoundingBox(IMG *img) {
    for (int i = UP_LEFT_CORNER_Y; i <= DOWN_LEFT_CORNER_Y; i++) 
	{
        for (int t = 0; t < BORDER_THICKNESS; t++) 
		{
            img->PX[i][UP_LEFT_CORNER_X + t].r = 255;
            img->PX[i][UP_LEFT_CORNER_X + t].g = 255;
            img->PX[i][UP_LEFT_CORNER_X + t].b = 255;
            img->PX[i][UP_RIGHT_CORNER_X - t].r = 255;
            img->PX[i][UP_RIGHT_CORNER_X - t].g = 255;
            img->PX[i][UP_RIGHT_CORNER_X - t].b = 255;
        }
    }
    for (int j = UP_LEFT_CORNER_X; j <= UP_RIGHT_CORNER_X; j++) 
	{
        for (int t = 0; t < BORDER_THICKNESS; t++) 
		{
            img->PX[UP_LEFT_CORNER_Y + t][j].r = 255;
            img->PX[UP_LEFT_CORNER_Y + t][j].g = 255;
            img->PX[UP_LEFT_CORNER_Y + t][j].b = 255;
            img->PX[DOWN_LEFT_CORNER_Y - t][j].r = 255;
            img->PX[DOWN_LEFT_CORNER_Y - t][j].g = 255;
            img->PX[DOWN_LEFT_CORNER_Y - t][j].b = 255;
        }
    }
}
