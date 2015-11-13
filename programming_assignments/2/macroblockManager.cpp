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
#include "pgmEncoded.h"
#include "macroblockManager.h"
#define BSIZE 8

macroblockManager::macroblockManager() {
    macroblocks = NULL;
    blocksX = 0;
    blocksY = 0;
}

macroblockManager::~macroblockManager() {
    if (macroblocks != NULL) {
        for (int i=0; i< blocksX;i++) {
            delete macroblocks[i];
        }
        delete macroblocks;
    }
}
void macroblockManager::readAndDump(pgmEncoded *test) {
    blocksX = test->macroblocksX;
    blocksY = test->macroblocksY;
    x = test->xDim;
    y = test->yDim;
    size_t index = 0;
    size_t rowCount = 0;
    size_t colCount = 0;
    initBlocks(test);
    int cc = 0;
    for (int i =0; i < test->macroblocksX; i++) {
        for (int j =0; j < test->macroblocksY; j++) {
            macroblocks[j][i].parse(test, j,i, x);
        }

    }
    transform();
    return;
}

void macroblockManager::initBlocks(pgmEncoded * test) {
    this->macroblocks = new macroblock * [test->macroblocksX];
    for (int i = 0;i< test->macroblocksX;i++) {
        macroblocks[i] = new macroblock [test->macroblocksY];
    }
}
void macroblockManager::transform() {
    std::cout<<"MYDCT\n";
    std::cout<<x<<" "<<y<<"\n";
    std::cout<<qscale<<"\n";
    for (int i = 0;i < blocksX;i++) {
        for (int j = 0;j < blocksY;j++) {
            macroblocks[j][i].transform(quantMatrix, qscale);
        }
    }

    return;
}

void macroblockManager::setScale(char *string) {
    qscale =atoi(string);

}

void macroblockManager::setOutFile(char *string) {
    outfile = string;
}

void macroblockManager::parseQuantMatrix(char *string) {
    FILE * p = fopen(string, "r");
    if (p == NULL) {
        printf("Failed to open %s\n", string);
        exit(1);
    }

    char line [100]; // Read line
    char qs [100];
    memset(qs,0,100);

    int count = 0;
    int row = 0;
    int col = 0;
    while(fgets(line, 100, p) != NULL) {
        int i = 0;
        for (i = 0; i< 100; i++ ) {
            if (line[i] == 10) {
                if (strlen(qs) != 0) {
                    quantMatrix[row][col] = atoi(qs);
                }
                memset(qs,0,100);
                count=0;
                col=0;
                break;
            } else if (line[i] == 32) { // Search for space
                if (strlen(qs) == 0) {continue;}
                else {
                    quantMatrix[row][col] = atoi(qs);
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



    fclose(p);

}

void macroblockManager::init(char *qscale, char *quantfile, char *outputfile) {
    setScale(qscale);
    parseQuantMatrix(quantfile);
    setOutFile(outputfile);

}
