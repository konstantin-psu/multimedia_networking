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


#ifndef JPEG_DCT_MACROBLOCKMANAGER_H
#define JPEG_DCT_MACROBLOCKMANAGER_H
#define BDIM 8

#include "block.h"
#include "pgmFileParser.h"
#include "macroblock.h"
#include "dct.h"


/*
 * This is the Driver class, creates and controls structure
 */
class macroblockManager {
public:
    macroblockManager();
    ~macroblockManager();
    void readAndDump(pgmFileParser *test); // Read pgmFileParser string and dump it to output file
    void initMacroBlocks(pgmFileParser *test);
    macroblock **macroblocks;  //  Two dimensional array of macroblocks (the only thing here that needs to be deleted
    size_t macroBlocksX; // Number of macro blocks in X dim
    size_t macroBlocksY; // Number of macro blocks in Y dim
    size_t x;  // Total X dim of the input
    size_t y;  // Total Y dim of the input

    void transform(); // Perform DCT transformation
    double qscale;
    char *outDCT;
    char * inDct;
    char * outPGM;
    char *quantFile;
    dct  dctRaw;

    int quantMatrix[BDIM][BDIM]; // quantmatrix - aquired by parsing quantfile

    void setScale(char *string);
    void setOutFile(char *string);
    void parseQuantMatrix(char *string);

    void init(char *qscale, char *quantfile, char *outputfile);

    void dumpHeader(FILE *pFILE);

    void init_dct(char *inputImage, char *quantfile, char *outputfile);

    void parseAndDumpDCT();

    void fillMacroblocks();

    void initMacroBlocks(dct *test);
};

#endif //JPEG_DCT_MACROBLOCKMANAGER_H
