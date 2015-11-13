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

#include "block.h"
#include <math.h>
#include <iostream>
#define BDIM 8

block::block() {
    for (int i = 0; i < BDIM;i++) {
        for (int j = 0;j< BDIM;j++) {
            items[i][j]=0;
            transofrmed[i][j]=0;
            reordered[i][j]=0;
        }
    }
    currentIndexX = 0;
    currentIndexY = 0;
    x = 0;
    y = 0;
}
void block::add(unsigned char c) {
    items[currentIndexX][currentIndexY] = c;
    currentIndexY++;
    if (currentIndexY % BDIM == 0) {
        currentIndexY = 0;
        currentIndexX++;
    }
}

void block::setIndex(size_t x, size_t y) {
    this->x = x;
    this->y = y;
}

void block::dct() {
    double C_u = 0.0;
    double C_v = 0.0;
    double sqr = 1.0/sqrt(2.0);
    double coef = 0.0;

    for (int u = 0 ;u < BDIM;u++) {
            if (u == 0) {
                C_u = sqr;
            } else {
                C_u = 1.0;
            }
        for (int v = 0 ;v < BDIM;v++) {
            if (v == 0) {
                C_v = sqr;
            } else {
                C_v = 1.0;
            }
            coef = (C_u/2.0)  * (C_v/2.0);
            double sum = 0;
            for (int x = 0; x< BDIM; x++) {
                for (int y = 0; y< BDIM; y++) {
                    sum += items[y][x]*cos(((double)(2*y+1)*(double)v*M_PI)/16.0)*cos(((double)(2*x+1)*(double)u*M_PI)/16.0);
                }

            }
            transofrmed[v][u] = coef * sum;
//            std::cout<<transofrmed[u][v]<<std::endl;
        }
    }
    return;

}

void block::zigzag() {
    int m = 8;
    int x=0, y =0;
    int r=0,c=0;
    int res=0;
    int n = 0;
    for (int i = 0; i < m * 2; i++) {
        for (int j = (i < m) ? 0 : i - m + 1; j <= i && j < m; j++) {
            x = n / 8;
            y = n - x * 8;
            n++;
            res = (i & 1) ? j * (m - 1) + i : (i - j) * m + j;
            r = res / 8;
            c = res - r * 8;
            reordered[y][x] = quantized[c][r];
        }
    }


}

void block::quantize(int qmatrix [8][8], double qscale) {
    for (int x= 0;x<BDIM;x++) {
        for (int y= 0;y<BDIM;y++) {
            int val = round( transofrmed[y][x] / (qmatrix[x][y]*qscale));
            if (val < -127) {
                val = -127;
            } else if (val > 128) {
                val = -128;
            }
            val +=127;
            quantized[y][x] = val;

        }

    }

}

void block::prettyPrint() {
    std::cout<<x<<" "<<y<<std::endl;
    for (int i = 0;i<8;i++) {
        for (int j = 0;j<8;j++) {
              std::cout<<"  "<<reordered[j][i];
//            std::cout<<quantized[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

}

void block::parse(pgmEncoded *pEncoded, size_t macroblock_offset_x, size_t macroblock_offset_y, int block_offset_x, int block_offset_y, size_t total_x) {
   setIndex(macroblock_offset_x + block_offset_x*BDIM, macroblock_offset_y + block_offset_y*BDIM);
    int index=0;
    int loc_x = 0;
    int loc_y = 0;
    for (int row = 0; row <BDIM; row++) {
        loc_y = (y + row)*total_x;
        for (int column = 0; column <BDIM; column++) {
            loc_x = x + column;
            index = loc_x + loc_y;
            items[column][row] = pEncoded->rawString[index];
        }

    }

}
