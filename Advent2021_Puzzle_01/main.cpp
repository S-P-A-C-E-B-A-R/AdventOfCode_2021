// Advent2021_Puzzle_01
// Modified On: 12/01/2021
// Modified By: Kenneth Meyerson

// Use: ProgramName.exe -i "InputText.txt"
// This program compares two numbers and increments a counter.
// Line-separated numerical values are provided through an input file.
// The program reads each value and compares it to the previous value.


// Runtime of 1.5s with debug text and 0.031s with cout and sprintf.
// Runtime of 5.3s with debug text and 0.031s with printf.

// Essential Libraries
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// Main Program
int main ( int argc, char *argv[] )
{
    // Argument validation:
    //     1 - Verify Number of Arguments
    //     2 - Verify Second Argument can be opened
    if (argc != 2)
    {
        printf("Usage Error!\nExample: Program.exe -i Source.txt");
        return 0;
    }
    else
    {
        // Assume second argument is a source file name
        ifstream InputSource(argv[1]);

        // Check if file opened successfully
        if (!InputSource.is_open())
        {
            printf("Usage Error!\nInput Source ( %s) failed to open!", argv[1]);;
            return 0;
        }

        // Attempt to process data
        else
        {
            // Report Success
            printf("Input Source (%s) opened!\n", argv[1]);

            // Prepare Result Variables
            int  cntLines = 0;
            int  cntInc   = 0;
            int  former   = 0;
            int  latter   = 0;
            bool check    = false;

            // Executes String Allocation
            // Executes Loop until no lines left.
            for( std::string line; getline( InputSource, line );)
            {
                // If no lines have been counted
                if (!cntLines)
                {
                    // Call stringstream to parse the line
                    stringstream convert(line);
                    if ( !(convert >> latter) )
                    {
                        // If there is an error, full stop.
                        printf("Failure to convert str to int");
                        return 0;
                    }
                }
                else
                {
                    // Shift last read value
                    former = latter;
                    // Call stringstream to parse the line
                    stringstream convert(line);
                    if ( !(convert >> latter) )
                    {
                        // If there is an error, full stop.
                        printf("Failure to convert str to int");
                        return 0;
                    }

                    // Check if the new value is larger than the previous one
                    if (latter > former){
                        cntInc++;
                        check = true;
                    }

                }

                // Report Findings
                cntLines++;
                /*
                if (cntLines == 1){
                    printf("[%4d,%4d] First Value = %d\n",cntLines,cntInc, latter);
                }
                else
                {
                    printf("[%4d,%4d] %4d > %4d =", cntLines, cntInc, former, latter);
                    if (check){
                        printf(" T\n");
                        check = false;
                    }
                    else
                    {
                        printf(" F\n");
                    }
                }
                */
            }
            printf("%4d entries processed with %4d sequentially increasing values.", cntLines, cntInc);
            return 1;
        }
    }
}
