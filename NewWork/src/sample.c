
/**
*
*
*
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void charToBinary(char* destination, char a_char);
char  binaryToChar(char* binary_rep);


int main(int argc, char* argv[]){
    char test[9];
    char target = 'h';
    charToBinary(test, target);
    printf("chr: %c\n", target);
    printf("asc: %i\n", target);
    printf("bin: %s\n", test);

    char test_two[] = "01100010";
    char testchar = binaryToChar(test_two);
    printf("chr: %c\n", testchar);
    return 0;
}


void charToBinary(char* destination, char a_char){
    char binary_rep[9];
    int remainders[9];
    int quotient = a_char;
    int remainder = 0;
    int count = 0;

    while(quotient > 0){
        remainder = quotient % 2;
        quotient = quotient / 2;
        remainders[count] = remainder;
        count++;
    }

    for(int i = (count - 1); 0 <= i; i--){
        char digit[2];
        sprintf(digit, "%d", remainders[i]);
        strcat(binary_rep, digit);
    }

    int binstr_len = 0;
    char target = binary_rep[binstr_len];
    while(target != '\0'){
        binstr_len++;
        target = binary_rep[binstr_len];
    }

    printf("%i\n", binstr_len);
    while(binstr_len < 8){
        char tempstr[9];
        tempstr[0] = '0';
        strcat(tempstr, binary_rep);
        strcpy(binary_rep, tempstr);
        binstr_len++;
    }

    strcpy(destination, binary_rep);
}

char binaryToChar(char* binary_rep){
    int power = 0;
    int sum = 0;
    for(int i = 7; 0 <= i; i--){
        int base = binary_rep[i] - '0';
        sum += (base * (1 << power));
        power++;
    }

    char ascii = sum;
    return ascii;
}