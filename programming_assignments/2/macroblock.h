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

/*
 * Representation of a single macroblock
 */
class macroblock {
public:
    block blocks [BLOCKS_DIM][BLOCKS_DIM]; // Each macroblock has fixed number of blocks
    void transform(int qmatrix [BLOCK_SIZE][BLOCK_SIZE], double); // transofrm will apply dct, quantmatrix, and zigzag
    void dump(FILE *outfile); // dump content to outfile
    void parse(pgmEncoded *pEncoded, int i, int i1, size_t max_x); // Parse corresponding pgm encoded string

    size_t offset_x; // Macroblock offset in X dim
    size_t offset_y; // Macroblock offset in Y dim
    size_t total_x;  // Total size of file in X dim

};

#endif //JPEG_DCT_MACROBLOCK_H
