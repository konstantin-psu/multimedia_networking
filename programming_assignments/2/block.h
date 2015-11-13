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
#include "pgmEncoded.h"

class block {
public:
    block();
    void add(unsigned char c);
    void dct();
    void zigzag();
    void setIndex(size_t x, size_t y);
    unsigned char items [8][8];
    double transofrmed [8][8];
    int quantized [8][8];
    int reordered [8][8];
    size_t currentIndexX;
    size_t currentIndexY;
    size_t x;
    size_t y;

    void quantize(int qmatrix[8][8], double qscale);

    void prettyPrint();

    void parse(pgmEncoded *pEncoded, size_t i, size_t i1, int i2, int i3, size_t total_x);
};

#endif //JPEG_DCT_BLOCK_H
