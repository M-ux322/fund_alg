#include <stdio.h>


int increment(int x) {
    int m = 1;
    while (x & m) {
        x = x ^ m;
        m = m << 1;
    }
    return x | m;
}

int decrement(int x) {
    int m = 1;
    while ((x & m) == 0) {
        x = x | m;
        m = m << 1;
        if (m == 0) break;
    }
    return x ^ m;
}


void to_2r(int number) {

    char* str = "0123456789abcdefghigklmnopqrstuvwxyz";

    if (number == 0) {
        putchar('0');
        return;
    }

    int r = 1;
    while (r < 6) {
        char buffer[100];
        int i = 0;
        int num = number;

        printf("Base 2^%d:", r);

        while (num != 0) {
            int mask = decrement(1 << r);
            unsigned int digit = num & mask;
            //if (digit < 10) {
                buffer[i] = str[digit];
            //} else {
                //buffer[i] = str[digit];               
            //}
            
            num = num >> r;
            i = increment(i);
        }

        int j = decrement(i);
        while (j >= 0) {
            putchar(buffer[j]);
            j = decrement(j);
        }
        putchar('\n');
        
        r = increment(r);
    }
    return;
}


int main() {

    printf("Number 2:\n");
    to_2r(2);
    printf("\n");

    printf("Number 4:\n");
    to_2r(4);
    printf("\n");

    printf("Number 8:\n");
    to_2r(8);
    printf("\n");

    printf("Number 16:\n");
    to_2r(16);
    printf("\n");

    printf("Number 32:\n");
    to_2r(32);
    printf("\n");
    return 0;
}