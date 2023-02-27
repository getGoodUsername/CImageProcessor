//DIP function definitions in Assigment 3 (B&W, Sharpen, Hue)

#include "DIPs.h"
#include <stdio.h>
#include <math.h>

/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image)
//void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y;
    int height, width;
    int r_im, g_im, b_im;
    int total;
   
    width = ImageWidth(image);
    height = ImageHeight(image);
	
    for (x = 0; x < width; x++)
    {   for(y = 0; y < height; y++)
        {   
		r_im = GetPixelR(image, x, y);
		g_im = GetPixelG(image, x, y);
		b_im = GetPixelB(image, x, y);

		total = (r_im + g_im + b_im)/3;
			
		SetPixelR(image, x, y, total);
		SetPixelG(image, x, y, total);
		SetPixelB(image, x, y, total);
        }
    }

    return image;
}

// Sharpen function
IMAGE *Sharpen(IMAGE *image)
//void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
 
    IMAGE *og_values;
    int x, y;
    int r_og, g_og, b_og; //used to handle the SetPixel
    int tmpr, tmpg, tmpb; //temp variables
    int r_im, g_im, b_im;
    int getr, getg, getb;
    int width, height;
    
    //unsigned char R_temp[WIDTH][HEIGHT];
    //unsigned char G_temp[WIDTH][HEIGHT];
    //unsigned char B_temp[WIDTH][HEIGHT];
    
    width = ImageWidth(image);
    height = ImageHeight(image);
    og_values = CreateImage(width, height);

    for (x = 0; x < width; x++)
    {   for(y = 0; y < height; y++)
        { 
	    r_og = GetPixelR(image, x, y);
	    g_og = GetPixelG(image, x, y);
	    b_og = GetPixelB(image, x, y);

	    SetPixelR(og_values, x, y, r_og);
	    SetPixelG(og_values, x, y, g_og);
            SetPixelB(og_values, x, y, b_og);
        }
    }

    int xy[3], px1y[3], nx1y[3], xpy1[3], xny1[3], px1py1[3], px1ny1[3], nx1py1[3], nx1ny1[3];
     //n = negative, p = positive, 1 means its being modified by one
     //entry '0' for r, entry '1' for g, entry '2' for b
    
    for (x = 1; x < width - 1; x++)
    {   for (y = 1; y < height - 1; y++)
        {
	    xy[0] = GetPixelR(image, x, y);	 
	    xy[1] = GetPixelG(image, x, y);	 
	    xy[2] = GetPixelB(image, x, y);	 

	    px1y[0] = GetPixelR(image, x + 1, y);	 
	    px1y[1] = GetPixelG(image, x + 1, y);	 
	    px1y[2] = GetPixelB(image, x + 1, y);	 

	    nx1y[0] = GetPixelR(image, x - 1, y);	 
	    nx1y[1] = GetPixelG(image, x - 1, y);	 
	    nx1y[2] = GetPixelB(image, x - 1, y);	 

	    xpy1[0] = GetPixelR(image, x, y + 1);	 
	    xpy1[1] = GetPixelG(image, x, y + 1);	 
	    xpy1[2] = GetPixelB(image, x, y + 1);	 
            
	    xny1[0] = GetPixelR(image, x, y + 1);	 
	    xny1[1] = GetPixelG(image, x, y + 1);	 
	    xny1[2] = GetPixelB(image, x, y + 1);	 

	    px1py1[0] = GetPixelR(image, x + 1, y + 1);	 
	    px1py1[1] = GetPixelG(image, x + 1, y + 1);	 
	    px1py1[2] = GetPixelB(image, x + 1, y + 1);	 
	   
	    px1ny1[0] = GetPixelR(image, x + 1, y - 1);	 
	    px1ny1[1] = GetPixelG(image, x + 1, y - 1);	 
	    px1ny1[2] = GetPixelB(image, x + 1, y - 1);	 

	    nx1ny1[0] = GetPixelR(image, x - 1, y - 1);	 
	    nx1ny1[1] = GetPixelG(image, x - 1, y - 1);	 
	    nx1ny1[2] = GetPixelB(image, x - 1, y - 1);	 

	    nx1py1[0] = GetPixelR(image, x - 1, y + 1);	 
	    nx1py1[1] = GetPixelG(image, x - 1, y + 1);	 
	    nx1py1[2] = GetPixelB(image, x = 1, y + 1);	 

	    tmpr = 9 * xy[0] - px1y[0] - nx1y[0] - xpy1[0] - xny1[0] - px1py1[0] - px1ny1[0] - nx1ny1[0] - nx1py1[0];
           
            tmpg = 9 * xy[1] - px1y[1] - nx1y[1] - xpy1[1] - xny1[1] - px1py1[1] - px1ny1[1] - nx1ny1[1] - nx1py1[1];
            
	    tmpb = 9 * xy[2] - px1y[2] - nx1y[2] - xpy1[2] - xny1[2] - px1py1[2] - px1ny1[2] - nx1ny1[2] - nx1py1[2];

        getr = (tmpr > 255)?255:(tmpr < 0)?0:tmpr;
        getg = (tmpg > 255)?255:(tmpg < 0)?0:tmpg;
        getb = (tmpb > 255)?255:(tmpb < 0)?0:tmpb;
       
	SetPixelR(og_values, x, y, getr);
	SetPixelG(og_values, x, y, getg);
	SetPixelB(og_values, x, y, getb);

	tmpr = tmpg = tmpb = 0;
        }
    }
 
    for (x = 0; x < width; x++)
    {   for(y = 0; y < height; y++)
        {  
	    r_im = GetPixelR(og_values, x, y);
	    g_im = GetPixelG(og_values, x, y);
	    b_im = GetPixelB(og_values, x, y);
	    

	    SetPixelR(image, x, y, r_im);
	    SetPixelG(image, x, y, g_im);
	    SetPixelB(image, x, y, b_im);
        }
    }

    DeleteImage(og_values);	
    return image;
}


// Hue function
IMAGE *Hue(IMAGE *image, int degree)
//void Hue(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int degree)
{
    int x, y;
    int width, height;
    int rim, gim, bim;
    int getr, getg, getb;
    double a, b, r;
    double d = degree * PI / 180.0;
    double tmp_r, tmp_g, tmp_b;

    width = ImageWidth(image);
    height = ImageHeight(image);
    
    a = (2 * cos(d) + 1.0) / 3.0;
    b = (1.0 - cos(d)) / 3.0 - sin(d) / sqrt(3.0);
    r = (1.0 - cos(d)) / 3.0 + sin(d) / sqrt(3.0);

    for (x = 0; x < width; x++)
    {   for (y = 0; y < height; y++)
        {   
	    getr = GetPixelR(image, x, y);
	    getg = GetPixelG(image, x, y);
	    getb = GetPixelB(image, x, y);
	

	    tmp_r = getr * a + getg * b + getb * r;
            tmp_g = getr * r + getg * a + getb * b;
            tmp_b = getr * b + getg * r + getb * a;

            rim = (tmp_r > 255)?255:(tmp_r < 0)?0:tmp_r;        
            gim = (tmp_g > 255)?255:(tmp_g < 0)?0:tmp_g;
            bim = (tmp_b > 255)?255:(tmp_b < 0)?0:tmp_b;

	    SetPixelR(image, x, y, rim);
	    SetPixelG(image, x, y, gim);
	    SetPixelB(image, x, y, bim);
        }
    }

    return image;
}
//EOF DIPs.c
