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
    pgmFormattedOutput = NULL;
}


/*
 * Default destructor
 */
macroblockManager::~macroblockManager() {
    if (macroblocks != NULL) {
        for (size_t i=0; i< macroBlocksX;i++) {
            delete macroblocks[i];
        }
        delete macroblocks;
    }
    if (pgmFormattedOutput != NULL) { delete pgmFormattedOutput;}
}

/*
 * Read pgm and dumpToDCT DCT
 */
void macroblockManager::PGMtoDCT() {
    macroBlocksX = inputObject.macroblocksX;
    macroBlocksY = inputObject.macroblocksY;
    x = inputObject.xDim;
    y = inputObject.yDim;
    initMacroBlocks(&inputObject);
    for (size_t i =0; i < inputObject.macroblocksY; i++) {
        for (size_t j =0; j < inputObject.macroblocksX; j++) {
            macroblocks[j][i].parse(&inputObject, j,i, x); // Let each macroblock to parsePGM it's own part
        }

    }
    transform();
    return;
}

/*
 * Allocate macroblocks
 */

void macroblockManager::initMacroBlocks(rawInput *test) {
    this->macroblocks = new macroblock * [test->macroblocksX];
    for (size_t i = 0;i< test->macroblocksX;i++) {
        macroblocks[i] = new macroblock [test->macroblocksY];
    }
}

/*
 * Transform and dumpToDCT
 */
void macroblockManager::transform() {
    FILE * out = fopen(outDCT, "w"); // Open out file with write permissions (file will be overwritten)
    WriteDCTheaderTo(out);
    if (outDCT == NULL) {
        printf("Failed to open %s\n", outDCT);
        exit(1);
    }
    for (size_t i = 0;i < macroBlocksY;i++) {
        for (size_t j = 0;j < macroBlocksX;j++) {
            macroblocks[j][i].transform(quantMatrix, qscale); // Make each macrobock to transform itself
            macroblocks[j][i].dump(out); // Make each macrobock to dumpToDCT itself
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

    // loop through each line in quantfile, skip spaces and save values
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
void macroblockManager::initPGM(char *inputfile, char *quantfile, char *outputfile, char *qscale) {
    setScale(qscale);
    parseQuantMatrix(quantfile);
    setOutFile(outputfile);
    inputObject.readInput(inputfile);
}

/*
 * Dump dct header
 */
void macroblockManager::WriteDCTheaderTo(FILE *pFILE) {
    fprintf(pFILE, "%s\n", "MYDCT");
    fprintf(pFILE, "%lu %lu\n", x, y);
    fprintf(pFILE, "%f\n", qscale);
}

/*
 * Dump pgm header
 */
void macroblockManager::WritePGMheaderTo(FILE *pFILE) {
    fprintf(pFILE, "%s\n", "P5");
    fprintf(pFILE, "%lu %lu\n", x, y);
    fprintf(pFILE, "%d\n", 255);
}

/*
 * Save arguments withinthis object
 */
void macroblockManager::initDct(char *inputImage, char *quantfile, char *outputfile) {
    inDct = inputImage;
    this->quantFile = quantfile;
    this->outPGM = outputfile;
}


/*
 * Convert DCT fromatted file back to PGM
 */
void macroblockManager::DCTtoPGM() {
    parseQuantMatrix(quantFile);  // Parse quantfile
    inputObject.readInput(inDct); // Read DCT file
    macroBlocksX = inputObject.macroblocksX; // Save number of macroblocks
    macroBlocksY = inputObject.macroblocksY;
    x = inputObject.xDim; // Save total dimensions of the picture
    y = inputObject.yDim;
    qscale = atof(inputObject.formatString); // fetch qscale
    fillMacroblocksFromDCT(); // Parse dct formatted string into macroblocks
    inverseTransofrm(); // inverse transform each macroblock
    return;
}

/*
 * Fill each macroblock from dct formatted string (block by block)
 *
 * Find next block start position, and end position, and fill corresponding macroblock
 */
void macroblockManager::fillMacroblocksFromDCT() {
    unsigned char * dctString = inputObject.rawString;

    size_t mBlock_start = 0;
    size_t mBlock_end = 0;
    initMacroBlocks(&inputObject);
    pgmFormattedOutput = new unsigned char[macroBlocksX * macroBlocksY * 16 * 16 + 1];
    memset(pgmFormattedOutput,0,macroBlocksX * macroBlocksY * 16 * 16 + 1);
    size_t count = 0;

    for (size_t pos = 0; pos < inputObject.rawStringSize; pos++) {
        if (dctString[pos] == 0) { break;} // EOF
        else if (dctString[pos] == 10) { // Breakline (can be inside a block, need to check
            if (count == 8) { // Block end

                mBlock_end = pos; // remember data
                createMacroBlock(dctString, mBlock_start, mBlock_end);
                mBlock_start = pos + 1; // skip new line
                count = 0;
            } else {
                count++;
            }
        }

    }
}


/*
 * Create (if needed) and add data to a macroblock
 */
void macroblockManager::createMacroBlock(unsigned char *dctString, size_t start, size_t anEnd) {
    unsigned char * cblock = dctString+start;
    unsigned char * line = new unsigned char[500];
    memset(line, 0, 500);
    size_t offset_x = 0;
    size_t offset_y = 0;
    // Each block in dct file starts with block position - fetch that line
    readLine(&cblock, &line);

    // Get block position
    parseOffset(line, &offset_x, &offset_y);

    // Get macroblock positions (index)
    size_t macroblock_offset_x = offset_x/16;
    size_t macroblock_offset_y = offset_y/16;

    // Add cblock to that macroblock
    macroblocks[macroblock_offset_x][macroblock_offset_y].fill_blockFromDCT(cblock, offset_x, offset_y);
    delete(line);
}

// Just read one line from a string
void macroblockManager::readLine(unsigned char **src, unsigned char **dst) {

    int index = 0;
    unsigned char t;
    while((*src)[index] != '\n'){ //loop until new line
        t = (*src)[index];
        (*dst)[index] =t;
        index ++;
    }
    *src = *src + index + 1; // advance string passed new line
}


// Fetch block offsets
void macroblockManager::parseOffset(unsigned char *line, size_t *offset_x, size_t *offset_y) {
    size_t i = 0;
    size_t j = 0;
    char temp [100];
    memset(temp,0,100);
    while(line[i]==32) { // skip spaces
        i++;
    }
    while(line[i]!=32) { // read offset x
        temp[j] = line[i];
        i++;
        j++;
    }
    (*offset_x) = atoi(temp); // save offset x
    j=0;
    memset(temp,0,100); // reset temp storage
    while(line[i]==32) { // sckip spaces
        i++;
    }
    while(line[i]!=0) { // read offset y
        temp[j] = line[i];
        i++;
        j++;
    }
    (*offset_y) = atoi(temp); // save offset y

}


/*
 * Transform each macroblock after it was filled
 */
void macroblockManager::inverseTransofrm() {
    // Loop through each macroblock
    for (size_t i = 0;i < macroBlocksY;i++) {
        for (size_t j = 0;j < macroBlocksX;j++) {
            macroblocks[j][i].inverse_transform(quantMatrix, qscale); // Make each macrobock to transform itself
        }
    }

    // Gather pgm data after each macraoblock was inverted
    gatherPGMResults();
    return;

}

/*
 * Save each macroblock into pgm encoded file
 */
void macroblockManager::gatherPGMResults() {

    // loop through each macroblock and gather data
    for (size_t i = 0;i < macroBlocksY;i++) {
        for (size_t j = 0;j < macroBlocksX;j++) {
            macroblocks[j][i].gatherPGMtoString(pgmFormattedOutput, x);
        }
    }

    // open file for binary write
    FILE * out = fopen(outPGM, "wb"); // Open out file with write permissions (file will be overwritten)
    // dump header
    WritePGMheaderTo(out);

    // dump pgmFormatted output
    fwrite(pgmFormattedOutput, macroBlocksX * macroBlocksY * 16 * 16,1,out);
    fclose(out);

    return;
}
