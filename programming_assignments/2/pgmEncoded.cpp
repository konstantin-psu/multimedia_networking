//
// Created by kmacarenco on 11/9/15.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "pgmEncoded.h"

pgmEncoded::pgmEncoded() {
    memset(this->twoFiveFive,0,20);
    memset(this->header,0,20);
    this->headerSize = 0;
    this->twoFiveFiveSize = 0;
    this->xDim = 0;
    this->yDim = 0;

    this->rawStringSize =0;
    this->macroblocksSize = 0;

    this->macroblocksX = 0;
    this->macroblocksY = 0;
    this->rawString = NULL;
}

pgmEncoded::~pgmEncoded() {
    if (this->rawString != NULL) {
        free(this->rawString);
    }
}

void pgmEncoded::init(size_t rawSize) {
    this->rawString = (unsigned char*) malloc(rawSize);
    memset(this->rawString, 0, rawSize);
}

void pgmEncoded::readInput(char *fname) {
    FILE * p = fopen(fname, "rb"); // Open file with reading permission
    if (p == NULL) {
        printf("Failed to open %s\n", fname);
        exit(1);
    }

    fseek(p, 0L, SEEK_END);
    size_t totSize = ftell(p);
    fseek(p, 0L, SEEK_SET);

    this->init(totSize);

    char line [100];
    memset(line, 0, 100);
    fgets(this->header,20,p);
    fgets(line,100,p);
    line[strlen(line) - 1] = 0;
    char * dim;
    dim = strtok (line," ");
    this->xDim = atoi(dim);
    dim = strtok (line," ");
    this->yDim = atoi(dim);

    this->macroblocksSize = this->xDim/8 * this->yDim/8; //Should be safe since we assume that all thiss are multiples of 16.
    this->macroblocksX = this->xDim/8;
    this->macroblocksY = this->yDim/8;


    fgets(this->twoFiveFive,20,p);
    size_t sz = ftell(p);

    size_t iter = totSize - sz;
    fread(this->rawString, iter, 1, p);
    this->rawStringSize = iter;
    fclose(p);
}
