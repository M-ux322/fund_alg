#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

int univers_putc(char c, void* name, int flag_file) {
    if (flag_file) {
        fputc(c, (FILE*)name);
    } else {
        char** str = (char**)name;
        **str = c;
        (*str)++;
    }
    return 1;
}

int univers_puts(const char* str, void* name, int flag_file) {
    int len = strlen(str);

    if (flag_file) {
        fputs(str, (FILE*)name);
    } else {
        char** str_copy = (char**)name;
        strcpy(*str_copy, str);
        *str_copy += len;
    }
    return len;
}

int Ro_func(void* file_name, int num, int flag) {

    int counter = 0;

    if (num <= 0) {
        univers_putc('0', file_name, flag);
        counter++;
        return counter;
    }

    struct Rdigit {
        int value;
        const char* symbol;
    };

    struct Rdigit rim_value[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    int n = num;
    for (size_t i = 0; n > 0; i++) {
        while (n >= rim_value[i].value) {
            univers_puts(rim_value[i].symbol, file_name, flag);
            counter += strlen(rim_value[i].symbol);
            n -= rim_value[i].value;
        }
    }
    return counter;
}


int* fib_numb(int n, int* counter) {

    if (n < 0) {
        return NULL;
    }

    int capacity = 10;

    int* fib_mas = malloc(capacity * sizeof(int));

    if (fib_mas == NULL) {
        return NULL;
    }

    fib_mas[0] = 1;
    *counter = 1;
    int num_f = 2;

    for (int i = 1; num_f <= n; i++) {
        if (i >= capacity) {
            int new_capacity = capacity * 2;
            int* new_fib_mas = realloc(fib_mas, new_capacity * sizeof(int));

            if (new_fib_mas == NULL) {
                free(fib_mas);
                return NULL;
            }
            fib_mas = new_fib_mas;
            capacity = new_capacity;
        }

        fib_mas[i] = num_f;
        //printf("%d\n", fib_mas[i]);
        num_f = fib_mas[i - 1] + fib_mas[i];
        //printf("%d", num_f);
        *counter = i + 1;


    }
    //printf("%d", *counter);
    return fib_mas;
}


int Zr_func(void* file_name, int num, int flag) {

    if (num == 0) {
        univers_putc('1', file_name, flag);
    }


    int f_counter;
    int* fib = fib_numb(num, &f_counter);
    int* mas = calloc(f_counter, sizeof(int));
    f_counter--;


    if (num <= 0) {
        return 1;
    }

    while (num != 0) {
        int i = 0;
        for (; i < f_counter; i++) {
            //printf("%d\n", fib[i]);

            if (fib[i] > num) {
                //printf("%d", fib[i]);
                
                i--;
                break;
            }
        }
        num -= fib[i];
        mas[i] = 1;
        //printf("%d, %d\n", fib[i], mas[i]);
       
    }
    mas[f_counter + 1] = 1;

    for (int i = 0; i <= f_counter + 1; i++) {
        univers_putc(mas[i] + '0', file_name, flag);
    }

    return f_counter + 2;
}

int Cv_func(void* file_name, int num, int base, char format, int flag) {
    if (base < 2 || base > 36) {
        if (flag) {
            fprintf((FILE*)file_name, "%d", num);
        } else {
            sprintf((char*)file_name, "%d", num);
        }
        return 0;
    }

    char numb[100];
    int i = 0;

    if (num == 0) {
        univers_putc('0', file_name, flag);
        return 0;
    }

    while (num != 0) {
        int digit = num % base;
        if (digit < 10) {
            numb[i] = digit + '0';
        } else {
            if (format == 0) {
                numb[i] = digit + 'a' - 10;
            } else {
                numb[i] = digit + 'A' - 10;
            }
        }
        num /= base;
        i++;
    }
    numb[i] = '\0';
    int counter = i;
    i--;

    while(i >= 0) {
        univers_putc(numb[i], file_name, flag);
        i--;
    }

    return counter;
}

int to_func(void* file_name, char* num, int base, char format, int flag) {
    if (base < 2 || base > 36) {
        base = 10;
    }

    int res = 0;

    for (int i = 0; num[i] != '\0'; i++) {
        char c = num[i];
        int digit;

        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else {
            if (format == 0 && (c >= 'a' && c <= 'z')) {
                digit = c - 'a' + 10;
            } else if (format == 1 && (c >= 'A' && c <= 'Z')) {
                digit = c - 'A' + 10;
            } else {
                univers_puts("-1", file_name, flag);
                return 1;
            }
        }
        if (digit >= base) {
            univers_puts("-1", file_name, flag);
            return 1;
        }
        res = res * base + digit;
    }

    int counter;
    if (flag) {
        counter = fprintf((FILE*)file_name, "%d", num);
    } else {
        counter = sprintf((char*)file_name, "%d", num);
    }

    return counter;
}

int mi_func(void* file_name, int num, int flag) {
    char number[100];
    itoa(abs(num), number, 2);

    int len = strlen(number);
    char new_number[100];
    int j = 0;

    if (len < 32) {
        for (; j < 32 - len; j++) {
            if (num >= 0) {
                new_number[j] = '0';
            } else {
                new_number[j] = '1';
            }
        }
    }

    for (int i = 0; number[i] != '\0'; i++) {
        if (num < 0) {
            if (number[i] == '1') {
                number[i] = '0';
            } else {
                number[i] = '1';
            }
        }
        new_number[j] = number[i];
        j++;
    }

    new_number[j] = '\0';
    int counter = j;
    j--;

    if (num >= 0) {
        for (int i = 31; i >= 0; i -= 8) {
            for (int j = 7; j >= 0; j--) {
                univers_putc(new_number[i - j], file_name, flag);
            }
            if (i > 7) {
                univers_putc(' ', file_name, flag);
                counter++;
             }
        }
        return counter;
    }

    while(j >= 0) {
        if (new_number[j] == '1') {
            new_number[j] = '0';
        } else {
            new_number[j] = '1';
            break;
        }
        j--;
    }

    for (int i = 31; i >= 0; i -= 8) {
        for (int j = 7; j >= 0; j--) {
            univers_putc(new_number[i - j], file_name, flag);
        }
        if (i > 7) {
            univers_putc(' ', file_name, flag);
            counter++;
        }
    }

    return counter;
}

int mu_func(void* file_name, int num, int flag) {
    char  number[100];
    itoa(num, number, 2);

    int len = strlen(number);
    unsigned char new_number[100];
    int j = 0;

    if (len < 32) {
        for (; j < 32 - len; j++) {
            new_number[j] = '0';
        }
    }

    for (int i = 0; number[i] != '\0'; i++) {
        new_number[j] = number[i];
        j++;
    }

    new_number[j] = '\0';
    int counter = j;
    j--;

    for (int i = 31; i >= 0; i -= 8) {
        for (int j = 7; j >= 0; j--) {
            univers_putc(new_number[i - j], file_name, flag);
        }
        if (i > 7) {
            univers_putc(' ', file_name, flag);
            counter++;
        }
    }
    return counter;
}

int md_func(void* file_name, double num, int flag) {
    unsigned char* bytes = (unsigned char*)&num;

    for (int i = 0; i < 8; i++) {
        unsigned char byte = bytes[i];
        
        int masks[8] = {128, 64, 32, 16, 8, 4, 2, 1};
        
        for (int bit = 0; bit < 8; bit++) {
            if (byte & masks[bit]) {
                univers_putc('1', file_name, flag);
            } else {
                univers_putc('0', file_name, flag);
            }
        }
        
        if (i < 7) univers_putc(' ', file_name, flag);
    }
    
    return 71;
}

int mf_func(void* file_name, float num, int flag) {
    unsigned char* bytes = (unsigned char*)&num;

    for (int i = 0; i < 4; i++) {
        unsigned char byte = bytes[i];
        
        int masks[8] = {128, 64, 32, 16, 8, 4, 2, 1};
        
        for (int bit = 0; bit < 8; bit++) {
            if (byte & masks[bit]) {
                univers_putc('1', file_name, flag);
            } else {
                univers_putc('0', file_name, flag);
            }
        }
        
        if (i < 3) univers_putc(' ', file_name, flag);
    }
    
    return 35; 
}

int overfprintf(FILE* file_name, const char* flag, ...) {

    const char* flg = flag;
    va_list args;
    va_start(args, flag);

    size_t counter = 0;

    while (*flg != '\0') {
        if (*flg != '%') {
            fputc(*flg, file_name);
            flg++;
            counter++;
            continue;
        }
        flg++;

        if (strncmp(flg, "Ro", 2) == 0) {
            int num = va_arg(args, int);
            counter += Ro_func(file_name, num, 1);
            flg += 2;
        }
        else if (strncmp(flg, "Zr", 2) == 0) {
            unsigned int num = va_arg(args, unsigned int);
            counter += Zr_func(file_name, num, 1);
            flg += 2;
        }
        else if (strncmp(flg, "Cv", 2) == 0) {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            counter += Cv_func(file_name, num, base, 0, 1);
            flg += 2;
        }
        else if (strncmp(flg, "CV", 2) == 0) {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            counter += Cv_func(file_name, num, base, 1, 1);
            flg += 2;
        }
        else if (strncmp(flg, "to", 2) == 0) {
            char* num = va_arg(args, char*);
            int base = va_arg(args, int);
            counter += to_func(file_name, num, base, 0, 1);
            flg += 2;
        }
        else if (strncmp(flg, "TO", 2) == 0) {
            char* num = va_arg(args, char*);
            int base = va_arg(args, int);
            counter += to_func(file_name, num, base, 1, 1);
            flg += 2;
        }
        else if (strncmp(flg, "mi", 2) == 0) {
            int num = va_arg(args, int);
            counter += mi_func(file_name, num, 1);
            flg += 2;
        } 
        else if (strncmp(flg, "mu", 2) == 0) {
            unsigned int num = va_arg(args, unsigned int);
            counter += mu_func(file_name, num, 1);
            flg += 2;
        } 
        else if (strncmp(flg, "md", 2) == 0) {
            double num = va_arg(args, double);
            counter += md_func(file_name, num, 1);
            flg += 2;
        } 
        else if (strncmp(flg, "mf", 2) == 0) {
            double value = va_arg(args, double);
            float num = (float)value;
            counter += mf_func(file_name, num, 1);
            flg += 2;
        } 
        else {
            char str[3] = {'%', *flg, '\0'};
            counter += vfprintf(file_name, str, args);
            flg ++;
        }
    }
    va_end(args);
    return counter;
}

int oversprintf(char* str, const char* flag, ...) {
    const char* flg = flag;
    va_list args;
    va_start(args, flag);

    size_t counter = 0;
    char* current_pos = str;

    while (*flg != '\0') {
        if (*flg != '%') {
            *current_pos = *flg;
            current_pos++;
            counter++;
            flg++;
            continue;
        }
        flg++;

        int written_chars = 0;

        if (strncmp(flg, "Ro", 2) == 0) {
            int num = va_arg(args, int);
            char* temp_ptr = current_pos;
            written_chars = Ro_func(&temp_ptr, num, 0);
            current_pos = temp_ptr;
            counter += written_chars;
            flg += 2;
        }
        else if (strncmp(flg, "Zr", 2) == 0) {
            unsigned int num = va_arg(args, unsigned int);
            char* temp_ptr = current_pos;
            written_chars = Zr_func(&temp_ptr, num, 0);
            current_pos = temp_ptr;
            counter += written_chars;
            flg += 2;
        }
        else if (strncmp(flg, "Cv", 2) == 0) {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char* temp_ptr = current_pos;
            written_chars = Cv_func(&temp_ptr, num, base, 0, 0);
            current_pos = temp_ptr;
            counter += written_chars;
            flg += 2;
        }
        else if (strncmp(flg, "CV", 2) == 0) {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char* temp_ptr = current_pos;
            written_chars = Cv_func(&temp_ptr, num, base, 1, 0);
            current_pos = temp_ptr;
            counter += written_chars;
            flg += 2;
        }
        else if (strncmp(flg, "to", 2) == 0) {
            char* num = va_arg(args, char*);
            int base = va_arg(args, int);
            char* temp_ptr = current_pos;
            written_chars = to_func(&temp_ptr, num, base, 0, 0);
            current_pos = temp_ptr;
            counter += written_chars;
            flg += 2;
        }
        else if (strncmp(flg, "TO", 2) == 0) {
            char* num = va_arg(args, char*);
            int base = va_arg(args, int);
            char* temp_ptr = current_pos;
            written_chars = to_func(&temp_ptr, num, base, 1, 0);
            current_pos = temp_ptr;
            counter += written_chars;
            flg += 2;
        }
        else if (strncmp(flg, "mi", 2) == 0) {
            int num = va_arg(args, int);
            char* temp_ptr = current_pos;
            written_chars = mi_func(&temp_ptr, num, 0);
            current_pos = temp_ptr;
            counter += written_chars;
            flg += 2;
        } 
        else if (strncmp(flg, "mu", 2) == 0) {
            unsigned int num = va_arg(args, unsigned int);
            char* temp_ptr = current_pos;
            written_chars = mu_func(&temp_ptr, num, 0);
            current_pos = temp_ptr;
            counter += written_chars;
            flg += 2;
        } 
        else if (strncmp(flg, "md", 2) == 0) {
            double num = va_arg(args, double);
            char* temp_ptr = current_pos;
            written_chars = md_func(&temp_ptr, num, 0);
            current_pos = temp_ptr;
            counter += written_chars;
            flg += 2;
        } 
        else if (strncmp(flg, "mf", 2) == 0) {
            double value = va_arg(args, double);
            float num = (float)value;
            char* temp_ptr = current_pos;
            written_chars = mf_func(&temp_ptr, num, 0);
            current_pos = temp_ptr;
            counter += written_chars;
            flg += 2;
        } 
        else {
            char format_str[3] = {'%', *flg, '\0'};
            int written = vsprintf(current_pos, format_str, args);
            current_pos += written;
            counter += written;
            flg++;
        }
    }
    
    *current_pos = '\0';
    va_end(args);
    return counter;
}


int main() {
    printf("=== Quick Test ===\n");
    
    FILE* file = fopen("test.txt", "w");
    if (file) {
        overfprintf(file, "Roman 14=%Ro Fib 7=%Zr Hex 255=%Cv", 14, 7, 255, 16);
        fclose(file);
    }
    
    char result[256];
    oversprintf(result, "Roman 14=%Ro Fib 7=%Zr Hex 255=%Cv", 14, 7, 255, 16);
    printf("Result: %s\n", result);
    
    oversprintf(result, "Signed -5=%mi Unsigned 5=%mu  %s", -5, 5, "xdfghjk");
    printf("Binary: %s\n", result);
    
    return 0;
}