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

#include <string.h>
#include "macroblock.h"
#define MBLOCKSIZE 16


/*
 * Perform transofrmation on each block
 */
void macroblock::transform(int quantMatrix [BLOCK_SIZE][BLOCK_SIZE], double qscale) {
    for (int y = 0; y < BLOCKS_DIM; y++) {
        for (int x = 0; x < BLOCKS_DIM; x++) {
            blocks[x][y].prettyPrintc(); // TODO: remove
            blocks[x][y].dct();
            blocks[x][y].quantize(quantMatrix, qscale);
            blocks[x][y].zigzag();
        }
    }
    return;
}

/*
 * parsePGM pgm
 * mb_id_x - index x as index of double array of macroblocks in macroblocks manager
 * mb_id_y - index y as index of double array of macroblocks in macroblocks manager
 * max_x   - total x size of the pgm
 */
void macroblock::parse(rawInput *pEncoded, size_t mb_ind_x, size_t mb_ind_y, size_t max_x) {
    offset_x = mb_ind_x * MBLOCKSIZE; // Calculate real x offset
    offset_y = mb_ind_y * MBLOCKSIZE; // Calculate real y offset

    for (int y = 0; y < BLOCKS_DIM; y++) {
        for (int x = 0; x < BLOCKS_DIM; x++) {
            blocks[x][y].parsePGM(pEncoded, offset_x, offset_y, x, y, max_x); // Let each block parsePGM its part.
        }
    }
}

/*
 * Dump rawInput encoded input.
 */
void macroblock::dump(FILE *outfile) {
    for (int y = 0; y < BLOCKS_DIM; y++) {
        for (int x = 0; x < BLOCKS_DIM; x++) {
            blocks[x][y].dump(outfile); // Let each block dump its part.
        }
    }
}

void macroblock::fill_block(unsigned char *block, size_t b_offset_x, size_t b_offset_y) {
    size_t mb_ind_x = b_offset_x/16;
    size_t mb_ind_y = b_offset_y/16;
    size_t mb_offset_x =mb_ind_x * 16;
    size_t mb_offset_y =mb_ind_y * 16;
    this->offset_x = mb_offset_x;
    this->offset_y = mb_offset_y;
    size_t b_ind_x = (b_offset_x - mb_offset_x)/8;
    size_t b_ind_y = (b_offset_y - mb_offset_y)/8;
    blocks[b_ind_x][b_ind_y].fill(block, b_offset_x, b_offset_y);

//    size_t index = 0;
//    size_t temp_index=0;
//    unsigned char temp[100];
//    memset(temp,0,100);
//    for (int y = 0; y < BLOCKS_DIM; y++) {
//        for (int x = 0; x < BLOCKS_DIM; x++) {
//            while(block[index] != '\n') {
//                if (block[index] != ' ') {
//                    temp[temp_index] = block[index];
//                    temp_index++;
//                } else {
//                    if (temp_index != 0) {
//                        blocks[x][y].dump(outfile); // Let each block dump its part.
//                    }
//                    temp_index = 0;
//                }
//                index++;
//            }
//            index++;
//        }
//    }
    printf("test"); //TODO remove me
}

void macroblock::inverse_transform(int quantMatrix[8][8], double qscale) {
    for (int y = 0; y < BLOCKS_DIM; y++) {
        for (int x = 0; x < BLOCKS_DIM; x++) {
            blocks[x][y].inverse_zigzag();
            blocks[x][y].inverse_quantize(quantMatrix, qscale);
            blocks[x][y].inverse_dct();
            blocks[x][y].prettyPrintc(); // TODO: remove
        }
    }
    return;

}
