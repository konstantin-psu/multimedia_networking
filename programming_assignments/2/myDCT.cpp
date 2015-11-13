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
 /*
 * Copyright Info
 */
#include <stdlib.h>
#include "pgmEncoded.h"
#include "macroblockManager.h"


/*
 * Nothing interesting is happening here.
 */
int main(int args, char * argv []) {
    if (args != 5) { //Force correct number of args
        std::cout<<"Error: Invalid number of arguments\n"
                "Usage:\n"
                "   myDCT <pgm file full path> <quant file full path> <quantization float> <compressed file destination full path>\n";
        exit(1);
    }
    char * inputImage = argv[1];              // get pgm file path
    char * quantfile = argv[2];               // get quant file path
    char * qscale = argv[3];                  // get desired compression ratio
    char * outputFile = argv[4];              // get output file path
    macroblockManager mblocksManager;         // create macroblock manager
    pgmEncoded * pgmInput = new pgmEncoded(); //create pgm parser


    pgmInput->readInput(inputImage);                     // Parse pgm file
    mblocksManager.init(qscale, quantfile, outputFile);  // Init macroblock manager

    mblocksManager.readAndDump(pgmInput);                // Read, transform and dump PGM
    delete(pgmInput);                                    // Don't forget to deallocate memory
    return 0;
}


