//function defintions for the new filters
//Noise(), Posterize(), MotionBlur()

#include "Advanced.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Function Definition noise */
IMAGE *Noise(IMAGE *image, int n)
//void Noise( int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{	
	srand(time(NULL));	
	int x, y;     //normal array indexing/counter
	int x_r, y_r; //random number variables
	int noise;    //the ammount of noise wanted
	int count = 0;
	int width, height;

	width = ImageWidth(image);
	height = ImageHeight(image);
	noise = (n*width*height)/100;

	for(x = 0; x < width; x++)
		for(y = 0; y < height; y++)
		{
			count++;
			x_r = rand() % width;   //used in the array indexing
			y_r = rand() % height;	//need to be random values
		
			if(count <= noise){
				SetPixelR(image, x_r, y_r, 255);
				SetPixelG(image, x_r, y_r, 255);
				SetPixelB(image, x_r, y_r, 255);
			}
		}
	return image;
}


/* Function Definiton posterize */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits)
//void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
{

/*
 * 127 //01111111 for 8 bit and 
 * 127 //01111111 for 8 bit or
 * 191 //10111111 for 7 bit and
 * 63  //00111111 for 7 bit or
 * 223 //11011111 for 6 bit and 
 * 31  //00011111 for 6 bit or
 * 239 //11101111 for 5 bit and
 * 15  //00001111 for 5 bit or
 * 247 //11110111 for 4 bit and
 * 7   //00000111 for 4 bit or
 * 251 //11111011 for 3 bit and
 * 3   //00000011 for 3 bit or
 * 253 //11111101 for 2 bit and 
 * 1   //00000001 for 2 bit or
 * 0   //00000000 for 1 bit and
   0   //00000000 for 1 bit or */
//This is the algorithim I came up 
//with for Posterize:
//(original_bit_value & nth_bit_and) | nth_bit_or
//nth_bit_and makes the the nth bit 0
//nth_bit_or makes the the n-1 bits 1
//Translated the binary values to decimal

	int x, y;
	int and[8] = {0, 253, 251, 247, 239, 223, 191, 127};
	int or[8]  = {0, 1, 3, 7, 15, 31, 63, 127};
	int r, g, b;
	int getr, getg, getb;
	int width, height;

	width = ImageWidth(image);
	height = ImageHeight(image);

	for(x = 0; x < width; x++)
	{
		for(y = 0; y < height; y++)
		{
			getr = GetPixelR(image, x, y);
			getg = GetPixelG(image, x, y);
			getb = GetPixelB(image, x, y);
			
			r = (getr & and[rbits - 1]) | or[rbits - 1];
			g = (getg & and[gbits - 1]) | or[gbits - 1];
			b = (getb & and[bbits - 1]) | or[bbits - 1];
	
			SetPixelR(image, x, y, r);	
			SetPixelG(image, x, y, g);	
			SetPixelB(image, x, y, b);	
		}
	}

	return image;
}

IMAGE *MotionBlur(IMAGE *image, int BlurAmount)
//void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{

//	int og_r[WIDTH][HEIGHT], og_g[WIDTH][HEIGHT], og_b[WIDTH][HEIGHT];//temp color
//	int blur_r[WIDTH][HEIGHT], blur_g[WIDTH][HEIGHT], blur_b[WIDTH][HEIGHT];//blur addition value added on
	
	IMAGE *og_values; //temp rgb value
	IMAGE *blur_values; //used for blur temp
	int r_og, g_og, b_og; //to be put in SetPixelR/G/B
	int blur_r, blur_g, blur_b; //to be put in SetPixel for blur_values
	int r, g, b;
	int x, y, n = 1; //counting variables
	int getr_o, getg_o, getb_o;
	int getr_b, getg_b, getb_b;
	int index_good; //used to divide by acceptable values 
	int width, height; //used to construct temp rgb value

	width = ImageWidth(image);
	height = ImageHeight(image);
	og_values = CreateImage(width, height);
	
	for(x = 0; x < width; x++)
	{	for(y = 0; y < height; y++)
		{
			r_og = GetPixelR(image, x, y);
			g_og = GetPixelG(image, x, y);
			b_og = GetPixelB(image, x, y);

			SetPixelR(og_values, x, y, r_og);
			SetPixelG(og_values, x, y, g_og);
			SetPixelB(og_values, x, y, b_og);
		}
	}
	
	blur_values = CreateImage(width, height);
	
	for(x = 0; x < width; x++)
	{	for(y = 0; y < height; y++)
		{	
			SetPixelR(blur_values, x, y, 0);
			SetPixelG(blur_values, x, y, 0);
			SetPixelB(blur_values, x, y, 0);
			index_good = 1;
				
			for(n = 1; ( (n <= BlurAmount) && ((y - n) >= 0) ); n++) //n = 1 ... don't want to start on og variable
			{
				if( (y - n) < 0)
					{break;}
				blur_r += GetPixelR(og_values, x, y - n);
				blur_g += GetPixelG(og_values, x, y - n);
				blur_b += GetPixelB(og_values, x, y - n);

				SetPixelR(blur_values, x, y, blur_r);
				SetPixelG(blur_values, x, y, blur_g);
				SetPixelB(blur_values, x, y, blur_b);
				index_good++;
			}
		
			getr_o = GetPixelR(og_values, x, y);
			getg_o = GetPixelG(og_values, x, y);
			getb_o = GetPixelB(og_values, x, y);

			getr_b = GetPixelR(blur_values, x, y);	
			getg_b = GetPixelG(blur_values, x, y);	
			getb_b = GetPixelR(blur_values, x, y);	
			
			r = (getr_o/2) + ((getr_b/index_good)/2);
			g = (getg_o/2) + ((getg_b/index_good)/2);
			b = (getb_o/2) + ((getb_b/index_good)/2);
			
			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}
	
	DeleteImage(og_values);
	DeleteImage(blur_values);
	
	return image;
}
//EOF Advanced.c
