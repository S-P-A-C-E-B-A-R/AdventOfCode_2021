// Advent2021_Puzzle_02_P1
// Modified On: 12/02/2021
// Modified By: Kenneth Meyerson

// Use: ProgramName.exe "InputText.txt"
// This program tracks the commands provided to determine
// final depth and position and calculate their product.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct position
{
   int Position;
   int Depth;
} GPS;

int main( int argc, char *argv[] )  {

    // Verify Program Use
    if( argc == 2 ) {

        // Attempt to Open File
        FILE *fptr;
        if ((fptr = fopen(argv[1],"r")) == NULL){
            printf("Error opening file, check file and argument");
            exit(1);
        }

        // Reset Coords:
        GPS.Position = 0;
        GPS.Depth    = 0;

        // Read contents of file.
        #define MAX 20
        char str[MAX];
        int  num;
        int  cntLines = 0;
        while (fscanf(fptr, " %s %d\n" , str, &num) != EOF )
        {
            cntLines++;
            // Report Line Count
            printf("[%4d] ",cntLines);

            // Parse CMD
            if (!strcmp(str,"forward"))
            {
                printf("CMD (%c%d) ",27,num);
                GPS.Position += num;
            }
            else if (!strcmp(str,"up"))
            {
                printf("CMD (%c%d) ",24,num);
                GPS.Depth -= num;
            }
            else if (!strcmp(str,"down"))
            {
                printf("CMD (%c%d) ",25,num);
                GPS.Depth += num;
            }
            else
            {
                printf("Error in Input!");
                exit(1);
            }

            // Report Result
            printf("GPS[%4d%c,%4d%c]\n",
                   GPS.Position,
                   ((GPS.Position >= 0) ? 27 : 26),
                   GPS.Depth,
                   ((GPS.Depth >= 0) ? 25: 24)
                   );
        }
        fclose(fptr);
    }
    else if( argc > 2 ) {
       printf("Too many arguments supplied. Expected \"Program.exe Source.txt\"\n");
    }
    else {
       printf("One argument expected: \"Program.exe Source.txt\"\n");
    }

    printf("Part 1: Distance * Depth = %d", GPS.Position*GPS.Depth);
    return 0;
 }
