// Advent2021_Puzzle_01_P2
// Modified On: 12/02/2021
// Modified By: Kenneth Meyerson

// Use: ProgramName.exe "InputText.txt"
// This program implements a "three-measurement sliding window".
// The sum of 3 values within a window are compared with...
// the sum of the subsequent 3 value window. Each window is...
// offset by 1 value.

// Four values are stored in a pseudo-ring buffer. The position
// of the most recent addition is tracked, thus the oldest value
// is assumed to be the following index (wrapping around the array).
// This is more memory and instruction efficient than shifting the
// array.

// Initially, it appears that sum of the first and last three values
// of the array is required every cycle.
//     Given: [A,B,C,D]
//     A+B+C -> ABC (2x Addition)
//     B+C+D -> BCD (2x Addition)
//     BCD > ABC    (1x Comparison)

// This is not the case. A simplified solution performs the following:
//     [A,B,C,D] - B+C -> BC (1x Addition)
//     A+BC => ABC (1x Addition)
//     BC+D => BDC (1x Addition)
//     BCD > ABC   (1x Comparison)
// The initial addition of common values saves an addition.

// Next, a new value replaced the oldest index:
//     [A,B,C,D] -> [E,B,C,D]
//     BCD was previously calculated.
//     C+D+E => CDE (3x Addition)
//     CDE > BCD    (1x Comparison)
// An instruction can be improved by replacing the 3x addition:
//     BCD was previously calculated.
//     BCD - B => CD  (1x Subtraction)
//     CD + E  => CDE (1x Addition)

// Runtime of 6.9s with debug text and 0.031s without.

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
            //printf("Input Source (%s) opened!\n", argv[1]);

            // Pseudo-Buffer Variables
            int  ring[4] = {0}; // Initialize empty Ring.
            int  pos = 0;       // Track most recent value

            // Prepare Sum Variables
            int temp       = 0;
            int sumLeading = 0;
            int sumLagging = 0;

            // Prepare Result Variables
            int  cntLines = 0;
            int  cntInc   = 0;

            // Executes String Allocation
            // Executes Loop until no lines left.
            for( std::string line; getline( InputSource, line );)
            {
                stringstream convert(line);
                if ( !(convert >> temp) )
                {
                    // If there is an error, full stop.
                    printf("Failure to convert str to int");
                    return 0;
                }
                else
                {
                    // Increment Line Counter
                    cntLines++;

                    // Initialize Buffer
                    if (cntLines < 5)
                    {
                        // Save Input to Ring
                        ring[pos] = temp;

                        // Initial Sum
                        if ((cntLines > 1) && (cntLines < 4))
                        {
                            sumLeading += temp;
                        }
                        if (cntLines == 4 )
                        {
                            sumLagging = sumLeading + ring[3];
                            sumLeading = sumLeading + ring[0];
                        }
                    }
                    // Standard Processing
                    else
                    {
                        // Update Trackers
                        ring[pos] = temp; // Update oldest

                        // Summation
                        sumLeading = sumLagging; // Update leading sum with lagging.
                        // Handle pseudo-ring wrap condition
                        if (pos == 3)
                        {
                            sumLagging -= ring[0];
                            sumLagging += ring[3];
                        }
                        else
                        {
                            sumLagging -= ring[pos+1];
                            sumLagging += ring[pos];
                        }
                    }

                    // Increment Increases if Appropriate
                    if (sumLagging > sumLeading)
                    {
                        cntInc++;
                    }

                    // Increment Ring Position
                    (pos < 3) ? (pos++) : (pos = 0);

                    // Report Results
                    /*
                    printf("(%4d,%1d)",cntLines,pos);
                    printf("[%4d,%4d,%4d,%4d]",ring[0],ring[1],ring[2],ring[3]);
                    printf(": %4d > %4d\n",sumLagging,sumLeading);
                    */
                }
            }
            printf("%4d entries processed with %4d sequentially increasing values.", cntLines, cntInc);
            return 1;
        }
    }
}
