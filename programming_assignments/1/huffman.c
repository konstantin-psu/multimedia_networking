#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MSIZE 512

struct symbol {
    unsigned int code;
    int size;
    char * codeChar;
};

int read_table(char * location, struct symbol * table, int size) {
    char * line = NULL;
    size_t lsize = 0;
    int code = 0;
//    int count = 0;
    int lineSize = 0;
    int position = 0;

    FILE * p = fopen(location, "r");
    if (p == NULL) {
        printf("Failed to open %s\n", location);
    }

    while((lineSize = getline(&line, &lsize, p)) != -1) {
        int i = 0;
        for (i = 0; i< lineSize; i++ ) {
            if (line[i] == 32) {

                line[i] = 0;
                position = atoi(line);
                code = strtol(line+i+1, NULL, 2);
                table[position].code = code;
                table[position].size = strlen(line+i+1) - 1;
                table[position].codeChar = (char *) calloc(table[position].size+1, sizeof(char));
                strncpy(table[position].codeChar, line+i+1, table[position].size);
            }
        }

    }
    return 0;
}

void encode(struct symbol * table, char * in, char * out)  {
    char * line = NULL;
    size_t lsize = 0;
//    struct symbol * encoded = NULL;
//    int code = 0;
    unsigned int count = 0;
    int bits_left = 32;
    int lineSize = 0;
//    uint32_t num = 4386;
    uint32_t b0,b1,b2,b3;
    uint32_t res;
//    int bits_taken = 0;
//    int position = 0;
    unsigned int encoded [MSIZE];
    memset(encoded, 0, MSIZE);

    FILE * p = fopen(in, "r");
    if (p == NULL) {
        printf("Failed to open %s\n", in);
    }

    while((lineSize = getline(&line, &lsize, p)) != -1) {
        int i = 0;
        for (i = 0; i< lineSize; i++ ) {
            unsigned int current_index = line[i];
            struct symbol csymb = table[current_index];
            unsigned int symb = csymb.code;
            if (bits_left >= csymb.size) {
                bits_left -= csymb.size;
                symb = symb << (bits_left);

                b0 = (symb & 0x000000ff) << 24u;
                b1 = (symb & 0x0000ff00) << 8u;
                b2 = (symb & 0x00ff0000) >> 8u;
                b3 = (symb & 0xff000000) >> 24u;

                res = b0 | b1 | b2 | b3;
                encoded[count]=encoded[count] | res;
            } else {
                bits_left = csymb.size - bits_left;
                symb = symb >> (bits_left);
                encoded[count]=encoded[count] | symb;
                bits_left = 32 - bits_left;
                count++;
                symb = csymb.code << bits_left;

                b0 = (symb & 0x000000ff) << 24u;
                b1 = (symb & 0x0000ff00) << 8u;
                b2 = (symb & 0x00ff0000) >> 8u;
                b3 = (symb & 0xff000000) >> 24u;

                res = b0 | b1 | b2 | b3;

                encoded[count]=encoded[count] | res;
            }
        }
    }


    char tempLoc[MSIZE];
    char * t = "/home/kmacarenco/gitHubRepos/PSU/multimedia_networking/programming_assignments/1";
    memset(tempLoc, 0, MSIZE);
    strcat(tempLoc, t);
    strcat(tempLoc, "/bintest");

    FILE * write_ptr = fopen(tempLoc,"wb");  // w for write, b for binary


    int code = strtol("00010010001101000001001000110100", NULL, 2);
    printf("%x\n",0x12);

    printf("%d", code);

//    int temp[10];
    char temp[] = "\x12\x34\x12\x34\x12\x39\x12\x34\x12\x34\x12\x39\x12\x34\x12\x34\x12\x39\x12\x34\x12\x34\x12\x39\x12\x34\x12\x34\x12\x39\x12\x34\x12\x34\x12\x39\x12\x34\x12\x34\x12\x39";
//    memset(temp, 0, 10);
    b0 = (code & 0x000000ff) << 24u;
    b1 = (code & 0x0000ff00) << 8u;
    b2 = (code & 0x00ff0000) >> 8u;
    b3 = (code & 0xff000000) >> 24u;

    res = b0 | b1 | b2 | b3;
//    temp[1]=56;

//    fwrite(encode, (count+1)*2,1,write_ptr);
    fwrite(temp, sizeof(temp),1,write_ptr);
    fclose(write_ptr);
    return;

}

void init_array(char * arr, int size, char * argv[], int ind) {
    char * t = "/home/kmacarenco/gitHubRepos/PSU/multimedia_networking/programming_assignments/1";
    memset(arr, 0, size);
    strcat(arr, t);
    strcat(arr, "/");
    strcat(arr, argv[ind]);

}

int main(int argc, char * argv[]) {
    if (argc != 4) {
        printf("Usage: huffman Table InFile OutFile");
        exit(1);
    }
    char tableLocation [MSIZE];
    char inFileLocation [MSIZE];
    char outFileLocation [MSIZE];

    struct symbol table[MSIZE];
    memset(table, 0, MSIZE);

    init_array(tableLocation, MSIZE, argv, 1);
    init_array(inFileLocation, MSIZE, argv, 2);
    init_array(outFileLocation, MSIZE, argv, 3);

    printf("%s\n", tableLocation);
    printf("%s\n", inFileLocation);
    printf("%s\n", outFileLocation);


    read_table(tableLocation, table, MSIZE);
    encode(table, inFileLocation, outFileLocation);
    return 0;
}