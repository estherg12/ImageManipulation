#include "Image.hpp"

Image::Image(std::string p_name)
{
    internal_name = p_name;//name of the image file
    filePointer = nullptr;//file pointer to null
    imageValid = false;//sets the valid image to false
    internal_width = 0;
    internal_height = 0;
    internal_error = "";
    internal_image = nullptr;//pointer to the image
    internal_palette = nullptr;   // palette data (if uses palette)
}

bool Image::isBMP()
{//checks if the image file is BMP
    std::string::size_type posOfDot = internal_name.find_last_of(".");//search for the last position of a dot in the files name
    std::string ext = internal_name.substr(posOfDot+1,std::string::npos);//gets the file extension
    //checks if the file extension is BMP
    return ext.compare("BMP")==0 || ext.compare("bmp")==0 ||
    ext.compare("BmP")==0 || ext.compare("bmP")==0 ||
    ext.compare("BMp")==0 || ext.compare("bMp")==0 ||
    ext.compare("Bmp")==0 || ext.compare("bMP")==0;
}
    
bool Image::openFile(std::string p_flags)
    {//opens the image file with the specified permisions
        filePointer = fopen(internal_name.c_str(), p_flags.c_str());    // FILEFLAGS_READBINARY
        return filePointer != nullptr; //returns true if u're able to open the file
    }
    
bool Image::loadImageFromDisk()        /* returns isValid() */
    {//load the image from the disk
        if (isBMP())//if the file is BMP
        {
            if (openFile("rb"))
            {//opens file in binary lecture mode
                unsigned long padding =  internal_width%4;    // calculate padding (relleno) of bytes of each list of pixels to avoid those bytes
                unsigned char * palette = NULL;   // initialize palette data (if uses palette)
                int sizePixelCount;   // pixel count: store the total number of pixels
                short bit_count;   // bit count per pixel (24 if no palette)
                int color_count = 0;   // colors used (if uses palette)
                unsigned char temp;
                int countOfBytesRead = 0; //counter of readed bytes
                
                
                fseek(filePointer, 18, SEEK_SET);//moves the file pointer to the 18 position (width) 
                fread(&internal_width, sizeof(int), 1, filePointer);    // read width of the image
                fread(&internal_height, sizeof(int), 1, filePointer);   // read height image
                
                fseek(filePointer, 28, SEEK_SET);//moves the file pointer to the 28 position (bit count)
                fread(&bit_count, sizeof(short), 1, filePointer);    // read bit count (color depth)
                
                fseek(filePointer, 54, SEEK_SET);//moves the file pointer to the 54 position (data image begins)
                
                /* If uses palette (bit count is not 24) */
                if (bit_count != 24)
                    {
                        color_count = (int)pow(2.0, bit_count);//calculate the amount of colors in the palette used
                        palette = (unsigned char *)malloc(sizeof(unsigned char) * 4 * color_count);//reserve the memory in the palette
                        fread(palette, sizeof(unsigned char), 4 * color_count, filePointer);//reads the palette of colors
                    }
                    
                /* Allocates memory for the image 
                 * Calculates the total sizq of the pixels and reserves memory for the image*/
                sizePixelCount = internal_width * internal_height;
                internal_image = (unsigned char *)malloc(sizeof(unsigned char) * sizePixelCount * 3); // from file --> pixels
                
                /* Reads the image data */
                if (bit_count == 24)
                {//if the image is 24 bits (RGB)
                    //padding (relleno) bytes
                    unsigned char paddingBytes[4]; // extra safety at 1 byte cost
                    paddingBytes[0]=0x00;
                    paddingBytes[1]=0x00;
                    paddingBytes[2]=0x00;
                    paddingBytes[3]=0x00;
                    
                    for (int i=0; i<internal_height; i++)
                    {
                        fread(internal_image+(i*internal_width*3),internal_width*3,1,filePointer);//read the data image
                        fread(paddingBytes,padding,1,filePointer);  // read padding to ignore/dispose the padding bytes
                    }
                }
                else
                {
                    while (countOfBytesRead < sizePixelCount)
                        {
                            fread(&temp, sizeof(unsigned char), 1, filePointer);
                            internal_image[countOfBytesRead * 3] = palette[temp * 4];
                            internal_image[countOfBytesRead * 3 + 1] = palette[temp * 4 + 1];
                            internal_image[countOfBytesRead * 3 + 2] = palette[temp * 4 + 2];
                            countOfBytesRead++;
                        }
                }
                
                fclose(filePointer);
                imageValid=true;
            }
            else
            {      
                imageValid=false;
                internal_error="File open failed";
            }
        }
        else
        {
            imageValid=false;
            internal_error="Not BMP";
        }
        
        return imageValid;
}
    
bool Image::isValid()
{
    return imageValid;
}

unsigned char * Image::getImagePointertoInternal()
{
    unsigned char * result = nullptr;
    if (imageValid)
    {
        result = internal_image;
    }
        
    return result;
}

int Image::getWidth()
{
        int result = 0;
        if (imageValid)
        {
            result = internal_width;
        }
        
        return result;
    }

int Image::getHeight()
{
        int result = 0;
        if (imageValid)
        {
            result = internal_height;
        }
        
    return result;
}
    
std::string Image::getInternalError()
{
    return internal_error;
}

bool Image::releaseImageMemory()
{
    bool result = false;
    if (imageValid && internal_image!=nullptr)
        {
            free(internal_image);
            if (internal_palette!=nullptr)
            {
                free(internal_palette);
            }
            result = true;
        }

        return result;
}
    
void Image::setNewImagePointerWithOldRemoval(unsigned char * p_image, int p_width, int p_height)
{/*updates de internal raw image data of the image object with a new one received as parameter. 
 * Then releases the memory of the previous.
 */
        if (internal_palette!=nullptr)
            {
                free(internal_palette);
            }
        
        if (internal_image!=nullptr)
            {
                free(internal_image);
            }
            
        internal_image = p_image;
        internal_width = p_width;
        internal_height = p_height;
        imageValid = true;
    }
    
int Image::saveImageToDisk(std::string p_name)
{
        int result=0; //Initialize the result to 0, indicating success by default
        
        internal_name = p_name; // Update the internal file name with the provided name
    
        /* Check if the file exists */
       /* if (openFile("rb"))// Try to open the file in read-binary mode
        {
            fclose(filePointer); //closes the file
            result = -1;  // file exist, abort
        }
        else // if the file doesn't exist
        {*/
        if (openFile("wb"))  // Try to open the file in write-binary mode (creating a new file)
            {
                unsigned long padding =  internal_width%4; // Calculate padding to ensure each row of pixels is a multiple of 4 bytes in size
                //unsigned long paddingb =  (4 - (width*3 -((width*3/4) * 4)))%4; 
                //std::cout << "padding: " << padding << "          padding B: " << paddingb <<std::endl;
                
                unsigned char header[14];
                header[0] = 0x42; //'B';  // First character of the BMP format is 'B'            
                header[1] = 0x4d; //'M';  // First character of the BMP format is 'M'
                // Calculates the total file size: image data size plus 54 bytes for the BMP header
                unsigned long fileSize_02 = (internal_width*3+padding) * internal_height + 54; // calcular data + header
                //std::cout << "file size: " << fileSize_02 <<std::endl;
                // Assigns the file size to the corresponding bytes in the BMP header
                header[2] = fileSize_02 & 0xFF;
                header[3] = (fileSize_02 >> 8) & 0xFF;
                header[4] = (fileSize_02 >> 16) & 0xFF;
                header[5] = (fileSize_02 >> 24) & 0xFF;
                //std::cout << "file size: " << (int)header[2] << " . " << (int)header[3] << " . "<< (int)header[4] << " . " << (int)header[5] << std::endl;
                 // The next 4 bytes are reserved and are set to 0
                header[6] = 0;
                header[7] = 0;
                header[8] = 0;
                header[9] = 0;
                
                 // Specify the offset where image data begins, which is 54 (in hexadecimal: 0x36)
                header[10] = 0x36; // offset to data, 54
                header[11] = 0;
                header[12] = 0;
                header[13] = 0;

                fwrite(header, 14, 1, filePointer); // Write the 14-byte header to the file               

                // Prepares the 40-byte BITMAPV5HEADER (containing image information)
                unsigned char bitmapV5Header[40];
                bitmapV5Header[0] = 0x28; // size = 40 bytes
                
                // The next bytes are initialized to 0
                bitmapV5Header[1] = 0;
                bitmapV5Header[2] = 0;
                bitmapV5Header[3] = 0;
                
                 // Specify the width of the image in pixels
                unsigned long imageWidth_7 = (unsigned long)internal_width;
                bitmapV5Header[4] = imageWidth_7 & 0xFF;
                bitmapV5Header[5] = (imageWidth_7 >> 8) & 0xFF;
                bitmapV5Header[6] = (imageWidth_7 >> 16) & 0xFF;
                bitmapV5Header[7] = (imageWidth_7 >> 24) & 0xFF;
                
                // Specify the height of the image in pixels
                unsigned long imageHeight_8 = (unsigned long)internal_height;
                bitmapV5Header[8] = imageHeight_8 & 0xFF;
                bitmapV5Header[9] = (imageHeight_8 >> 8) & 0xFF;
                bitmapV5Header[10] = (imageHeight_8 >> 16) & 0xFF;
                bitmapV5Header[11] = (imageHeight_8 >> 24)& 0xFF;
                
                // Specify the number of color planes (always 1)
                bitmapV5Header[12] = 0x01;  // plane
                bitmapV5Header[13] = 0x00;  // plane
                // Specify the color depth: 24 bits (3 bytes per pixel)
                bitmapV5Header[14] = 0x18;  // 24 bits
                bitmapV5Header[15] = 0x00;  // 24 bits
                
                 // Specify no compression
                bitmapV5Header[16] = 0x00;  // no compression
                bitmapV5Header[17] = 0x00;  // no compression
                bitmapV5Header[18] = 0x00;  // no compression
                bitmapV5Header[19] = 0x00;  // no compression
                
                // Specify the size of the raw image data (including padding)
                unsigned long rawDataSize = (unsigned long)(internal_height * (internal_width*3+padding));
                //std::cout << "rawDataSize: " << rawDataSize <<std::endl;
                bitmapV5Header[20] = rawDataSize & 0xFF;  // data size
                bitmapV5Header[21] = (rawDataSize >> 8) & 0xFF;  // data size
                bitmapV5Header[22] = (rawDataSize >> 16) & 0xFF;  // data size
                bitmapV5Header[23] = (rawDataSize >> 24)& 0xFF;  // data size
                
                 // Specify horizontal and vertical resolution in pixels per meter (typically 2835)
                bitmapV5Header[24] = 0x13;
                bitmapV5Header[24] = 0x13;  // hor resol
                bitmapV5Header[25] = 0x0B;  // hor resol
                bitmapV5Header[26] = 0x00;  // hor resol
                bitmapV5Header[27] = 0x00;  // hor resol

                bitmapV5Header[28] = 0x13;  // vert resol
                bitmapV5Header[29] = 0x0B;  // vert resol
                bitmapV5Header[30] = 0x00;  // vert resol
                bitmapV5Header[31] = 0x00;  // vert resol
                
                // No colors in the palette and no important colors specified
                bitmapV5Header[32] = 0x00;  // colors in palette
                bitmapV5Header[33] = 0x00;  // colors in palette
                bitmapV5Header[34] = 0x00;  // colors in palette
                bitmapV5Header[35] = 0x00;  // compression

                bitmapV5Header[36] = 0x00;  // important colors
                bitmapV5Header[37] = 0x00;  // important colors
                bitmapV5Header[38] = 0x00;  // important colors
                bitmapV5Header[39] = 0x00;  // important colors

                fwrite(bitmapV5Header, 40, 1, filePointer);  // Write the 40-byte BITMAPV5HEADER to the file                
                
                // Prepare the padding bytes (extra space to align each row to 4 bytes)
                unsigned char paddingBytes[4];  // extra safety at 1 byte cost
                paddingBytes[0]=0x00;
                paddingBytes[1]=0x00;
                paddingBytes[2]=0x00;
                paddingBytes[3]=0x00;
                 // Write the image data row by row, including the padding
                for (int i=0; i<internal_height; i++)
                {
                    //std::cout << "fwrite -W " <<width<<"  H "<<height<<"   i: " << i << "  desp: " << (i*width*3) <<std::endl;
                    fwrite(internal_image+(i*internal_width*3),internal_width*3,1,filePointer);  // write the pixel data         fwrite(image, 3, 4, fp);    writing 3 bytes, 4 times 
                    fwrite(paddingBytes,padding,1,filePointer); // write the padding bytes
                    
                }
                fclose(filePointer); // close the file after writing
                result =0; // operation is successfull, retun 0
            }
            else
            {
                result = -2;  // couldn't create the file, abort
            }
       //}
       return result; // return the final result of the operation
}

Image::~Image() /* release memory */
{
    if (internal_palette!=nullptr)
            {
                free(internal_palette);
            }
            
    if (internal_image!=nullptr)
            {
                free(internal_image);
            }
}

