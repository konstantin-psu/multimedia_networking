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
    char * rawString;
};
//Input format: myDCT <input image> <quantfile> <qscale> <output file>

struct pgmEncoded * readInput(char *fname);
void pgmDestroyer(struct pgmEncoded * pgm);
int main(int args, char * argv []) {
    if (args != 5) {
        exit(1);
    }
    char * inputImage = argv[1];
    char * quantfile = argv[2];
    char * qscale = argv[3];
    char * outputFile = argv[4];
    struct pgmEncoded * pgmInput = readInput(inputImage);
    return 0;
}

struct pgmEncoded * readInput(char *fname) {
    FILE * p = fopen(fname, "r"); // Open file with reading permission
    if (p == NULL) {
        printf("Failed to open %s\n", fname);
        exit(1);
    }

    fseek(p, 0L, SEEK_END);
    size_t sz = ftell(p);
    fseek(p, 0L, SEEK_SET);

    struct pgmEncoded *input = malloc(sizeof *input);
    char line [100];
    memset(line, 0, 100);
    fgets(input->header,20,p);
    printf("%s\n", input->header);
    fgets(line,100,p);
    printf("%s\n", line);
    fgets(input->twoFiveFive,20,p);
    printf("%s\n", input->twoFiveFive);

    printf("%d\n", sz);
    fclose(p);
    free(input);

}

void pgmDestroyer(struct pgmEncoded * pgm) {
    free(pgm->rawString);
    free(pgm);
}
