#include "Image.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//reminder of the definition of the struct IMAGE

/*typedef struct {
	unsigned int W;	// image width 
	unsigned int H; // image height
	unsigned char *R;	// pointer to the memory storing all the R intensity values 
	unsigned char *G;	// pointer to the memory storing all the G intensity values
	unsigned char *B;	// pointer to the memory storing all the B intensity values
} IMAGE;
*/



/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y)
{
	unsigned char *output = NULL;
	unsigned int address;
	unsigned int width;
	
	width = ImageWidth(image);
	
	address = x + (y*width);
	
	image += address;
	output = image->R;
	
	return *output;
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y)
{
	unsigned char *output = NULL;
	unsigned int address;
	unsigned int width;
	
	width = ImageWidth(image);
	
	address = x + (y*width);
	
	image += address;
	output = image->G;
	
	return *output;
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y)
{
	unsigned char *output = NULL;
	unsigned int address;
	unsigned int width;
	
	width = ImageWidth(image);
	
	address = x + (y*width);
	
	image += address;
	output = image->B;
	
	return *output;
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
	unsigned int address;
	unsigned char *pR = NULL;  //used to talk with image->R since R is a pointer
	unsigned int width;

	width = ImageWidth(image);	
	address = x + (y*width);

	image += address;
	image->R = pR;
	*pR = r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g)
{
	unsigned int address;
	unsigned char *pG = NULL;  //used to talk with image->G since G is a pointer
	unsigned int width;

	width = ImageWidth(image);	
	address = x + (y*width);

	image += address;
	image->G = pG;
	*pG = g;
}


/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b)
{
	unsigned int address;
	unsigned char *pB = NULL;  //used to talk with image->B since B is a pointer
	unsigned int width;

	width = ImageWidth(image);	
	address = x + (y*width);

	image += address;
	image->B = pB;
	*pB = b;
}	

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
	IMAGE *p = NULL;
	IMAGE *og_p = NULL; //used to keep the orignal address access 

	long int size;
	unsigned int x, y; //counter

	size = sizeof(IMAGE)*Width*Height;
	
	p = malloc(size);
	if(!p){
		return NULL;
		exit(10);}
	
	og_p = p; //initate og_p to p's base address

	for(x = 0; x < Width; x++) 
	{
		for(y = 0; y < Height; y++)
		{
			p->W = x;			
			p->H = y;			
			p += Width;
		}
		
		og_p++;
		p = og_p;
	}

	return p;
}

/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image)
{
	assert(image);
	free(image);
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image)
{
	unsigned int x = 0;

	image++; //have to do this or the first "W" value
		 // will be zero and will exit out of the 
		 // loop below

	do{
		image++;
		x++;
	}while( (image->W) != 0);

	return x;
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image)
{
	unsigned int y = 0;
	unsigned int width;

	width = ImageWidth(image);

	do{
		image = image + width;
		y++;		
	}while( (image->W) == 0);

	y = y - 1;
	return y;
}
//EOF Image.c
