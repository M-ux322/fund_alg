#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum kOpts {
    OPT_H,
    OPT_P,
    OPT_S,
    OPT_E,
    OPT_A,
    OPT_F
} kOpts;

typedef void (*callback_t) (int);

bool IsValidNumber(const char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    
    return true;
}

int GetOpts(int argc, char** argv, kOpts *option, int *number) {
    for (int i = 1; i < argc; ++i) {
        char* proceeded_string = argv[i];
        if (i == 1) {
            // -
            // h p
            if (proceeded_string[0] != '-') {
                return 1;
            }

            switch (proceeded_string[1])
            {
            case 'h':
                *option = OPT_H;
                break;
            case 'p':
                *option = OPT_P;
                break;
            case 's':
                *option = OPT_S;
                break;
            case 'e':
                *option = OPT_E;
                break;
            case 'a':
                *option = OPT_A;
                break;
            case 'f':
                *option = OPT_F;
                break;
            default:
                return 1;
            }
        } else {
            if (!IsValidNumber(proceeded_string)) {
                printf("Error: incorrect number format\n");
                return 1;
            }
            *number = atoi(proceeded_string);
        }

    }
    return 0;
}

void HandlerOptH(int num) {
    if (num <= 0 || num > 100) {
        printf("Error: number must be between 1 and 100\n");
        return;
    }
    for (int i = 1; i <= 100; ++i) {
        if (!(i % num)) {
            printf("%d\n", i);
        }
    }
    return;
}


void HandlerOptP(int num) {
    if (num <= 0 || num > INT_MAX) {
        printf("Error: number must be positive and not exceed %d\n", INT_MAX);
        return;
    }
    int up = ceil(sqrt(num));
    bool check = true;
    if (num == 1) {
        check = false;
    }
    for (int i = 2; i < up + 1; i++) {
        if (num % i == 0) {
            check = false;
            break;
        }
    }
    printf("Number %d %sis prime", num, check ? "" : "not ");
    return;
}

void HandlerOptS(int num) {
    if (num < 0 || num > INT_MAX) {
        printf("Error: number must be non-negative and not exceed %d\n", INT_MAX);
        return;
    }
    char str_num[100];
    sprintf(str_num, "%x", num);
    int length = strlen(str_num);
    for (int i = 0; i < length; i++) {
        printf("%c\n", str_num[i]);
    }
    return;
}

void HandlerOptE(int num) {
    if (num <= 0 || num > 10) {
        printf("Error: number must be between 1 and 10\n");
        return;
    }
    double st = 1;
        if (num > 10) {
        printf("x should not exceed 10");
        return;
    }
    for (int i = 1; i < 11; i++) {
        st *= num;
        printf("%d^%d = %0.f\n", num, i, st);
    }
    return; 
}

void HandlerOptA (int num) {
    if (num <= 0 || num > INT_MAX) {
        printf("Error: number must be positive and not exceed %d\n", INT_MAX);
        return;
    }
    int sum = 0;
    if ((1 + num) * num / 2 - (num - 1) * num / 2 != num) {
        printf("Overflow");
    }

    sum = (1 + num) * num / 2;
    printf("%d", sum);
    return; 
}

void HandlerOptF (int num) {
    if (num < 0 || num > 20) {
        printf("Error: number must be between 0 and 20 (factorial limit)\n");
        return;
    }
    long long pr = 1;
    for (int i = 1; i <= num; i++) {
        long long a = pr * i;
        
        pr *= i;
        if ((pr * i) / i != pr) {
            printf("Error: number must be between 0 and 20 (factorial limit)\n");
            return;
        }
    }
    printf("%lli", pr);
    return;
}

int main (int argc, char** argv) {
    
    kOpts opt = OPT_H;
    int procceed_number = 0;

    callback_t handlers[6] = {
        HandlerOptH,
        HandlerOptP,
        HandlerOptS,
        HandlerOptE,
        HandlerOptA,
        HandlerOptF   
    };

    if (GetOpts(argc, argv, &opt, &procceed_number)) {
        printf("%s", "Incorrect option");
        return 1;
    }


    handlers[opt](procceed_number);
    return 0;
}
