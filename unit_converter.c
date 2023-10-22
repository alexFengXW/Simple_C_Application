/*
 * converter.c
 * This program is to do conversions between:
 *  Kilograms and Pounds
 *  Hectares and Acres
 *  Litres and Gallons
 *  Kilometre and Mile
 * @author: Xiaowei Feng
 * @para char functionChoice for conversion choice,
 * @para char order for conversion direction
 * @para float input for user input
 */
#include <stdio.h>
int main(){
    char functionChoice;
    char order;
    float input;

    float conversionKP(float , char);
    float conversionHA(float , char);
    float conversionLG(float, char);
    float conversionKM(float, char);

    while(1){
        printf("\nWhat kind of conversion you want?\n");
        printf("1 for conversion between Kilograms and Pounds \n");
        printf("2 for conversion between Hectares and Acres\n");
        printf("3 for conversion between Litres and Gallons\n");
        printf("4 for conversion between Kilometre and Mile\n");
        printf("5 for quit\n");
        printf("\nYou want to enter: \n");
        scanf("  %c",&functionChoice);

        if(functionChoice == '1') {
            printf("Kilograms to Pounds: K\nPounds to Kilograms: P\n" );
            scanf(" %c",&order);
            printf("Please enter a value: ");
            scanf(" %f",&input);
            printf("Your conversion is: %f " , conversionKP(input, order));
            continue;
        }
        else if(functionChoice == '2') {
            printf("Hectares and Acres: H\nAcres to Hectares: A\n");
            scanf(" %c",&order);
            printf("Please enter a value: ");
            scanf(" %f", &input);;
            printf("Your conversion is: %f " , conversionHA(input,order));
            continue;
        }
        else if(functionChoice == '3') {
            printf("Litres and Gallons: L\nGallons to Litres: G\n");
            scanf(" %c", &order);
            printf("Please enter a value: ");
            scanf(" %f", &input);
            printf("Your conversion is: %f ", conversionLG(input, order));
            continue;
        }
        else if(functionChoice == '4') {
            printf("Kilometre to Mile:K\nMile to Kilometre: M\n");
            scanf(" %c", &order);
            printf("Please enter a value: ");
            scanf(" %f", &input);
            printf("Your conversion is: %f ", conversionKM(input,order));
            continue;
        }
        else if(functionChoice == '5'){
            printf("Thank you!\n");
            break;
        }
        else{
            printf("\nWrong enter, please try again");
            continue;
        }
    }
}

float conversionKP(float value, char order){
    float result;
    if(order == 'K'){
        result = value * 2.20462;
        return result;
    }
    else if(order == 'P'){
        result = value * 0.45359237;
        return result;
    }
    else{
        printf("Wrong input, please try again");
    }
}

float conversionHA(float value, char order){
    float result;
    if(order == 'H'){
        result = value * 2.47105;
        return result;
    }
    else if(order == 'A'){
        result = value * 0.40468;
        return result;
    }
    else{
        printf("Wrong input, please try again");
    }
}

float conversionLG(float value, char order){
    float result;
    if(order == 'L'){
        result = value * 0.264172;
        return result;
    }
    else if(order == 'G'){
        result = value * 3.78541;
        return result;
    }
    else{
        printf("Wrong input, please try again");
    }
}

float conversionKM(float value, char order){
    float result;
    if(order == 'K'){
        result = value * 0.621371;
        return result;
    }
    else if(order == 'M'){
        result = value * 1.609344;
        return result;
    }
    else{
        printf("Wrong input, please try again");
    }
}

