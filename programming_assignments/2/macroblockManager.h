//
// Created by kmacarenco on 11/9/15.
//


#ifndef JPEG_DCT_MACROBLOCKMANAGER_H
#define JPEG_DCT_MACROBLOCKMANAGER_H
#define BDIM 8

#include "block.h"
#include "pgmEncoded.h"
#include "macroblock.h"

class macroblockManager {
public:
    macroblockManager();
    ~macroblockManager();
    void read(pgmEncoded * test);
    void initBlocks(pgmEncoded * test);
    macroblock **macroblocks;
    size_t blocksX;
    size_t blocksY;
    int x;
    int y;
    void transform();
    double qscale;
    char * outfile;

    int quantMatrix[BDIM][BDIM];

    void setScale(char *string);

    void setOutFile(char *string);

    void parseQuantMatrix(char *string);
};

#endif //JPEG_DCT_MACROBLOCKMANAGER_H
