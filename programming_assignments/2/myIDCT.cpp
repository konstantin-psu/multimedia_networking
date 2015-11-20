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
#include <iostream>
#include "macroblockManager.h"


/*
 * Nothing interesting is happening here.
 */
int main(int args, char * argv []) {
    if (args != 4) { //Force correct number of args
        std::cout<<"Error: Invalid number of arguments\n"
                "Usage:\n"
                "   myIDCT <.dct input file full path> <quantfile full path> <output file full path>\n";
        exit(1);
    }
    char * inputImage = argv[1];              // get rawInput file path
    char * quantfile = argv[2];               // get formatString file path
    char * outputFile = argv[3];              // get output file path
    macroblockManager manager;
    manager.initDct(inputImage, quantfile, outputFile);
    manager.DCTtoPGM();
    return 0;
}


