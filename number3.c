#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>


typedef enum {
    OPT_Q,
    OPT_M,
    OPT_T
} kOpts;



bool IsValidNumber(const char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    char* endptr;
    strtof(str, &endptr);

    return (endptr != str) && (*endptr == '\n');
    
}


int getopts(int argc, char** argv, kOpts *option, double** number) {
   // for (int i = 1; i < argc; i++) {
        char* processed_str = argv[1];
        if (processed_str[0] != '-') {
            return 1;
        }
        switch (processed_str[1]) 
        {
        case 'q':
            *option = OPT_Q;
            if (argc != 6) {
                return 1;
            }
            break;
        case 'm':
            *option = OPT_M;
            if (argc != 4) {
                return 1;
            }
            break;
        case 't':
            *option = OPT_T;
            if (argc != 6) {
                return 1;
            }
            break;
        default:
            return 1;
        }
    //}

    int num_count = (*option == OPT_M) ? 2 : 3;
    *number = (double*)malloc(num_count * sizeof(double));
    
    int i = 0;
    if (num_count == 3) {
        if (!IsValidNumber(argv[2])) {
            printf("Error: incorrect number format\n");
            return 1;
        }
        //double eps = atof(argv[2]);
        for (; i < num_count; i++) {
            if (!IsValidNumber(argv[3 + i])) {
                printf("Error: incorrect number format\n");
                return 1;
        }
            (*number)[i] = atof(argv[3 + i]);
        //printf("%f", number[i])
        }
    } else {
        for (; i < num_count; i++) {
            (*number)[i] = atof(argv[2 + i]);
        //printf("%f", number[i]);
        }
    }
    
    return 0;
}

double ur(double eps, double a, double b, double c, double x_1, double x_2) {

    while (fabs(x_1 - x_2) > eps) {
        double x = (x_1 + x_2) / 2;

        double f_1 = a * pow(x_1, 2) + b * x_1 + c;
        double f_2 = a * pow(x, 2) + b * x + c;
        if (f_1 * f_2 < 0) {
            x_2 = x;
        } else x_1 = x;
    }
    return x_1;
}

void HandlerOptQ(double* arr, double eps) {
    double disc;
    for (int i = 0; i < 3; i++) {
        double a = arr[i], b = arr[(i + 1) % 3], c = arr[(i + 2) % 3];
        disc = pow(b, 2) - 4 * a * c;
        //printf("%f, %f, %f, %f\n", a, b, c, disc);
        if (disc > 0) {
            double x_1 = (-b + sqrt(disc)) / (2 * a);
            double x_2 = (-b - sqrt(disc)) / (2 * a);
            //double x_1 = ur(eps, a, b, c, x_11 - 0.01, x_11 + 0.01);
            //double x_2 = ur(eps, a, b, c, x_22 - 0.01, x_22 + 0.01);

            printf("%f, %f\n", x_1, x_2);
        } else if (fabs(disc) < eps) {
            double x = (-b) / (2 * a);
            printf("%f/n", x);
        }
        
    return;
    }
}

void HandlerOptM(double* arr) {
    int x_1 = (int)arr[0];
    int x_2 = (int)arr[1];

    if (x_1 % x_2 == 0) {
        printf("True");
    } else printf("False");
    return;
}

void HandlerOptT(double* arr, double eps) {
    double a = arr[0], b = arr[1], c = arr[2];
    if ((a * a - b * b - c * c) > eps || (-a * a + b * b - c * c) > eps || (-a * a - b * b + c * c) > eps) {
        printf("False");
    } else printf("True");
    
    return;
}

int main(int argc, char** argv) {
    double eps = atof(argv[2]);

    kOpts opt = OPT_Q;
    double* numbers_arr = NULL;


    if (getopts(argc, argv, &opt, &numbers_arr)) {
        printf("Incorrect option");
        return 1;
    }

    switch (opt) {
        case OPT_Q:
            HandlerOptQ(numbers_arr, eps);
            break;
        case OPT_M:
            HandlerOptM(numbers_arr);
            break;
        case OPT_T:
            HandlerOptT(numbers_arr, eps);
            break;
    }
    free(numbers_arr);

    return 0;

}