//
// Created by kmacarenco on 11/12/15.
//

#ifndef JPEG_DCT_MACROBLOCK_H
#define JPEG_DCT_MACROBLOCK_H


#include <iostream>
#include "block.h"

class macroblock {
public:
    block blocks [2][2];
    void transform(int qmatrix [8][8], double);

};



#endif //JPEG_DCT_MACROBLOCK_H
