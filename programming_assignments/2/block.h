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

#ifndef JPEG_DCT_BLOCK_H
#define JPEG_DCT_BLOCK_H

#include <stddef.h>
#include <stdio.h>
#include "pgmEncoded.h"


/*
 * This class is representing 8x8 block
 */
class block {
public:
    block(); // Default constructor
    void dct(); // Dct transform itself
    void zigzag(); // Zig zag transform itself
    void setIndex(size_t x, size_t y); // Set offset
    unsigned char items [8][8]; // Raw items in pgm
    double transofrmed [8][8];  // DCT transformed items
    int quantized [8][8];       // Quantized items
    int reordered [8][8];       // Reordered items
    //Could use only one array to save space -- easier this way, though less efficient.

    size_t currentIndexX;
    size_t currentIndexY;
    size_t x; // Real offset in x
    size_t y; // Real offset in y

    void quantize(int qmatrix[8][8], double qscale);
    void parse(pgmEncoded *pEncoded, size_t i, size_t i1, int i2, int i3, size_t total_x);
    void dump(FILE *outfile);
    void prettyPrint();

};

#endif //JPEG_DCT_BLOCK_H
