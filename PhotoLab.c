/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2017       */
/*                                                                   */
/* Author: Mina Moghadam                                                */
/* Date:   11/8/2017                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "Test.h"
#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"

IMAGE *load;
/*** function declarations ***/

void Test(void);

/* print a menu */
void PrintMenu();

/* Test all functions */

int main()
{

#ifdef DEBUG
    AutoTest();
#else
    int rc;
    //unsigned char R[WIDTH][HEIGHT];
    //unsigned char B[WIDTH][HEIGHT];
    //unsigned char G[WIDTH][HEIGHT];

    int option;            /* user input option */
    char fname[SLEN];        /* input file name */

    rc = 1;
    PrintMenu();
    scanf("%d", &option);

    /* Hue() parameter */
    int hue;

    /* Posterize() parameter */
    unsigned char rbits, gbits, bbits;

    /* Noise() parameter */
    int n;

    /* MotionBlur() parameter */
    int blur_amount;
    while (option != EXIT) {
        if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            LoadImage(fname);
	    load = LoadImage(fname);
        }

        /* menu item 2 - 14 requires image is loaded first */
        else if (option >= 2 && option < 12) {
            if (rc != SUCCESS)     {
                printf("No image is read.\n");
            }
            /* now image is loaded */
            else {
                switch (option) {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, load);
                        break;
                    case 3:
                        load = BlackNWhite(load);
                        printf("\"Black amd White\" operation is done!\n");
                        break;
                    case 4:
                        load = Sharpen(load);
                        printf("\"Sharpen\" operation is done!\n");
                        break;
                    case 5:
                        printf("Please input the degree of changing hue: ");
                        scanf("%d", &hue);
                        load = Hue(load, hue);
                        printf("\"Hue\" operatin is done!\n");
                    case 6:
                        printf("Please input noise percentage: ");
                        scanf("%d", &n);
                        load = Noise(load, n);
                        printf("\"Noise\" operation is done!\n");
                        break;
                    case 7:
                        printf("Enter the number of posterization bits for R chennel (1 to 8):");
                        scanf("%hhu", &rbits);
                        printf("Enter the number of posterization bits for G chennel (1 to 8):");
                        scanf("%hhu", &gbits);
                        printf("Enter the number of posterization bits for B chennel (1 to 8):");
                        scanf("%hhu", &bbits);
                        load = Posterize(load, rbits, gbits, bbits);
                        printf("\"Posterize\" operation is done!\n");
                        break;
                    case 8:
                        printf("Please input motion blur amount: ");
                        scanf("%d", &blur_amount);
                        load = MotionBlur(load, blur_amount);
                        printf("\"Motion Blur\" operation is done!\n");
                        break;
		    default:
                        break;

                }
            }
        }

        else if (option == 12) {
            Test();
            rc = SUCCESS;    /* set returned code SUCCESS, since image is loaded */
        }
        else {
            printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        scanf("%d", &option);
    }
    printf("You exit the program.\n");
#endif

    return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu()
{

    printf("\n-------------------------\n");
    printf("1:  Load a PPM image\n");
    printf("2:  Save the image in PPM and JPEG format\n");
    printf("3:  Change the color image to black and white\n");
    printf("4:  Sharpen the image\n");
    printf("5:  Change the hue of image\n");
    printf("6:  Add Noise to an image\n");
    printf("7:  Posterize an image\n");
    printf("8:  Add Motion Blur to an image\n");
    printf("9:  Enlarge the picture by percentage (COMMING SOON!)\n");
    printf("10: Crop a squre portion of the image (COMMING SOON!)\n");
    printf("11: Adjust the Brightness and Contrast of an image (COMMING SOON!)\n");
    printf("12; Test all functions\n");
    printf("13: Exit\n");
    printf("\n-------------------------\n");
    printf("Please make your choise: ");
}


/* auto test*/
void Test(void)
{
	int test;
	test = AutoTest();
	
	if(test){
		printf("Oops, something went wrong \n");}

}
/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
