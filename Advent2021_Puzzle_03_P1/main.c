// Advent2021_Puzzle_03_P1
// Modified On: 12/03/2021
// Modified By: Kenneth Meyerson

// Use: ProgramName.exe "InputText.txt"
// This program processes binary input to determine
// what bit-vector is most common from the input stream.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 14

// Recursive Power2
int power2(int a) {
    return (a != 0) ? (2 * power2(a - 1)) : 1;
}

// Hacky Binary Conversion
int binaryArrtoDec(int arr[])
{
    // Print the Array
    printf("[%d%d%d%d%d%d%d%d%d%d%d%d]\n",
           arr[0],
           arr[1],
           arr[2],
           arr[3],
           arr[4],
           arr[5],
           arr[6],
           arr[7],
           arr[8],
           arr[9],
           arr[10],
           arr[11]);

    // Sum the Binary Values
    int n = 0;
    for (int i = 0; i <= MAX-3; i++)
    {
        printf("[%2d] n = %4d +", i,n);
        n += arr[i]*power2(11-i);
        printf (" %d*(2^%2d)\n",arr[i],(11-i));
    }

    return n;
}

int main( int argc, char *argv[] )  {

    // Verify Program Us
    if( argc == 2 ) {

        // Attempt to Open File
        FILE *fptr;
        if ((fptr = fopen(argv[1],"r")) == NULL){
            printf("Error opening file, check file and argument");
            exit(1);
        }

        // Track number of "1" in each position.
        const char One = 49;
        int BitVecArray[12] = {0};
        int Gamma = 0;
        int Epsilon = 0;

        // Read contents of file.
        char str[MAX];
        int  cntLines = 0;

        while (fgets (str, MAX, fptr))
        {
            // Clean Line Garbage
            str[strcspn(str, "\n")] = 0;

            // Parse Result
            for (int i = 0; i < MAX; i++)
            {
                // Check if current position is 1
                //printf("%d == %d\n", str[i], One);
                if (str[i] == One)
                {
                    BitVecArray[i]++;
                }
            }

            // Debug Line Result
            cntLines++;
            printf("[%4d](%s) => [%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d]\n",
                   cntLines,
                   str,
                   BitVecArray[0],
                   BitVecArray[1],
                   BitVecArray[2],
                   BitVecArray[3],
                   BitVecArray[4],
                   BitVecArray[5],
                   BitVecArray[6],
                   BitVecArray[7],
                   BitVecArray[8],
                   BitVecArray[9],
                   BitVecArray[10],
                   BitVecArray[11]);
        }
        fclose(fptr);

        // Process Results
        for (int i = 0; i < MAX; i++)
        {
            // If the index is greater than half of the values, then it is the most
            // common bit. Therefore, a "1" is assigned to that position.
            (BitVecArray[i] > (cntLines/2)) ? (BitVecArray[i] = 1) : (BitVecArray[i] = 0);
        }

        // Calculate Gamma
        printf("Gamma (Most Common Bits): ");
        Gamma   = binaryArrtoDec(BitVecArray);
        printf("Decimal: %d\n",Gamma);

        // Hacky "BitFlip" on an array
        for (int i = 0; i < MAX; i++)
        {
            (BitVecArray[i] == 0) ? (BitVecArray[i] = 1) : (BitVecArray[i] = 0);
        }

        // Calculate Epsilon
        printf("Epsilon (Least Common Bits): ");
        Epsilon = binaryArrtoDec(BitVecArray);
        printf("Decimal: %d\n",Epsilon);

        // Calculate Final
        printf("\nPart 1: Gamma * Epsilon = %d", Gamma*Epsilon);
    }
    else if( argc > 2 ) {
       printf("Too many arguments supplied. Expected \"Program.exe Source.txt\"\n");
    }
    else {
       printf("One argument expected: \"Program.exe Source.txt\"\n");
    }
    return 0;
 }
