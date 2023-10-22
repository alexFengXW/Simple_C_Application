// This program can do arithmetic operations for + - * /
#include <stdio.h>
#include <stdlib.h>

char get_op(void);
float get_num(void);
float sim_sub_exp(float);
float sim_exp(void);
float md_exp(void);
float md_sub_exp(float);

char get_op(void){
    char op;
    // If operator is whitespace, continue the loop so that it gets next operator.
    while ((op = getchar()) == ' ') {
        continue;
    }
    return op;
}

float get_num(void) {
    float num;
    // Check if the next character in the input is a minus sign
    int next_char = get_op();
    if (next_char == '-') {
        // If it is, num = -num
        scanf("%f", &num);
        num = -num;
    }
    else {
        // Otherwise, push the character back to the input stream and read the number with scanf()
        ungetc(next_char, stdin);
        scanf("%f", &num);
    }
    return num;
}

float sim_sub_exp(float sub_exp){
    char next_op = get_op();
    // If the next operator is a newline character, return sub_exp
    if (next_op == '\n') {
        // Push the newline character back to the standard input stream
        ungetc(next_op, stdin);
        return sub_exp;
    }

    // Otherwise, compute the next character in the expression
    // Add the next term to the current sub_exp value
    // OR subtract the next term from the current sub_exp value
    else if (next_op == '+') {
        float next_md_exp = md_exp();
        sub_exp = sub_exp + next_md_exp;
    }
    else if (next_op == '-') {
        float next_md_exp = md_exp();
        sub_exp = sub_exp - next_md_exp;
    }

    // If the next operator is not valid, print an error message and exit the program
    else {
        printf("Invalid operator entered.\nOnly '+', '-', '*', and '/' are allowed.\nProgram terminated.");
        exit(1);
    }

    // call the function recursively
    return sim_sub_exp(sub_exp);
}

float sim_exp(void) {
    float m = md_exp();
    return sim_sub_exp(m);
}

float md_sub_exp(float sub_exp) {
    char next_op = get_op();
    // If the next operator is +, -, or \n, return the sub_exp
    if (next_op == '+' || next_op == '-' || next_op == '\n') {
        // Push the operator back to the standard input stream
        ungetc(next_op, stdin);
        return sub_exp;
    }
    // Otherwise, the next operator is * or /
    // Multiply the current sub_exp value by the next number
    // Divide the current sub_exp value by the next number
    else if (next_op == '*') {
        float next_num = get_num();
        sub_exp = sub_exp * next_num;
    }
    else if (next_op == '/') {
        float next_num = get_num();
        sub_exp = sub_exp / next_num;
    }

    // If the next operator is not valid, print an error message and exit the program
    else {
        printf("Invalid operator entered.\nOnly '+', '-', '*', and '/' are allowed.\nProgram terminated.");
        exit(1);
    }

    // call the function recursively
    return md_sub_exp(sub_exp);
}

float md_exp(void) {
    float m = get_num();
    return md_sub_exp(m);
}

int main() {
    // Set state to 'Y' by default
    char state = 'Y';
    float answer;

    // while loop when state is 'Y'
    while (state == 'Y' || state == 'y') {
        printf("Make sure you only enter:+ - * /, any other operator sign would terminate the program directly.\n"
               "Please input a simple arithmetic expression: ");
        answer = sim_exp();
        printf("Result is %f\n", answer);
        // ask user to choose continue or stop
        printf("Do you want to continue input a arithmetic expression?\nY for yes and N for no: ");
        scanf(" %c", &state);
    }
    return 0;
}










