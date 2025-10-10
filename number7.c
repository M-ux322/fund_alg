#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int to_10(const char* number, int base) {
    int res = 0;
    for (int i = 0; number[i] != '\0'; i++) {
        char symbol = number[i];
        int digit;

        if(isdigit(symbol)) {
            digit = symbol - '0';
        } else if (isalpha(symbol)) {
            digit = toupper(symbol) - 'A' + 10;
        } else return -1;

        res = res * base + digit;
    }
    return res;

}

void func(FILE* input, FILE* output) {

    int capacity = 36;
    char* buffer = malloc(capacity);
    int symbol;
    int base = 0;
    int i = 0;
    while ((symbol = fgetc(input)) != EOF) {
        if (isdigit(symbol) || isalpha(symbol)) {

            if (i >= capacity - 1) {
                capacity *= 2;
                buffer = realloc(buffer, capacity);
            }

            buffer[i] = symbol;
            int numb;
            if (isdigit(symbol)) {
                numb = symbol - '0';
            } else numb = toupper(symbol) - 'A' + 10;

            if ((numb + 1) > base) {
                base = numb + 1;
            }

            if (i == 0 && (symbol - '0') == 0) {
                i--;
            } else fputc(symbol, output);
            i++;
            
        } else {
            //fputc(" ", output);
            if (i > 0) {
                buffer[i] = '\0';
                int num = to_10(buffer, base);
                fprintf(output, " %d, %d\n", base, num);
            }
            i = 0;
            base = 0;

        }

    }

    if (i > 0) {
        buffer[i] = '\0';
        int num = to_10(buffer, base);
        fprintf(output, " %d, %d\n", base, num);
    }

    free(buffer);

    return;
}

int main(int argc, char **argv) {

    if (argc != 3) {
        printf("Incorrect options!!!");
        return 1;
    }

    char *input_file = argv[1];
    char *output_file = argv[2];

    FILE* in_file = fopen(input_file, "r");

    if (in_file == NULL) {
        printf("Error opening file!!!");
        return 1;
    }

    FILE* out_file = fopen(output_file, "w");

    func(in_file, out_file);

    fclose(in_file);
    fclose(out_file);
    return 0;
}