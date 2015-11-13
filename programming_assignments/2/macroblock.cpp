//
// Created by kmacarenco on 11/12/15.
//

#include "macroblock.h"

void macroblock::transform(int quantMatrix [8][8], double qscale) {
    for (int i = 0;i < 4;i++) {
        for (int j = 0;j < 4;j++) {
            blocks[i][j].dct();
            blocks[i][j].quantize(quantMatrix, qscale);
            blocks[i][j].zigzag();
            blocks[i][j].prettyPrint();
        }
    }

    return;
}
