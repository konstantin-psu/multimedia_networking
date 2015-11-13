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
#define MBLOCKSIZE 16


/*
 * Perform transofrmation on each block
 */
void macroblock::transform(int quantMatrix [BLOCK_SIZE][BLOCK_SIZE], double qscale) {
    for (int y = 0; y < BLOCKS_DIM; y++) {
        for (int x = 0; x < BLOCKS_DIM; x++) {
            blocks[x][y].dct();
            blocks[x][y].quantize(quantMatrix, qscale);
            blocks[x][y].zigzag();
            //blocks[x][y].prettyPrint(); // TODO: remove
        }
    }
    return;
}

/*
 * parse pgm
 * mb_id_x - index x as index of double array of macroblocks in macroblocks manager
 * mb_id_y - index y as index of double array of macroblocks in macroblocks manager
 * max_x   - total x size of the pgm
 */
void macroblock::parse(pgmEncoded *pEncoded, int mb_ind_x, int mb_ind_y, size_t max_x) {
    offset_x = mb_ind_x * MBLOCKSIZE; // Calculate real x offset
    offset_y = mb_ind_y * MBLOCKSIZE; // Calculate real y offset

    for (int y = 0; y < BLOCKS_DIM; y++) {
        for (int x = 0; x < BLOCKS_DIM; x++) {
            blocks[x][y].parse(pEncoded, offset_x, offset_y, x, y, max_x); // Let each block parse its part.
        }
    }
}

/*
 * Dump dct encoded input.
 */
void macroblock::dump(FILE *outfile) {
    for (int y = 0; y < BLOCKS_DIM; y++) {
        for (int x = 0; x < BLOCKS_DIM; x++) {
            blocks[x][y].dump(outfile); // Let each block dump its part.
        }
    }
}
