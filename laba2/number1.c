#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

int NOD(int a, int b) {

    while (a != b) {
        if (a > b) a = a - b;
        else b = b - a;
    }
    return a;
}

bool is_prime(int num) {

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
            break;
        }
    }
    if (num < 2) return false;
    return true;
}

bool check(int base, double number) {
    int up = (int)number;
    int down = 1;
    while (up != number) {
        up = (int)(number *= 10);
        down *= 10;
    }

    int nod;
    if ((nod = NOD(up, down)) != 1) {
        up /= nod;
        down /= nod;
    }

    for (int i = 2; i <= base; i++) {

        if (is_prime(i) && base % i == 0) {
            while (down % i == 0) {
                down /= i;
            }
        }
    }


    if (down != 1) {
        return false;
    } else return true;

}

void function(int base, ...) {

    va_list args;
    va_start(args, base);

    double number;
    while ((number = va_arg(args, double)) != -1.0) {
        if (check(base, number)) {
            printf("Number %f has finite representation in base %d\n", number, base);
        } else printf("Number %f has not finite representation in base %d\n", number, base);
    }

    return;

}


int main() {

    printf("Test 1: Base 2\n");
    function(2, 0.5, 0.25, 0.125, 0.1, -1.0);
    printf("\n");

    printf("Test 2: Base 8\n");
    function(8, 0.5, 0.25, 0.125, 0.1, -1.0);
    printf("\n");

    printf("Test 3: Base 3\n");
    function(3, 0.5, 0.333, 0.25, 0.1, -1.0);
    printf("\n");

    printf("Test 4: Base 16\n");
    function(16, 0.5, 0.25, 0.125, 0.0625, 0.1, -1.0);
    printf("\n");

    return 1;
}