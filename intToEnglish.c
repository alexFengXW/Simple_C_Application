/*
 * intToEnglish.c
 *  This program is to do the conversion between integer and English words
 * @author: Xiaowei Feng
 * @para: int input for prompting the user to input an integer (1-999)
 * @para: int digit_number for recording the number of digits in user's input
 * @para: int ones for the right digit
 * @para: int tens for the middle digit
 * @para: int hundreds for the left digit
 * @para: char *single[] for string array to record the single numbers (1-9)
 * @para: char *specialDecimals[] for string array to record the special spellings (10-19)
 * @para: char *tenDecimals[] for string array to record the decimal numbers (10-90)
 */
#include <stdio.h>
int main() {
    int input;
    int digit_number;

    char *single[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *specialDecimals[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                               "eighteen", "nineteen"};
    char *tenDecimals[] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    while (1) {
        printf("Please enter a value (1-999, 0 to quit): ");
        scanf("%d", &input);

        if(input == 0) {
            printf("Thank you!");
            break;
        }

        if (input > 999 || input < 0) {
            printf("Invalid input. Please enter a number between 1 and 999.\n");
            continue;
        }

        int input_value = input;
        digit_number = 0;
        while (input_value != 0) {
            input_value /= 10;
            digit_number++;
        }

        int ones = input % 10;
        int tens = (input / 10) % 10;
        int hundreds = (input / 100) % 10;

        // Single digit
        if (digit_number == 1) {
            printf("You entered the number: %s\n", single[input - 1]);
        }

        // Decimal digit
        if (digit_number == 2) {
            if(tens < 2){
                printf("You entered the number: %s\n", specialDecimals[ones]);
            }
            else if(ones == 0){
                printf("You entered the number: %s\n", tenDecimals[tens-2]);
            }
            else{
                printf("You entered the number: %s and %s\n", tenDecimals[tens - 2], single[ones - 1]);
            }
        }

        // Hundred digit
        if (digit_number == 3) {
            // 101,204,309,407...
            if(tens == 0 && ones != 0){
                if(hundreds == 1) printf("You entered the number: %s hundred and %s\n", single[hundreds - 1], single[ones - 1]);
                else printf("You entered the number: %s hundreds and %s\n",single[hundreds - 1], single[hundreds - 1]);
            }
                // 100,200,300,800...
            else if (tens < 1 && ones == 0){
                if(hundreds == 1) printf("You entered the number: %s hundred\n", single[hundreds - 1]);
                else printf("You entered the number: %s hundreds\n", single[hundreds - 1]);
            }
                // 110,115,318,517...
            else if(tens < 2){
                if(hundreds == 1) printf("You entered the number: %s hundred and %s\n",single[hundreds - 1],specialDecimals[ones]);
                else printf("You entered the number: %s hundreds and %s\n",single[hundreds - 1], specialDecimals[ones]);
            }

                // 130,150,250,380...
            else if(tens >= 2 && ones == 0){
                if(hundreds == 1) printf("You entered the number: %s hundred and %s\n", single[hundreds - 1], tenDecimals[tens-2]);
                else printf("You entered the number: %s hundreds and %s\n", single[hundreds - 1], tenDecimals[tens-2]);
            }

                // 284,351,821,999...
            else{
                if(hundreds  == 1) printf("You entered the number: %s hundred and %s %s\n", single[hundreds - 1], tenDecimals[tens - 2], single[ones - 1]);
                else printf("You entered the number: %s hundreds and %s %s\n", single[hundreds - 1],tenDecimals[tens - 2], single[ones - 1]);
            }

        }
    }
    return 0;
}
