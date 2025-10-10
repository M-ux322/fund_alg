#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

long long to_10(const char* number, int base) {
    long long res = 0;
    for (int i = 0; number[i] != '\0'; i++) {
        char symbol = number[i];
        int digit;

        if(isdigit(symbol)) {
            digit = symbol - '0';
        } else if (isalpha(symbol)) {
            digit = toupper(symbol) - 'A' + 10;
        } else return -1;
        
        if (digit >= base) return -1;

        res = res * base + digit;
    }

    return res;

}

char* to_base(long long number, int base) {
    char buffer[100];
    if (number == 0) {
        strcpy(buffer, "0");
    }

    int flag = 0;
    if (number < 0) {
        flag = 1;
        number = -number;
    }
    
    int counter = 0;

    while (number != 0) {
        int digit = number % base;

        if (digit < 10) {
            buffer[counter] = '0' + digit;
        } else {
            buffer[counter] = 'A' + digit - 10;
        }
        number /= base;
        counter++;
    }

    char* res = malloc(100 * sizeof(char));

    int index = 0;
    if (flag == 1) {
        res[index++] = '-';
    }
    
    for (int i = counter - 1; i >= 0; i--) {
        res[index++] = buffer[i];
    }
    res[index] = '\0';

    return res;
    
}

int main() {
    int base;
    scanf("%d", &base);
    if (base < 2 || base > 36) {
        printf("Incorrect base");
        return 1;
    }
    char number_str[100];
    scanf("%s", number_str);
    long long max_number = 0;

    while(strcmp(number_str, "Stop") != 0) {
        long long number = to_10(number_str, base);

        if (number == -1) {
            printf("Incorrect number");
            return 1;
        }

        long long number_abs = llabs(number);

        if (number_abs > max_number) {
            if (number == number_abs) {
                max_number = number_abs;
            } else max_number = -number_abs;
            
        }

        scanf("%s", number_str);
    }

    char* result = to_base(max_number, base);
    printf("Max number: %s\n", result);

    free(result);

    int bases[] = {9, 18, 27, 36};
    for (int i = 0; i < 4; i++) {
        printf("Base %d: ", bases[i]);
        result = to_base(max_number, bases[i]);
        printf("%s\n", result);
        free(result);
    }


    return 0;
}