#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
//#include "../Challenge7/decrypt.c"
#include "../Challenge2/xorHelper.c"

int main(int argc,char *argv[]){

    FILE *infile = fopen("input.txt", "r");
    if(infile == NULL)exit(EXIT_FAILURE);

    unsigned char hexString[322];
    int hexStringSize = sizeof(hexString);

    int line = 0;
    while(fgets(hexString, hexStringSize, infile)){
        hexString[strcspn(hexString, "\n")] = '\0';
        line++;
        int rawStringLength = strlen(hexString)/2;
        uint8_t* rawString = calloc(rawStringLength, sizeof(uint8_t));
        hexStringToRawString(hexString, rawString);

        int numberOfBlocks = rawStringLength/16;
        int blockLength = 16;
        for(int i=0;i<numberOfBlocks-1;i++){
            for(int j=i+1;j<numberOfBlocks;j++){
                bool blocksAreEqual = true;
                for(int c=0;c<blockLength;c++){
                    int leftmostBlockIndex = i*blockLength+c;
                    int rightBlockIndex = j*blockLength+c;
                    if(rawString[leftmostBlockIndex] != rawString[rightBlockIndex]){
                        blocksAreEqual = false;
                        break;
                        // go to next block
                    }
                }
                if(blocksAreEqual == true){
                    printf("line: %i, block1: %i, block2: %i\n", line, i, j);
                }
            }
        }
        free(rawString);
    }
    fclose(infile);

    return 0;
}