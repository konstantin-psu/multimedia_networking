#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MSIZE 512 //should be enough under assumption, that we are encoding ASCII table.

//Symbol representation
struct symbol {
    int size;
    char * codeChar; //Symbol string, and it's size.
};

struct encoded {
    char * rawLine; //To hold concatenated "encoded" input as string.
    char * encodedLine; //Convert to array of 8 bit entries
    int size;
};


int read_table(char * location, struct symbol * table, int size);  //Parse table assuming that input will be a character in ASCII format
void encode(struct symbol * table, char * in, char * out);         //Parse input file and convert to binary
void convert_and_write(struct encoded code, char * outfile);       //Convert encoded table to binary and write to the given output file
void init_array(char * arr, int size, char * argv[], int ind); //Initialize and save arguments

int main(int argc, char * argv[]) {
    // Enforce four arguments
    if (argc != 4) {
        printf("Usage: huffman Table InFile OutFile");
        exit(1);
    }

    char tableLocation [MSIZE]; //Table file location
    char inFileLocation [MSIZE]; //Input file location
    char outFileLocation [MSIZE]; //Out (encoded) file loation.

    struct symbol table[MSIZE]; //Table of symbols
    memset(table, 0, MSIZE);

    init_array(tableLocation, MSIZE, argv, 1);
    init_array(inFileLocation, MSIZE, argv, 2);
    init_array(outFileLocation, MSIZE, argv, 3);

    read_table(tableLocation, table, MSIZE);
    encode(table, inFileLocation, outFileLocation);
    return 0;
}


/***
 * Idea is to read Huffman table, and put it into array.
 * Each table entry is a letter number (In ASCII) in range [0 - 256], followed by binary represented by a string, with arbitrary length <= 32;
 *
 * To avoid searching the table each, when parsing input file, use letter number as index into array of symbols.
***/

int read_table(char * location, struct symbol * table, int size) {


    char * line = NULL; // Read line
    size_t lsize = 0;   // Placeholder for getline size;
    int lineSize = 0;   // Holder for actual line size
    int position = 0;   // Position holder for letter number.

    FILE * p = fopen(location, "r"); // Open file with reading permission
    if (p == NULL) {
        printf("Failed to open %s\n", location);
        exit(1);
    }

    while((lineSize = getline(&line, &lsize, p)) != -1) {
        int i = 0;
        for (i = 0; i< lineSize; i++ ) {
            if (line[i] == 32) { // Search for space

                line[i] = 0;     // Split line, Now we have to strings in the same array [index] [encoded string]
                position = atoi(line); // Convert position into integer.
                table[position].size = strlen(line+i+1) - 1; // Set size to the size of [encoded string]
                table[position].codeChar = (char *) calloc(table[position].size+1, sizeof(char)); // save encoded string into symbol
                strncpy(table[position].codeChar, line+i+1, table[position].size);
                break;
            }
        }

    }
    fclose(p);
    return 0;
}



/*
 *  Read Input file char by char, encode each char into corresponding entry from Huffman table
 *
 *  Save.
 */
void encode(struct symbol * table, char * in, char * out)  {

    char * line = NULL; // Getline line holder
    size_t lsize = 0;   // getline size holder
    int lineSize = 0;
    struct encoded encodedLine; // Encoded table
    encodedLine.size = 0; // Reset
    encodedLine.rawLine = (char *) calloc(5000, sizeof(char)); // 5000 should be enough to accommodate all possible entries

    FILE * p = fopen(in, "r"); // Try to open file
    if (p == NULL) {
        printf("Failed to open %s\n", in);
        exit(1);
    }

    while((lineSize = getline(&line, &lsize, p)) != -1) {
        int i = 0;
        for (i = 0; i< lineSize; i++ ) { // Read each line and append to RawLine in encoded struct
            unsigned int current_index = line[i];
            struct symbol csymb = table[current_index];
            strcat(encodedLine.rawLine, csymb.codeChar);
            encodedLine.size += csymb.size;
        }
    }
    fclose(p);

    convert_and_write(encodedLine, out);
    return;

}

void copy8(char * dest, char * source) { // Copy only 8 characters
    int i = 0;
    for (i = 0; i< 8; i++) {
        dest[i] = source[i];
    }
}
void convert_and_write(struct encoded code, char * outfile) {
    int i = 0;

    char tempStorage [9]; // To hold current value 8 - bit + 1 for null terminator
    memset(tempStorage, 0, 9); // reset
    code.encodedLine = (char *) calloc(5000, sizeof(char));
    int encodedIndex = 0; // Keep track of current entry in the encoded line

    for (i = 0; i < code.size; i++) {
        if (i%8==0) { // Convert to binary every eight characters
            copy8(tempStorage, code.rawLine + i); // Copy current 8 characters to tempStorage
            int last = code.size - i; // Make sure we have enough characters to fill the tempStorage
            if (last < 8) { //if not set all unused spaces to '0'
                for (;last < 8;last++) {
                    tempStorage[last] = '0';
                }
            }
            char code1 = strtol(tempStorage, NULL, 2); // Convert string to int, with base = 2, i.e "1001" = 9, char is enough to hold it, since
                                                       // We convert only 8 character at a time, which won't exceed 1 byte after conversion
            code.encodedLine[encodedIndex] = code1;    // Save converted character into encoded line
            encodedIndex++;
        }
    }


    FILE * write_ptr = fopen(outfile,"wb");  // w for write, b for binary
    fwrite(code.encodedLine, encodedIndex,1,write_ptr);  // save
    fclose(write_ptr);
}

void init_array(char * arr, int size, char * argv[], int ind) {
    char * t = "/home/kmacarenco/gitHubRepos/PSU/multimedia_networking/programming_assignments/1";
    memset(arr, 0, size);
    strcat(arr, t);
    strcat(arr, "/");
    strcat(arr, argv[ind]);
}
