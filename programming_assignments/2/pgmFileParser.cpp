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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "pgmFileParser.h"

/*
 * implementation of pgmFileParser class
 */

/*
 * Default constructor
 * Set everything to 0
 */
pgmFileParser::pgmFileParser() {
    memset(this->twoFiveFive,0,20);
    memset(this->header,0,20);
    this->xDim = 0;
    this->yDim = 0;

    this->rawStringSize =0;

    this->macroblocksX = 0;
    this->macroblocksY = 0;
    this->rawString = NULL;
}

/*
 * Default destructor
 * rawString is the only thing needs to be cleaned up
 */
pgmFileParser::~pgmFileParser() {
    if (this->rawString != NULL) {
        free(this->rawString);
    }
}

/*
 * Allocate rawString
 */
void pgmFileParser::init(size_t rawSize) {
    this->rawString = (unsigned char*) malloc(rawSize);
    memset(this->rawString, 0, rawSize);
}


/*
 * Read input file
 */
void pgmFileParser::readInput(char *fname) {
    FILE * p = fopen(fname, "rb"); // Open file with reading permission
    if (p == NULL) {
        printf("Failed to open %s\n", fname);
        exit(1);
    }

    // Figure out total size of the file;
    fseek(p, 0L, SEEK_END);
    size_t totSize = ftell(p);
    fseek(p, 0L, SEEK_SET);

    this->init(totSize); // Allocate array for raw string

    char line [100];   // Temp string
    memset(line, 0, 100);
    fgets(this->header,20,p); // Read header
    fgets(line,100,p); // Read dimensions
    line[strlen(line) - 1] = 0;
    char * dim;
    dim = strtok (line," "); //Convert dimensions to Int
    this->xDim = atoi(dim);
    dim = strtok (line," ");
    this->yDim = atoi(dim);

    if (xDim % 16 != 0 || yDim % 16 != 0)  {
        std::cout<<"Error, input file dimensions expected to be divisible by 16\n";
        exit(1);
    }
    this->macroblocksX = this->xDim/16; // Calculate number of macroblocks
    this->macroblocksY = this->yDim/16;


    fgets(this->twoFiveFive,20,p); // Skip 255 line
    size_t sz = ftell(p);

    size_t encodedLineSize = totSize - sz;
    fread(this->rawString, encodedLineSize, 1, p); // Read encoded part in binary.
    this->rawStringSize = encodedLineSize;
    fclose(p);  // Don't forget to close the input file.
}
