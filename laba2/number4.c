#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

int univers_scan(void* name, char* buffer, int flag_file) {
    int counter = 0;

    if (flag_file) {
        fscanf((FILE*)name, "%99s", buffer);
        counter += strlen(buffer);
    } else {
        const char** str = (const char**)name;
        sscanf(*str, "%99s", buffer);

        *str += strlen(buffer);
        counter += strlen(buffer);
    }
    return counter;
}

int univers_ungetc(int c, void* name, int flag_file) {
    if (flag_file) {
        return ungetc(c, (FILE*)name);
    } else {
        const char** str = (const char**)name;
        (*str)--;
        return c;
    }
}

int Ro_func(char* name, int* result) {

    int counter = 0;
    *result = 0;

     struct Rdigit {
        int value;
        const char* symbol;
    };

    struct Rdigit rim_value[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    for (int i = 0; i < 13; i++) {
        int len = strlen(rim_value[i].symbol);
        while (strncmp(name, rim_value[i].symbol, len) == 0) {
            *result += rim_value[i].value;
            name += len;
            counter += len;
        }
    }
    return counter;
}

int fib_numb(int n, int* fib_mas) {

    if (n <= 0 || fib_mas == NULL) {
        return -1;
    }

    fib_mas[0] = 1;
    int num_f = 2;

    for (int i = 1; i < n; i++) {

        fib_mas[i] = num_f;
        num_f = fib_mas[i - 1] + fib_mas[i];
    }
    return 0;
}

int Zr_func(void* name, unsigned int* result, int flag_file) {

    *result = 0;
    char str[100];
    int len = univers_scan(name, str, flag_file);

    if (len <= 0 || len > 50) {
        return 0;
    }

    int f_mas[len];
    if (fib_numb(len, f_mas) != 0) {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '1') {
            *result += f_mas[i];
        }
    }
    return len;
}

int Cv_func(void* name, int* result, int base, char format, int flag_file) {
    int counter = 0;
    char num[100];
    int len = univers_scan(name, num, flag_file);
    if (len <= 0) {
        return 0;
    }

    if (base < 2 || base > 36) {
        base = 10;
    }

    *result = 0;

    for (int i = 0; num[i] != '\0'; i++) {
        char c = num[i];
        int digit;

        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else {
            //printf("%c", c);
            if (format == 0 && (c >= 'a' && c <= 'z')) {
                digit = c - 'a' + 10;
            } else if (format == 1 && (c >= 'A' && c <= 'Z')) {
                digit = c - 'A' + 10;
            } else {
                break;
            }
        }
        if (digit >= base) {
            break;
        }
        *result = *result * base + digit;
        counter++;
    }

    return counter;
}


int overfscanf(FILE* file_name, const char* flag, ...) {
    va_list args;
    va_start(args, flag);

    const char* flg = flag;
    int counter = 0;

    while(*flg != '\0') {
        if (*flg != '%') {
            int c = fgetc(file_name);
            if (c != *flg) {
                if (c != *flg) {
                    if (c != EOF) ungetc(c, file_name);
                    break;
                }
            }
            flg++;
            continue;
        }
        flg++;

        if (strncmp(flg, "Ro", 2) == 0) {
            int* dest = va_arg(args, int*);
            char buffer[100];
            int len = univers_scan(file_name, buffer, 1);
            counter += len;
            Ro_func(buffer, dest);
            flg += 2;
        }
        else if (strncmp(flg, "Zr", 2) == 0) {
            unsigned int* dest = va_arg(args, unsigned int*);
            counter += Zr_func(file_name, dest, 1);
            flg += 2;
        }
        else if (strncmp(flg, "Cv", 2) == 0) {
            int* dest = va_arg(args, int*);
            int base = va_arg(args, int);
            counter += Cv_func(file_name, dest, base, 1, 1);
            flg += 2;
        }
        else if (strncmp(flg, "CV", 2) == 0) {
            int* dest = va_arg(args, int*);
            int base = va_arg(args, int);
            counter += Cv_func(file_name, dest, base, 0, 1);
            flg += 2;
        } else {
            char spec[3] = {'%', *flg, '\0'};
            counter += vfscanf(file_name, spec, args);
            flg++;
        }

    }
    va_end(args);
    return counter;
}


int oversscanf(const char* str, const char* flag, ...) {
    va_list args;
    va_start(args, flag);

    const char* input_ptr = str;
    const char* flg = flag;
    int counter = 0;

    while(*flg != '\0' && *input_ptr != '\0') {
        if (*flg != '%') {
            if (*input_ptr != *flg) {
                break;
            }
            input_ptr++;
            flg++;
            continue;
        }
        flg++;

        if (strncmp(flg, "Ro", 2) == 0) {
            int* dest = va_arg(args, int*);
            char buffer[100];
            int len = univers_scan((void*)&input_ptr, buffer, 0);
            counter += len;
            Ro_func(buffer, dest);
            flg += 2;
        }
        else if (strncmp(flg, "Zr", 2) == 0) {
            unsigned int* dest = va_arg(args, unsigned int*);
            counter += Zr_func((void*)&input_ptr, dest, 0);
            flg += 2;
        }
        else if (strncmp(flg, "Cv", 2) == 0) {
            int* dest = va_arg(args, int*);
            int base = va_arg(args, int);
            counter += Cv_func((void*)&input_ptr, dest, base, 1, 0);
            flg += 2;
        }
        else if (strncmp(flg, "CV", 2) == 0) {
            int* dest = va_arg(args, int*);
            int base = va_arg(args, int);
            counter += Cv_func((void*)&input_ptr, dest, base, 0, 0);
            flg += 2;
        } else {
            char spec[3] = {'%', *flg, '\0'};
            int len;
            char buffer[100];            
            
            int result = vsscanf(input_ptr, spec, args);
            if (result <= 0) break;
            
            sscanf(input_ptr, "%s%n", buffer, &len);
            input_ptr += len;
            
            flg++;
            counter += len;
        }
    }
    va_end(args);
    return counter;
}


int main() {
    printf("=== Testing overfscanf ===\n");
    FILE* file = fopen("test.txt", "w+");
    if (file) {
        fprintf(file, "XIV 10101 1A 1a 100");
        rewind(file);
        
        int ro_val, cv_val1, cv_val2, zr_val, normal_val;
        int count = overfscanf(file, "%Ro %Zr %Cv %CV %d", 
                              &ro_val, &zr_val, &cv_val1, 16, &cv_val2, 16, &normal_val);
        
        printf("Read %d values:\n", count);
        printf("Ro (Roman): %d\n", ro_val);        // Должно быть 14
        printf("Zr (Fib): %d\n", zr_val);          // Должно быть 12 (10101 в фиб.)
        printf("Cv (hex): %d\n", cv_val1);         // Должно быть 26 (1A в hex)
        printf("CV (hex): %d\n", cv_val2);         // Должно быть 26 (1a в hex)  
        printf("Normal: %d\n", normal_val);        // Должно быть 100
        
        fclose(file);
    }
    
    printf("\n=== Testing oversscanf ===\n");
    const char* test_str = "XIV 10101 1A 1a 100";
    int ro_val2, cv_val3, cv_val4, zr_val2, normal_val2;
    
    int count2 = oversscanf(test_str, "%Ro %Zr %Cv %CV %d", 
                           &ro_val2, &zr_val2, &cv_val3, 16, &cv_val4, 16, &normal_val2);
    
    printf("Read %d values:\n", count2);
    printf("Ro (Roman): %d\n", ro_val2);      // Должно быть 14
    printf("Zr (Fib): %d\n", zr_val2);        // Должно быть 12
    printf("Cv (hex): %d\n", cv_val3);        // Должно быть 26
    printf("CV (hex): %d\n", cv_val4);        // Должно быть 26
    printf("Normal: %d\n", normal_val2);      // Должно быть 100
    
    return 0;
}