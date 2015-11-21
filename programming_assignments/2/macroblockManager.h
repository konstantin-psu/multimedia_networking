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
#include "macroblock.h"
#include "rawInput.h"


/*
 * This is the Driver class, creates and controls structure
 */
class macroblockManager {
public:
    macroblockManager();
    ~macroblockManager();
    void PGMtoDCT();                     // Read pgmFileParser string and dumpToDCT it to output file
    macroblock **macroblocks;            //  Two dimensional array of macroblocks (the only thing here that needs to be deleted
    size_t macroBlocksX;                 // Number of macro blocks in X dim
    size_t macroBlocksY;                 // Number of macro blocks in Y dim
    size_t x;                            // Total X dim of the input
    size_t y;                            // Total Y dim of the input

    void transform();                    // Perform DCT transformation
    double qscale;                       // qscale holder
    char *outDCT;                        // location of DCT encoded file (in pgm -> dct transformation)
    char * inDct;                        // location of DCT in file ( in dct -> pgm transformation)
    char * outPGM;                       // location of PGM out filr (in dct -> pgm transformation)
    unsigned char * pgmFormattedOutput;  // pgm encoded string ( used to dump pgm in dct -> pgm transofrmation)
    char * quantFile;                    // location of quantfile
    rawInput inputObject;                // DCT or PGM input object holder - depends on how it is invoked
                                         // it is ok to do since DCT and PGM header are close enough.


    int quantMatrix[BDIM][BDIM];         // quantmatrix - aquired by parsing quantfile

    void setScale(char *string);         // Setter function for qscale value
    void setOutFile(char *string);       // Setter function for outDCT
    void parseQuantMatrix(char *string); // Read quantfile and same it into quantMatrix

    void initPGM(char *inputfile, char *quantfile, char *outputfile, char *qscale); // Initialize all data required for PGM->DCT transformation

    void WriteDCTheaderTo(FILE *pFILE);  // Dump DCT header into pFile
    void WritePGMheaderTo(FILE *pFILE);  // Dump PGM header into pFile

    void gatherPGMResults();             // Collect PGM

    void initDct(char *inputImage, char *quantfile, char *outputfile); // Initialize data needed for DCT->PGM transformation

    void DCTtoPGM(); // Convert DCT to PGM

    void fillMacroblocksFromDCT();

    void initMacroBlocks(rawInput *test); //

    void createMacroBlock(unsigned char *dctString, size_t start, size_t anEnd); // Create macroblock from PGM

    void readLine(unsigned char **src, unsigned char **dst); // Just read line, will advance src to the end of the line

    void parseOffset(unsigned char *line, size_t *offset_x, size_t *offset_y); // Read offset from beginning of a block in DCT formatted string

    void inverseTransofrm();
};

#endif //JPEG_DCT_MACROBLOCKMANAGER_H
