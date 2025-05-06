#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <stdlib.h>
#include <math.h>
#include <iostream>

class Pixel
{
    unsigned int coordX=0;  // from 0 to N
    unsigned int coordY=0;  // from 0 to N
    
    unsigned char colorR=0; // 0-255 (0x00 - 0xff)
    unsigned char colorG=0; // 0-255 (0x00 - 0xff)
    unsigned char colorB=0; // 0-255 (0x00 - 0xff)
    
public:
    Pixel();
    Pixel(unsigned int paramX, unsigned int paramY);
    Pixel(unsigned int paramX, unsigned int paramY, unsigned char paramR, unsigned char paramG, unsigned char paramB); 
    ~Pixel();

    unsigned int getX();
    unsigned int getY();
    unsigned char getR();
    unsigned char getG();
    unsigned char getB();
    
    void setComponents(unsigned char paramR, unsigned char paramG, unsigned char paramB);
    
    void normalizeToRedGreenOrBlue();
    bool isBlack();
    bool isNotBlack();
    unsigned int getDistACentro(unsigned int width, unsigned int height);
    bool getFromRaw(const unsigned char *image, unsigned int width, unsigned int height, unsigned int p_x, unsigned int p_y);
    bool setIntoRaw(unsigned char *image, unsigned int width, unsigned int height, unsigned int p_x, unsigned int p_y);

    Pixel* clone();
};

#endif // PIXEL_HPP
