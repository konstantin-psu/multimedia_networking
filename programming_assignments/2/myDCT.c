#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct pgmEncoded {
    int xDim;
    int yDim;
    size_t headerSize;
    size_t twoFiveFiveSize;
    char header [20];
    char twoFiveFive [20];
    unsigned char * rawString;

    size_t rawStringSize;
    unsigned char ** macroblocks;
    size_t macroblocksSize;
    size_t macroblocksX;
    size_t macroblocksY;
};

struct macroBlock {

};


struct pgmEncoded * readInput(char *fname);
void pgmDestroyer(struct pgmEncoded * pgm);
struct pgmEncoded *pgmAllocator(struct pgmEncoded *pgm, size_t rawSize);



int main(int args, char * argv []) {
    if (args != 5) {
        exit(1);
    }
    char * inputImage = argv[1];
    char * quantfile = argv[2];
    char * qscale = argv[3];
    char * outputFile = argv[4];
    struct pgmEncoded * pgmInput = readInput(inputImage);
    pgmDestroyer(pgmInput);
    return 0;
}

struct pgmEncoded * readInput(char *fname) {
    FILE * p = fopen(fname, "rb"); // Open file with reading permission
    if (p == NULL) {
        printf("Failed to open %s\n", fname);
        exit(1);
    }

    fseek(p, 0L, SEEK_END);
    size_t totSize = ftell(p);
    fseek(p, 0L, SEEK_SET);

    struct pgmEncoded *input = NULL;
    input = pgmAllocator(input, totSize);

    char line [100];
    memset(line, 0, 100);
    fgets(input->header,20,p);
    printf("%s\n", input->header);
    fgets(line,100,p);
    line[strlen(line) - 1] = 0;
    printf("%s\n", line);
    char * dim;
    dim = strtok (line," ");
    input->xDim = atoi(dim);
    dim = strtok (line," ");
    input->yDim = atoi(dim);

    input->macroblocksSize = input->xDim/16 * input->yDim/16; //Should be safe since we assume that all inputs are multiples of 16.
    input->macroblocksX = input->xDim/16;
    input->macroblocksY = input->yDim/16;

    printf("xdim %d ydim %d\n", input->xDim, input->yDim);
    fgets(input->twoFiveFive,20,p);
    printf("%s\n", input->twoFiveFive);
    size_t sz = ftell(p);

    printf("%d\n", sz);
    char c;
    size_t iter = totSize - sz;
    fread(input->rawString, iter, 1, p);
    input->rawStringSize = iter;


    printf("Raw string %s\n", input->rawString);
    printf("Raw string size %d\n", input->rawStringSize);

    fclose(p);

    return input;
}

struct pgmEncoded *pgmAllocator(struct pgmEncoded *pgm, size_t rawSize) {
    pgm =  malloc(sizeof * pgm);
    pgm->rawString = (unsigned char *) malloc(rawSize);
    memset(pgm->rawString, 0, rawSize);
    memset(pgm->twoFiveFive,0,20);
    memset(pgm->header,0,20);
    pgm->headerSize = 0;
    pgm->twoFiveFiveSize = 0;
    pgm->xDim = 0;
    pgm->yDim = 0;

    pgm->rawStringSize =0;
    pgm->macroblocks = NULL;
    pgm->macroblocksSize = 0;

    pgm->macroblocksX = 0;
    pgm->macroblocksY = 0;

    return pgm;
}

void pgmDestroyer(struct pgmEncoded * pgm) {
    if (pgm != NULL) {
        if (pgm->rawString != NULL) {
            free(pgm->rawString);
        }
        free(pgm);
    }
}
