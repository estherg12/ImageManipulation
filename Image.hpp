#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h> 

class Image
{
    int internal_width;
    int internal_height;
    unsigned char * internal_image;
    unsigned char * internal_palette;   // palette data (if uses palette)
    std::string internal_name;
    std::string internal_error;
    bool imageValid;
    FILE *filePointer;
    
    bool isBMP();
    bool openFile(std::string p_flags);
    
public:
    Image(std::string p_name);
    
    bool loadImageFromDisk();        /* returns isValid() */
    bool isValid();

    unsigned char * getImagePointertoInternal();
    int getWidth();
    int getHeight();
    std::string getInternalError();
    
    bool releaseImageMemory();
    
    void setNewImagePointerWithOldRemoval(unsigned char * p_image, int p_width, int p_height);
    
    int saveImageToDisk(std::string p_name);
    
    ~Image();  /* release memory */

};

#endif // IMAGE_HPP
