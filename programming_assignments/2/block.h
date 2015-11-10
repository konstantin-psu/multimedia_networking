//
// Created by kmacarenco on 11/9/15.
//

#ifndef JPEG_DCT_BLOCK_H
#define JPEG_DCT_BLOCK_H

#include <stddef.h>

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
};

#endif //JPEG_DCT_BLOCK_H
