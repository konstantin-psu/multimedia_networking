#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "pgmEncoded.h"
#include "macroblockManager.h"

using namespace std;






int main(int args, char * argv []) {
    if (args != 5) {
        exit(1);
    }
    char * inputImage = argv[1];
    char * quantfile = argv[2];
    char * qscale = argv[3];
    char * outputFile = argv[4];
    pgmEncoded * pgmInput = new pgmEncoded();
    macroblockManager mblocks;
    mblocks.setScale(qscale);
    mblocks.parseQuantMatrix(quantfile);
    mblocks.setOutFile(outputFile);


    pgmInput->readInput(inputImage);
    mblocks.read(pgmInput);
    delete(pgmInput);
    return 0;
}


