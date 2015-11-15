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

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "pgmFileParser.h"
#include "macroblockManager.h"


/*
 * MacroblockManager implementation
 */

/*
 * Default constructor
 */
macroblockManager::macroblockManager() {
    macroblocks = NULL;
    macroBlocksX = 0;
    macroBlocksY = 0;
}


/*
 * Default destructor
 */
macroblockManager::~macroblockManager() {
    if (macroblocks != NULL) {
        for (int i=0; i< macroBlocksX;i++) {
            delete macroblocks[i];
        }
        delete macroblocks;
    }
}

/*
 * Read pgm and dump DCT
 */
void macroblockManager::readAndDump(pgmFileParser *test) {
    macroBlocksX = test->macroblocksX;
    macroBlocksY = test->macroblocksY;
    x = test->xDim;
    y = test->yDim;
    initMacroBlocks(test);
    for (size_t i =0; i < test->macroblocksX; i++) {
        for (size_t j =0; j < test->macroblocksY; j++) {
            macroblocks[j][i].parse(test, j,i, x); // Let each macroblock to parse it's own part
        }

    }
    transform();
    return;
}

/*
 * Allocate macroblocks
 */
void macroblockManager::initMacroBlocks(pgmFileParser *test) {
    this->macroblocks = new macroblock * [test->macroblocksX];
    for (int i = 0;i< test->macroblocksX;i++) {
        macroblocks[i] = new macroblock [test->macroblocksY];
    }
}

void macroblockManager::initMacroBlocks(dct *test) {
    this->macroblocks = new macroblock * [test->macroblocksX];
    for (int i = 0;i< test->macroblocksX;i++) {
        macroblocks[i] = new macroblock [test->macroblocksY];
    }
}

/*
 * Transform and dump
 */
void macroblockManager::transform() {
    //std::cout<<"MYDCT\n";
    //std::cout<<x<<" "<<y<<"\n";
    //std::cout<<qscale<<"\n";
    FILE * out = fopen(outDCT, "w"); // Open out file with write permissions (file will be overwritten)
    dumpHeader(out);
    if (outDCT == NULL) {
        printf("Failed to open %s\n", outDCT);
        exit(1);
    }
    for (int i = 0;i < macroBlocksX;i++) {
        for (int j = 0;j < macroBlocksY;j++) {
            macroblocks[j][i].transform(quantMatrix, qscale); // Make each macrobock to transform itself
            macroblocks[j][i].dump(out); // Make each macrobock to dump itself
        }
    }
    fclose(out);

    return;
}

/*
 * Setters
 */
void macroblockManager::setScale(char *string) { qscale =atof(string); }
void macroblockManager::setOutFile(char *string) { outDCT = string; }

/*
 * Parse quantfile
 */
void macroblockManager::parseQuantMatrix(char *string) {
    FILE * p = fopen(string, "r");
    if (p == NULL) {
        printf("Failed to open %s\n", string);
        exit(1);
    }

    size_t lineSize = 1000;
    size_t charSize = 100;
    char line [lineSize]; // Templine
    char qs [charSize]; // Temp char (100 symbols is overkill but whatever)
    memset(qs,0,charSize);

    int count = 0;
    int row = 0;
    int col = 0;

    while(fgets(line, lineSize, p) != NULL) { //read
        size_t i = 0;
        for (i = 0; i< lineSize; i++ ) {
            if (line[i] == 10) { // End of line - break;
                if (strlen(qs) != 0) {
                    quantMatrix[row][col] = atoi(qs); // set entry in the matrix
                }
                memset(qs,0,charSize);
                count=0;
                col=0;
                break;
            } else if (line[i] == 32) { // Search for space
                if (strlen(qs) == 0) {continue;}
                else {
                    quantMatrix[row][col] = atoi(qs); // set entry in the matrix
                    memset(qs,0,100);
                    count=0;
                    col++;
                }
            } else {
                qs[count] = line[i];
                count++;
            }
        }
        row++;
    }
    if (row >8 || col > 8) {
        std::cout<<"Error: quantfile expected to have 8 columns and 8 rows\n";
        exit(1);
    }



    fclose(p);

}

/*
 * Initialize object
 */
void macroblockManager::init(char *qscale, char *quantfile, char *outputfile) {
    setScale(qscale);
    parseQuantMatrix(quantfile);
    setOutFile(outputfile);

}

/*
 * Dump dct header
 */
void macroblockManager::dumpHeader(FILE *pFILE) {
    fprintf(pFILE, "%s\n", "MYDCT");
    fprintf(pFILE, "%lu %lu\n", x, y);
    fprintf(pFILE, "%f\n", qscale);
}

void macroblockManager::init_dct(char *inputImage, char *quantfile, char *outputfile) {
    inDct = inputImage;
    this->quantFile = quantfile;
    this->outPGM = outputfile;
}

void macroblockManager::parseAndDumpDCT() {
    parseQuantMatrix(quantFile);
    dctRaw.readInput(inDct);
    macroBlocksX = dctRaw.macroblocksX;
    macroBlocksY = dctRaw.macroblocksY;
    qscale = dctRaw.quantization;
    fillMacroblocks();
    inverse_transofrm();
    return;
}

void macroblockManager::fillMacroblocks() {
    unsigned char * dctString = dctRaw.rawString;
    unsigned char * currentMblock = dctRaw.rawString;

    size_t mBlock_start = 0;
    size_t mBlock_end = 0;
    initMacroBlocks(&dctRaw);
    size_t count = 0;
    size_t b_end = 9;


    /*
     * TODO remove this:
     * Find
     */
    for (size_t pos = 0; pos < dctRaw.rawStringSize; pos++) {
        if (dctString[pos] == 0) { break;}
        else if (dctString[pos] == 10) {
            if (count == 8) {

                mBlock_end = pos;
                createMacroBlock(dctString, mBlock_start, mBlock_end);
                mBlock_start = pos + 1;
                count = 0;
            } else {
                count++;
            }
        }

    }
    printf("test");//TODO delete me

}

void macroblockManager::createMacroBlock(unsigned char *dctString, size_t start, size_t anEnd) {
    unsigned char * cblock = dctString+start;
    unsigned char * line = new unsigned char[500];
    memset(line, 0, 500);
    size_t offset_x = 0;
    size_t offset_y = 0;
    readLine(&cblock, &line);

    parseOffset(line, &offset_x, &offset_y);
    size_t macroblock_offset_x = offset_x/16;
    size_t macroblock_offset_y = offset_y/16;
    macroblocks[macroblock_offset_x][macroblock_offset_y].fill_block(cblock,offset_x,offset_y);
    printf("pause");
    delete(line);
}

void macroblockManager::readLine(unsigned char **src, unsigned char **dst) {

    int index = 0;
    unsigned char t;
    while((*src)[index] != '\n'){
        t = (*src)[index];
        (*dst)[index] =t;
        index ++;
    }
    *src = *src + index + 1;
}

void macroblockManager::parseOffset(unsigned char *line, size_t *offset_x, size_t *offset_y) {
    size_t i = 0;
    size_t j = 0;
    char temp [100];
    memset(temp,0,100);
    while(line[i]!=32) {
        temp[j] = line[i];
        i++;
    }
    (*offset_x) = atoi(temp);
    j=0;
    while(line[i]!=0) {
        temp[j] = line[i];
        i++;
    }
    (*offset_y) = atoi(temp);

}

void macroblockManager::inverse_transofrm() {
    //FILE * out = fopen(outDCT, "w"); // Open out file with write permissions (file will be overwritten)
    //dumpHeader(out);
    //if (outDCT == NULL) {
    //    printf("Failed to open %s\n", outDCT);
    //    exit(1);
    //}
    for (int i = 0;i < macroBlocksX;i++) {
        for (int j = 0;j < macroBlocksY;j++) {
            macroblocks[j][i].inverse_transform(quantMatrix, qscale); // Make each macrobock to transform itself
            //macroblocks[j][i].dump(out); // Make each macrobock to dump itself
        }
    }
    //fclose(out);
    return;

}
