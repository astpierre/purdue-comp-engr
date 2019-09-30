#include "bmpfunc.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#ifdef TEST_FUNCGIVEN
int RGB2Gray(unsigned char red, unsigned char green, unsigned char blue){
	// this is a commonly used formula
	int gray = 0.2989 * red + 0.5870 * green + 0.1140 * blue;
	return gray;
}
#endif

//Modify below this line
#ifdef TEST_IMGTOGRAY
BMPImage * ImgToGray(BMPImage * image)
{
    // Grab width and height from image header
    int width = (image->header).width;
	int height = (image->header).height;

	// Allocate memory for the gray image
    BMPImage * gray_image = NULL;
    gray_image = (BMPImage *)malloc(sizeof(BMPImage));
    if(gray_image == NULL) return NULL;

    // Images have same headers
    gray_image->header = image->header;
	
	// Assign the the imagesize as height * width
	(gray_image->header).imagesize = width*height*3; 
	
	// Check for data allocation fail
	if((gray_image->data = (unsigned char *)malloc(sizeof(unsigned char)*(gray_image->header).imagesize)) == NULL)
    {  BMP_Free(gray_image);  }
	
	// Run loop for all pixels using height and width
	int pixel=0;
    for(pixel=0; pixel<(gray_image->header).imagesize; pixel+=3)
    {
        // Convert each pixel of all channels to gray using RGB2GRAY function
        unsigned char gray_val = RGB2Gray(image->data[pixel+(uint8_t)2],
                                          image->data[pixel+(uint8_t)1],	
                                          image->data[pixel]);
        
        // Assign values to all pixels of gray_image (same to all)
        gray_image->data[pixel+(uint8_t)2] = gray_val;
        gray_image->data[pixel+(uint8_t)1] = gray_val;
        gray_image->data[pixel] = gray_val;
    }

    // Return the gray image
    return gray_image;
}
#endif
