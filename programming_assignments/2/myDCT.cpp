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


int main(int args, char * argv []) {
    if (args != 5) {
        exit(1);
    }
    char * inputImage = argv[1];
    char * quantfile = argv[2];
    char * qscale = argv[3];
    char * outputFile = argv[4];
    macroblockManager mblocksManager;
    pgmEncoded * pgmInput = new pgmEncoded();


    pgmInput->readInput(inputImage);
    mblocksManager.init(qscale, quantfile, outputFile);

    mblocksManager.readAndDump(pgmInput);
    delete(pgmInput);
    return 0;
}


