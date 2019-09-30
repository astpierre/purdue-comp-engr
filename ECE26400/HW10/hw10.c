#include "hw10.h"
#ifdef TEST_MAINFUNC
int main(int argc, char **argv)
{
    // Check the arguments (if argc != 3)
    if(argc != 3) return EXIT_FAILURE;

    // Call BMP_Open()
    BMPImage * img = BMP_Open(argv[1]);
    if(img==NULL) 
    {  BMP_Free(img); return EXIT_FAILURE;  }

    // Call ImgToGray()
    BMPImage * gray_image = ImgToGray(img);
    if(gray_image==NULL) 
    {  BMP_Free(img); BMP_Free(gray_image); return EXIT_FAILURE;  } 
    
    // Call BMP_Write() to write image to file
    if(BMP_Write(argv[2],gray_image)!=TRUE)
    {  BMP_Free(img); BMP_Free(gray_image); return EXIT_FAILURE;  }
    
    // Free all images and return successfull
    BMP_Free(img);
    BMP_Free(gray_image);
	return EXIT_SUCCESS;
}
#endif
