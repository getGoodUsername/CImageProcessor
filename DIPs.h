//DIP header file, DIP declerations (B&W, Sharpen, Hue)

#ifndef dip_h_
#define dip_h_

#include "Constants.h"
#include "Image.h"

/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image);

// Sharpen function
IMAGE *Sharpen(IMAGE *image);

// Hue function
IMAGE *Hue(IMAGE *image, int degree);

#endif //dip_h_
//EOF dip_h_
