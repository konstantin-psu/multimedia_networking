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
#include "macroblockManager.h"


/*
 * Nothing interesting is happening here.
 */
int main(int args, char * argv []) {
    if (args != 5) { //Force correct number of args
        std::cout<<"Error: Invalid number of arguments\n"
                "Usage:\n"
                "   myDCT <.pgm input file full path> <quant file full path> <quantization float> <.dct out full path>\n";
        exit(1);
    }
    char * inputImage = argv[1];              // get pgm file path
    char * quantfile = argv[2];               // get formatString file path
    char * qscale = argv[3];                  // get desired compression ratio
    char * outputFile = argv[4];              // get output file path
    macroblockManager mblocksManager;         // create macroblock manager


    mblocksManager.initPGM(inputImage, quantfile, outputFile, qscale);  // Init macroblock manager
    mblocksManager.PGMtoDCT();                // Read, transform and dumpToDCT PGM
    return 0;
}


