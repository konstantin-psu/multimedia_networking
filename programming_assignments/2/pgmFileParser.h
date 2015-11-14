/*
* Class: Intro to Multimedia Networking 
* 
* Student: Konstantin Macarenco 
* 
* Programming assignment #2.  
* 
*/
/*
* Copyright (c) 2015. Konstantin Macarenco 
* 
* [This program is licensed under the GPL version 3 or later.] 
* 
* Please see the file COPYING in the source 
* distribution of this software for license terms.  
* 
*/
//
// Created by kmacarenco on 11/9/15.
//

#ifndef JPEG_DCT_PGMENCODED_H
#define JPEG_DCT_PGMENCODED_H

#include <glob.h>

// This class represent pgm encoded file.
class pgmFileParser {
public:

    pgmFileParser();

    ~pgmFileParser();

    void init(size_t rawSize);
    void readInput(char *fname);

    size_t xDim; // x dimension retrieved from header
    size_t yDim; // y dimension retrieved from header
    //
    char header [20];   // For P5
    char twoFiveFive [20]; // For 255
    unsigned char * rawString; // Encoded String

    size_t rawStringSize; // Encoded String size
    size_t macroblocksX; // Number of macroblocks in y dimension
    size_t macroblocksY; // Number of macroblocks in x dimension
};

#endif //JPEG_DCT_PGMENCODED_H
