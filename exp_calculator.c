/*
 * This program will calculate exponential number
 * ex. 2^34, 21^97 and even negative exponent like 4^-9 etc.
 */
#include <stdio.h>
#include <stdlib.h>
int main(){
    double base;
    int exponent;
    int loopEnd = 0;
    while(loopEnd == 0) {
        float calculator(double, int);
        printf("\nYou can enter any non-zero number for base, and any integer for exponent.\n");
        printf("To stop, enter 0 for exponent and the program would terminate.\n");
        printf("\nYour base value is:  ");

        // Using conversion specifier %lf for double
        scanf("%lf", &base);
        printf("\nYour exponent value is:  ");
        scanf("%d", &exponent);

        // I define three cases
        // When the exponent is smaller than 0, result is 1/the value of calculator class
        if (exponent < 0) {
            printf("\nBase value is: %lf and Exponent value: %d, your result is: %f\n",
                   base, exponent, 1 / calculator(base, exponent));

            // When exponent is greater than 0, the result would be the value of calculator class
        } else if (exponent > 0) {
            printf("\nBase value is: %lf and Exponent value: %d, your result is: %f\n",
                   base, exponent, calculator(base, exponent));

            // When exponent is 0, the result would be 1 regardless of the value of base
        } else {
            printf("\nYour exponent is 0, Program terminated.\nYour result is: %d", 1);
            loopEnd = 1;
        }
    }
    return 0;

}
float calculator(double base, int exp) {
    // Because I differ negative, positive and zero in main(), so the exponent I got here must be absolute value
    // I use abs() function in <stdlib.h> library to achieve that
    exp = abs(exp);
    float result;

    // If exponent is 1, return base itself
    if(exp == 1){
        return base;
    }

    // If exponent is even, as the hint shown in assignment page, the result is (a^(n/2)) * (a^(n/2))
    // So I use recursion to achieve that
    else if(exp % 2 == 0){
        result = (calculator(base, exp/2)) * (calculator(base, exp/2));
        return result;
    }

    // If exponent is even, as the hint shown in assignment page, the result is (a^(n-1/2)) * (a^(n-1/2)) * a
    else{
        result = (calculator(base, (exp-1)/2)) * (calculator(base, (exp-1)/2)) * base;
        return result;
    }
}
