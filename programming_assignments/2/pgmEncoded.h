//
// Created by kmacarenco on 11/9/15.
//

#ifndef JPEG_DCT_PGMENCODED_H
#define JPEG_DCT_PGMENCODED_H

#include <glob.h>

class pgmEncoded {
public:

    pgmEncoded();

    ~pgmEncoded();

    void init(size_t rawSize);
    void readInput(char *fname);

    int xDim;
    int yDim;
    size_t headerSize;
    size_t twoFiveFiveSize;
    char header [20];
    char twoFiveFive [20];
    unsigned char * rawString;

    size_t rawStringSize;
    size_t macroblocksSize;
    size_t macroblocksX;
    size_t macroblocksY;
};

#endif //JPEG_DCT_PGMENCODED_H
