#include "bmpimage.h"

#ifdef TEST_HEADERVALID
int Is_BMPHeader_Valid(BMPHeader* header, FILE *fptr) 
{
    if((header->type)!=0x4d42) return FALSE;
    if((header->offset)!=BMP_HEADER_SIZE) return FALSE;
    if((header->DIB_header_size)!=DIB_HEADER_SIZE) return FALSE;
    if((header->planes)!=1) return FALSE;
    if((header->compression)!=FALSE) return FALSE;
    if((header->ncolours)!=0) return FALSE;
    if((header->importantcolours)!=0) return FALSE;
    if((header->bits)!=24) return FALSE;
    return TRUE;
}
#endif

#ifdef TEST_BMPOPENFILE
BMPImage *BMP_Open(const char *filename) 
{
    // Declare the BMPImage pointer and file pointer
    BMPImage *img = NULL;
  	FILE *fptr = NULL;
    
    // Open and check the file
    fptr=fopen(filename,"r");
	if(fptr==NULL) 
    {  BMP_Free(img);  fclose(fptr);  return NULL;  }

	// Allocate memory for BMPImage*
	img = (BMPImage *)malloc(sizeof(BMPImage));
	
    // Check for memory allocation errors
    if(img==NULL)
    {  fprintf(stderr,"malloc fail\n"); BMP_Free(img);  fclose(fptr); return NULL;  }
	
	// Read the first 54 bytes of the source into the header
    fseek(fptr,0L,SEEK_SET);
	if(fread(&(img->header), sizeof(BMPHeader), 1, fptr) != 1) 
    {  BMP_Free(img);  fclose(fptr);  return NULL;  }
	
	// Check if the header is valid
	if(Is_BMPHeader_Valid(&(img->header), fptr)==0)
    {  BMP_Free(img);  fclose(fptr);  return NULL;  }
 
    // Allocate memory for image data
    img->data=(unsigned char *)malloc(sizeof(unsigned char)*((int)((img->header).imagesize)));
    if((img->data)==NULL)
    {  fprintf(stderr,"malloc fail\n"); BMP_Free(img);  fclose(fptr); return NULL;  }

	// Read in the image data
    for(int i=0; i<img->header.imagesize; i++)
    {
        if(fread(&img->data[i],sizeof(unsigned char), 1, fptr) != 1)
        {  free(img->data); free(img); return NULL;  }
    }

    // Check if file still has data (error)
    unsigned char onebyte;
    if(fread(&onebyte, sizeof(unsigned char), 1, fptr) != 0)
    {  BMP_Free(img);  fclose(fptr);  return NULL;  } 
    
    // Everything successful, close file
	fclose(fptr);
	return img;
}
#endif

#ifdef TEST_WRITEFUNC
int BMP_Write(const char * outfile, BMPImage* image)
{
    // Open the outfil and check for error
    FILE * fptr = NULL;
    fptr = fopen(outfile, "w");
    if(fptr==NULL) return 0;

    // Write the image header to the outfile
    fseek(fptr,0,SEEK_SET);
    if(fwrite(&(image->header),sizeof(BMPHeader), 1, fptr) != 1)
    {  fclose(fptr); return 0;  }
	
	// Write the image data to the outfile
    for(int i=0;i<image->header.imagesize; i++)
    {
        if(fwrite(&image->data[i],sizeof(unsigned char), 1, fptr) != 1)
        {  fclose(fptr); return FALSE;  }
    }

    // Everything successful, close file
	fclose(fptr);
	return TRUE;
}
#endif

#ifdef TEST_BMPFREEFUNC
void BMP_Free(BMPImage* image) 
{ 
    free(image->data);
    free(image);
}
#endif
