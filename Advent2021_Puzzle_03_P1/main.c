// Advent2021_Puzzle_03_P1
// Modified On: 12/03/2021
// Modified By: Kenneth Meyerson

// Use: ProgramName.exe "InputText.txt"
// This program processes binary input to determine
// what bit-vector is most common from the input stream.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )  {

    // Verify Program Use
    if( argc == 2 ) {

        // Attempt to Open File
        FILE *fptr;
        if ((fptr = fopen(argv[1],"r")) == NULL){
            printf("Error opening file, check file and argument");
            exit(1);
        }

        // Track number of "1" in each position.
        int BitVecArray[12] = {0};
        int Gamma = 0;
        int Epsilon = 0;

        // Read contents of file.
        #define MAX 12
        char str[MAX];
        int  num;
        int  cntLines = 0;

        while (fgets (str, 60, fptr))
        {
            cntLines++;
            // Report Line Count
            printf("[%4d] ",cntLines);

            // Report Result
            printf("%s",str);
        }
        fclose(fptr);
    }
    else if( argc > 2 ) {
       printf("Too many arguments supplied. Expected \"Program.exe Source.txt\"\n");
    }
    else {
       printf("One argument expected: \"Program.exe Source.txt\"\n");
    }

    printf("\nPart 1: Gamma * Epsilon = %d", 0);
    return 0;
 }
