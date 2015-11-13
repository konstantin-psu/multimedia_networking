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
void macroblockManager::read(pgmEncoded * test) {
    blocksX = test->macroblocksX;
    blocksY = test->macroblocksY;
    x = test->xDim;
    y = test->yDim;
    size_t index = 0;
    size_t rowCount = 0;
    size_t colCount = 0;
    initBlocks(test);
    int cc = 0;
    for (int i=0; i< test->xDim;i++) {
        if (i%8==0 && i!=0) {
            colCount++;
        }
        for (int j=0; j< test->yDim;j++) {
                if (i%8 == 0 && j%8 == 0) {
                    macroblocks[i / 8][j / 8].setIndex(i, j);
                }
                if (j%8==0 && j!=0) {
                   rowCount++;
                }
                index = i * test->xDim + j;
                cc++;
                macroblocks[colCount][rowCount].add(test->rawString[index]);
        }
        rowCount=0;
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
            macroblocks[i][j].transform(quantMatrix, qscale);
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
