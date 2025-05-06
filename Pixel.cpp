#include "Pixel.hpp"

// empty constructor, all 0 (coordinates and RGB color components), again
Pixel::Pixel()
{
    coordX=0;   // X coordinate
    coordY=0;   // Y coordinate
    colorR=0;   // red component of the pixel color
    colorG=0;   // green component
    colorB=0;   // blue component
}

// Constructor with X and Y coordinates as parameters. Initializes the color components to 0.
Pixel::Pixel(unsigned int paramX, unsigned int paramY)
{
    coordX=paramX;
    coordY=paramY;
    colorR=0;
    colorG=0;
    colorB=0;    
}

Pixel::Pixel(unsigned int paramX, unsigned int paramY, unsigned char paramR, unsigned char paramG, unsigned char paramB)
{
    coordX=paramX;
    coordY=paramY;
    colorR=paramR;
    colorG=paramG;
    colorB=paramB;
}

Pixel::~Pixel()
{
}

Pixel* Pixel::clone()
{
    return new Pixel(this->getX(), this->getY(), this->getR(), this->getG(), this->getB());
}

unsigned int Pixel::getX()
{
    return coordX;
}

unsigned int Pixel::getY()
{
    return coordY;
}

unsigned char Pixel::getR()
{
    return colorR;
}

unsigned char Pixel::getG()
{
    return colorG;
}

unsigned char Pixel::getB()
{
    return colorB;
}

// Sets the RGB color components of the pixel
void Pixel::setComponents(unsigned char paramR, unsigned char paramG, unsigned char paramB)
{
    colorR=paramR;
    colorG=paramG;
    colorB=paramB;
}

// Normalizes the pixel color to either full Red, full Green, full Blue, or Black based on thresholds    
void Pixel::normalizeToRedGreenOrBlue()
{
    if (colorR>190 && colorG<100 && colorB<100)
    {
        // if red is dominant, set the pixel to full red
        colorR=255;
        colorG=0;
        colorB=0;
    }
    else
    {
        if (colorR<100 && colorG>190 && colorB<100)
        {
            // if green is dominant, set the pixel to full green
            colorR=0;
            colorG=255;
            colorB=0;
        }
        else
        {
            if (colorR<100 && colorG<100 && colorB>190)
            {   
                 // if blue is dominant, set the pixel to full blue
                colorR=0;
                colorG=0;
                colorB=255;
            }
            else
            {   
                 // Otherwise, set the pixel to Black
                colorR=0;
                colorG=0;
                colorB=0;                
            }                    
        }        
    }
}

// Checks if the pixel is black (i.e., if the sum of the RGB components is 0)
bool Pixel::isBlack()
{
    return 0==(colorR+colorG+colorB);  // si la suma de los tres componentes es 0, el pixel es de color negro
}

bool Pixel::isNotBlack()
{
    return 0!=(colorR+colorG+colorB);  // si la suma de los tres componentes no es 0, el pixel no es de color negro
}
// Calculates the distance of the pixel from the center of an image with given width and height
unsigned int Pixel::getDistACentro(unsigned int width, unsigned int height)
{
    //std::cout << "dist: X " << coordX << "  Y " << coordY << "W: " <<  width << "H: " <<  height << std::endl;
    
    // calculates the difference between the pixel's X coordinate and the image center
    long difX = std::abs((long)coordX - (long)width/2);
    // calculates the difference between the pixel's Y coordinate and the image center
    long difY = std::abs((long)coordY - (long)height/2);

    //std::cout << "dist: X " << difX << "  Y " << difY << "dist: " << std::sqrt((difX*difX)+(difY*difY)) << std::endl;
    
    // Return the Euclidean distance from the pixel to the center of the image
    return std::sqrt((difX*difX)+(difY*difY));
}

// Extracts RGB values of a pixel from a raw image data array
bool Pixel::getFromRaw(const unsigned char *image, unsigned int width, unsigned int height, unsigned int p_x, unsigned int p_y)
{
    bool result = false; // default to false, indicating no success
    
    //check if the coordinates are valid within the image boundaries
    if (height < 1 || width < 1 || p_x < 0 || p_y < 0 || p_x >= width || p_y >= height)
    {
        result = false;
    }
    else
    {
        int rowPix = width*3; // Calculate the number of bytes per row (width * 3, because 3 bytes per pixel)

         // extracts the Blue, Green, and Red components from the raw image data
        colorB = *(image+((p_y*rowPix)+(p_x*3)+0));  // blue
        colorG = *(image+((p_y*rowPix)+(p_x*3)+1));  // green
        colorR = *(image+((p_y*rowPix)+(p_x*3)+2));  // red
        result = true;// successfully extracted the pixel data
    }
    
    return result;
}

// Sets the RGB values of a pixel into a raw image data array
bool Pixel::setIntoRaw(unsigned char *image, unsigned int width, unsigned int height, unsigned int p_x, unsigned int p_y)
{/*allows you to forget about details of image internal format of the raw (malloc) image. 
 * Every Pixel Objects knows how to write itself in an image raw if you provide it the image pointer, 
 * the coordinates and the size of the image in width and heigth.
 */
    bool result = false; // no success
    
    // Check if the coordinates are valid within the image boundaries
    if (height < 1 || width < 1 || p_x < 0 || p_y < 0 || p_x >= width || p_y >= height)
    {
        result = false; 
    }
    else
    {
        int rowPix = width*3; // Calculate the number of bytes per row

        *(image+((p_y*rowPix)+(p_x*3)+0)) = colorB;  // blue
        *(image+((p_y*rowPix)+(p_x*3)+1)) = colorG;  // green
        *(image+((p_y*rowPix)+(p_x*3)+2)) = colorR;  // red
        result = true;// Successfully set the pixel data
    }
    
    return result;
}

