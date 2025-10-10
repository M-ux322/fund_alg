#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void prime(int t) {
    bool number_massiv[t + 1];
    int prime_massive[1000];
    int counter = 0;
    const int MAX_SIZE = 10000;

    for (int i = 0; i <= MAX_SIZE; i++) {
            number_massiv[i] = true;
    }
    
    for (int i = 2; i * i <= MAX_SIZE; i++) {
        if (number_massiv[i]) {
            for (int j = i + i; j < MAX_SIZE; j += i) {
                number_massiv[j] = false;
                //printf("%d\n", j);
            }
        }
    }

    number_massiv[0] = number_massiv[1] = false;

    for (int i = 0; i < MAX_SIZE; i++) {
        if (number_massiv[i]) {
            counter++;
            prime_massive[counter] = i;
        }
    }

    for (int i = 0; i < t; i++) {
        int num;
        if (scanf("%d", &num) != 1 || num < 0) {
            printf("Error: incorrect numbers format\n");
            return;
        }
        printf("%d\n", prime_massive[num]);
    }
    return;
}

int main() {
    int T;


    printf("Enter the number of queries: ");
    scanf("%d", &T);
    if (T < 0) {
        printf("Error: incorrect numbers format\n");
        return 0;
    }

    prime(T);
    return 0;
}