#include "hw11.h"
#ifdef TEST_MAIN
int main(int argc, char **argv)
{
    // Check the arguments (if argc != 5)
    if(argc != 5) return EXIT_FAILURE;
 
    // Check input arguments for radius and epsilon
    // <origImageLoc> <filtImageLoc> <radius> <epsilon>
    int radius = (int)strtol(argv[3],NULL,10);
    int epsilon = (int)strtol(argv[4],NULL,10);

    // Call BMP_Open()
    BMPImage * img = BMP_Open(argv[1]);
    if(img==NULL) 
    {  BMP_Free(img); return EXIT_FAILURE;  }

    // Call ImgToGray()
    BMPImage * gray_image = ImgToGray(img);
    if(gray_image==NULL) 
    {  BMP_Free(img); BMP_Free(gray_image); return EXIT_FAILURE;  } 
    
    // Call AdaptiveThesholding()
    BMPImage * adaptive = AdaptiveThresholding(gray_image,radius,epsilon);
    if(adaptive==NULL) 
    {  BMP_Free(img); BMP_Free(gray_image); BMP_Free(adaptive); return EXIT_FAILURE;  } 

    // Call BMP_Write() to write image to file
    if(BMP_Write(argv[2],adaptive)!=TRUE)
    {  BMP_Free(img); BMP_Free(gray_image); BMP_Free(adaptive); return EXIT_FAILURE;  }  
    
    // Free all images and return successfull
    BMP_Free(img);
    BMP_Free(gray_image);
    BMP_Free(adaptive);
	return EXIT_SUCCESS;
}
#endif
