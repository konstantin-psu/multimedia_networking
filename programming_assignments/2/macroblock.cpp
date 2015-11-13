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

#include "macroblock.h"

void macroblock::transform(int quantMatrix [BLOCK_SIZE][BLOCK_SIZE], double qscale) {
    for (int y = 0; y < BLOCKS_DIM; y++) {
        for (int x = 0; x < BLOCKS_DIM; x++) {
            blocks[x][y].dct();
            blocks[x][y].quantize(quantMatrix, qscale);
            blocks[x][y].zigzag();
            blocks[x][y].prettyPrint();
        }
    }
    return;
}

void macroblock::parse(pgmEncoded *pEncoded, int mb_ind_x, int mb_ind_y, size_t max_x) {
    offset_x = mb_ind_x * 16;
    offset_y = mb_ind_y * 16;

    for (int y = 0; y < BLOCKS_DIM; y++) {
        for (int x = 0; x < BLOCKS_DIM; x++) {
            blocks[x][y].parse(pEncoded, offset_x, offset_y, x, y, max_x);

        }
    }
}

void macroblock::dump(FILE *outfile) {

}
