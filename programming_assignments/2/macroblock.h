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
// Created by kmacarenco on 11/12/15.
//

#ifndef JPEG_DCT_MACROBLOCK_H
#define JPEG_DCT_MACROBLOCK_H
#define BLOCKS_DIM 2
#define BLOCK_SIZE 8

#include <iostream>
#include "block.h"
#include "pgmEncoded.h"

class macroblock {
public:
    block blocks [BLOCKS_DIM][BLOCKS_DIM];
    void transform(int qmatrix [BLOCK_SIZE][BLOCK_SIZE], double);

    void parse(pgmEncoded *pEncoded, int i, int i1, size_t max_x);
    size_t offset_x;
    size_t offset_y;
    size_t total_x;
};



#endif //JPEG_DCT_MACROBLOCK_H
