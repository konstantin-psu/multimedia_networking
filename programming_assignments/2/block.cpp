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
#include <string.h>
#include <stdlib.h>

#define BDIM 8

/*
 * Implementation of the block class
 */

/*
 * Default constructor - just set everything to 0
 */
block::block() {
    for (int i = 0; i < BDIM;i++) {
        for (int j = 0;j< BDIM;j++) {
            items[i][j]=0;
            transofrmed[i][j]=0;
            reordered[i][j]=0;
        }
    }
    x = 0;
    y = 0;
}

/*
 * Offset setter
 */
void block::setIndex(size_t x, size_t y) {
    this->x = x;
    this->y = y;
}


/*
 * Dct transform (Just apply the given formula -- no optimizations
 */
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
                    sum += (double)items[y][x]*cos(((double)(2*y+1)*(double)v*M_PI)/16.0)*cos(((double)(2*x+1)*(double)u*M_PI)/16.0);
                }

            }
            transofrmed[v][u] = coef * sum;
        }
    }
    return;
}

/*
 * Zigzag reorder
 */
void block::zigzag(bool inversed) {
    int m = 8;
    int y =0, x =0;
    int c =0, r =0; //row and column
    int res=0;
    int n = 0;
    for (int i = 0; i < m * 2; i++) {
        for (int j = (i < m) ? 0 : i - m + 1; j <= i && j < m; j++) {
            y = n / 8;
            x = n - y * 8;
            n++;
            res = (i & 1) ? j * (m - 1) + i : (i - j) * m + j;
            c = res / 8;
            r = res - c * 8;
            inversed ? quantized[r][c] = reordered[x][y] : reordered[x][y] = quantized[r][c];
        }
    }
}

/*
 * Quantize the transformed array
 */
void block::quantize(int qmatrix [8][8], double qscale) {
    for (int x= 0;x<BDIM;x++) {
        for (int y= 0;y<BDIM;y++) {
            int val = (int)round( transofrmed[y][x] / ((double)qmatrix[x][y]*qscale));
            if (val < -127) {
                val = -127;
            } else if (val > 128) {
                val = 128;
            }
            val +=127;
            quantized[y][x] = val;

        }

    }

}

/*
 * Pretty print the block (mostly for debugging purposes)
 */
void block::prettyPrintq() {
    std::cout<<x<<" "<<y<<std::endl;
    for (int i = 0;i<8;i++) {
        for (int j = 0;j<8;j++) {
              std::cout<<"  "<<quantized[j][i];
        }
        std::cout<<std::endl;
    }
}

void block::prettyPrintt() {
    std::cout<<x<<" "<<y<<std::endl;
    for (int i = 0;i<8;i++) {
        for (int j = 0;j<8;j++) {
            std::cout<<"  "<<transofrmed[j][i];
        }
        std::cout<<std::endl;
    }
}

void block::prettyPrintc() {
    std::cout<<x<<" "<<y<<std::endl;
    for (int i = 0;i<8;i++) {
        for (int j = 0;j<8;j++) {
            printf("%5d", items[j][i]);
        }
        std::cout<<std::endl;
    }
}
void block::prettyPrintr() {
    std::cout<<x<<" "<<y<<std::endl;
    for (int i = 0;i<8;i++) {
        for (int j = 0;j<8;j++) {
            std::cout<<"  "<<reordered[j][i];
        }
        std::cout<<std::endl;
    }
}


/*
 * parsePGM pgm into double array
 */
void block::parsePGM(rawInput *pEncoded, size_t macroblock_offset_x, size_t macroblock_offset_y,
                     int block_offset_x, int block_offset_y, size_t total_x) {


    setIndex(macroblock_offset_x + block_offset_x*BDIM, macroblock_offset_y + block_offset_y*BDIM);

     size_t index=0;
     size_t loc_x = 0;
     size_t loc_y = 0;
    for (size_t row = 0; row < BDIM; row++) {
        loc_y = (y + row) * total_x;
        for (size_t column = 0; column < BDIM; column++) {
            loc_x = x + column;
            index = loc_x + loc_y;
            items[column][row] = pEncoded->rawString[index];
        }

    }

}

void block::dumpToPGM(FILE *outfile) {
    fprintf(outfile, "%lu %lu\n", x, y);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            fprintf(outfile, "%5d", reordered[j][i]);
        }
        fprintf(outfile, "\n");
    }
}

void block::fill(unsigned char *block, size_t b_oofset_x, size_t b_offset_y) {

    x = b_oofset_x;
    y = b_offset_y;

    size_t index = 0;
    size_t temp_index=0;
    unsigned char temp[100];

    memset(temp,0,100);
    for (int yl = 0; yl < BDIM; yl++) {
        for (int xl = 0; xl < BDIM; xl++) {
            while(block[index] != 10) {
                if (block[index] != 32) {
                    temp[temp_index] = block[index];
                    temp_index++;
                } else {
                    if (temp_index != 0) {
                        reordered[xl][yl] = atoi((char *)temp);
                        memset(temp,0,100);
                        temp_index = 0;
                        break;
                    }
                    temp_index = 0;
                }
                index++;
            }
            if (temp_index != 0) {
                reordered[xl][yl] = atoi((char *)temp);
                memset(temp,0,100);
                temp_index = 0;
            }
            index++;
        }
    }
    printf("test"); //TODO remove me

}


void block::inverse_quantize(int (*quantMatrix)[8], double qscale) {
    for (int x= 0;x<BDIM;x++) {
        for (int y = 0; y < BDIM; y++) {
            double val = (double) (quantized[y][x] - 127);
            val = val * ((double) quantMatrix[x][y] * qscale);
            transofrmed[y][x] = val;
        }
    }

}

void block::inverse_dct() {
    double C_u = 0.0;
    double C_v = 0.0;
    double sqr = 1.0/sqrt(2.0);
    double coef = 0.0;

    for (int x = 0 ;x < BDIM;x++) {
        for (int y = 0 ;y < BDIM;y++) {
            double sum = 0;
            for (int u = 0; u< BDIM; u++) {
                if (u == 0) {
                    C_u = sqr;
                } else {
                    C_u = 1.0;
                }
                for (int v = 0; v< BDIM; v++) {
                    if (v == 0) {
                        C_v = sqr;
                    } else {
                        C_v = 1.0;
                    }
                    coef = (C_u/2.0)  * (C_v/2.0);
                    sum += coef * transofrmed[v][u] *cos(((double)(2*x+1)*(double)u*M_PI)/16.0)*cos(((double)(2*y+1)*(double)v*M_PI)/16.0);
                }

            }
            if (sum < 0) {
                sum = 0;
            } else if (sum > 255) {
                sum = 255;
            }
            items[y][x] = (char)sum;
        }
    }
    return;
}
