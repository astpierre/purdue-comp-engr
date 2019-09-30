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

#ifdef TEST_ADAPTIVETHRESHOLDING
BMPImage * AdaptiveThresholding(BMPImage * grayImage, int radius, int epsilon)
{
    // Grab width and height from image header
    int width = (grayImage->header).width;
	int height = (grayImage->header).height;

	// Allocate memory for the a-thresh'ed image
    BMPImage * adaptive = NULL;
    adaptive = (BMPImage *)malloc(sizeof(BMPImage));
    if(adaptive == NULL) return NULL;

    // Images have same headers
    adaptive->header = grayImage->header;
	
	// Assign the the imagesize as height * width
	(adaptive->header).imagesize = width*height*3;
	
	// Check for data allocation fail
	if((adaptive->data = (unsigned char *)malloc(sizeof(unsigned char)*(adaptive->header).imagesize)) == NULL)
    {  BMP_Free(adaptive); return NULL;  }
	
	// Run loop for all pixels using height and width	
    int counter=0;
    int allData=0;
    int loc=0;
    int loc2=0;
    int adap_val=0;
    int row=0;
    int col=0;
    int row2=0;
    int col2=0;
    int toprow=0;
    int bottomrow=0;
    int leftcol=0;
    int rightcol=0;

    // Iterate through pixels using height and width
    for(row=0; row<height; row++)
    {
        for(col=0; col<width; col++)
        {
            // Find the maximum of top row, bottom row, left column and right column
            toprow = MAX(0, row-radius);
     	    bottomrow = MIN(height-1, row+radius);
     	    leftcol = MAX(0, col-radius);
     	    rightcol = MIN(width-1, col+radius);
        
            // Run loop from toprow to bottom row
            for(row2=toprow; row2<=bottomrow; row2++)
            {
                // Run loop from leftcol to rightcol
                for(col2=leftcol; col2<=rightcol; col2++)
                {
                    counter++;
                    loc=(row2*width+col2)*3;
                    allData+= grayImage->data[loc];
                }
            }

            // Calculate the pixel location for indexing data
            loc2=(row*width+col)*3;
            
            // Calculate the average of radius
            adap_val=(int)allData/counter;

            // Check if average minus epsilon > grayImage->data[pixel]
            if((adap_val-epsilon)>grayImage->data[loc2])
            {
                // Change pixel to black
                adaptive->data[loc2+(uint8_t)2] = 0;
                adaptive->data[loc2+(uint8_t)1] = 0;
                adaptive->data[loc2] = 0;
            }
            else
            {
                // Change pixel to white
                adaptive->data[loc2+(uint8_t)2] = 255;
                adaptive->data[loc2+(uint8_t)1] = 255;
                adaptive->data[loc2] = 255;
            }

            // Reset variables
            counter=0;
            allData=0;
        }
    }

    // Return image after thresholding
    return adaptive;
}
#endif
