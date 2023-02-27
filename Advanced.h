//Header file for Advanced.c
//Function declerations of Noise(), Posterize(), MotionBlur()

#ifndef advanced_h_
#define advanced_h_

//header files
#include "Constants.h"
#include "Image.h"

//add noise to image
IMAGE *Noise(IMAGE *image, int n);

//posterize image
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits);

//add motionblur
IMAGE *MotionBlur(IMAGE *image, int BlurAmount);

//make image squre
IMAGE *Square(IMAGE *image, int x, int y, int L);

//enlarge image
IMAGE *Enlarge(IMAGE *image, int percentage);

//adjust brightness & contrast of image
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast);

#endif //advanced_h_

//EOF Advanced.h
