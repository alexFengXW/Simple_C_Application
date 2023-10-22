/*
 * This program will output integer in seven-segment display format.
 */
    #include <stdio.h>
    #include <stdlib.h>
    const char segments[10][3][3] = {
               {{' ', '_', ' '},
                    {'|', ' ', '|'},
                    {'|', '_', '|'}}, // 0

               {{' ', ' ', ' '},
                    {' ', ' ', '|'},
                    {' ', ' ', '|'}}, // 1

               {{' ', '_', ' '},
                    {' ', '_', '|'},
                    {'|', '_', ' '}}, // 2

               {{' ', '_', ' '},
                    {' ', '_', '|'},
                    {' ', '_', '|'}}, // 3

               {{' ', ' ', ' '},
                    {'|', '_', '|'},
                    {' ', ' ', '|'}}, // 4

               {{' ', '_', ' '},
                    {'|', '_', ' '},
                    {' ', '_', '|'}}, // 5

               {{' ', '_', ' '},
                    {'|', '_', ' '},
                    {'|', '_', '|'}}, // 6

               {{' ', '_', ' '},
                    {' ', ' ', '|'},
                    {' ', ' ', '|'}}, // 7

               {{' ', '_', ' '},
                    {'|', '_', '|'},
                    {'|', '_', '|'}}, // 8

               {{' ', '_', ' '},
                    {'|', '_', '|'},
                    {' ', '_', '|'}}  // 9
    };

    // print positive input digit
    void printPositiveDigit(int digit) {
        // Loop through each row and column of the segments array
        // i index for array in this array, so it is the row, j for index in i array, so it is the column
        for (int i = 0; i < 3; i++) {
            // print one space in the first column, to fit the position of negative sign
            if (i == 1 || i == 0) {
                printf(" ");
            }
            for (int j = 0; j < 3; j++) {
                // Because the existence of an extra space to fit the negative sign ,
                // without this if condition the third row of my result would not be in shape
                // So I add this condition to print one more extra space at the beginning of third rows
                if(i == 2 && j == 0){
                    printf(" %c", segments[digit][i][j]);
                }
                else{
                    printf("%c", segments[digit][i][j]);
                }
            }
            // Move to the next row of the display
            printf("\n");
        }
    }

    // print positive input digit
    // the algorithm are same as above, just change the left-middle independent column to '_'
    void printNegativeDigit(int digit) {
        // Convert digit to absolute value
        int negativeInput = abs(digit);
        for (int i = 0; i < 3; i++) {
            // Print '-' character in left-middle independent column
            if (i == 0) {
                printf(" ");
            }
            if (i == 1) {
                printf("_");
            }
            for (int j = 0; j < 3; j++) {
                if(i == 2 && j == 0){
                    printf(" %c", segments[negativeInput][i][j]);
                }
                else{
                    printf("%c", segments[negativeInput][i][j]);
                }
            }
            printf("\n");
        }
    }

    int main() {
        int input;
        char state;
        do {
            printf("Please enter an integer from -9 to 9: ");
            scanf("%d", &input);
            // Check if the input is negative and call the appropriate function
            if (input < 0) {
                printNegativeDigit(input);
            } else {
                printPositiveDigit(input);
            }
            printf("You want to continue or stop? (Y/N): ");
            scanf(" %c", &state);
        } while (state == 'Y' || state == 'y');

        return 0;
    }