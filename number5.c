#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef enum {
    OPT_D,
    OPT_I,
    OPT_S,
    OPT_A
} kOpts;

typedef void (*callback_t) (FILE*, FILE*);

char* add_pref(const char* name) {
    if (name == NULL) return NULL;
    size_t len = strlen(name) + strlen("out_") + 1;
    char* res = malloc(len);
    if (res != NULL) {
        snprintf(res, len, "out_%s", name);
    }
    return res;
}

int getopts(int argc, char **argv, kOpts *option, char **file_name, char** file_name_out) {
    char *str = argv[1];
    *file_name = argv[2];
    char flag;
    if (str[0] != '-') return 1;
    if (str[1] == 'n') {
        if (argc != 4) {
            return 1;
        }
        *file_name_out = argv[3];
        flag = str[2];
    } else {
        if (argc != 3) {
            return 1;
        }
        *file_name_out = add_pref(argv[2]);
        flag = str[1];
    }
    
    if (*file_name_out == NULL) return 1;

    switch (flag) {
        case 'd':
            *option = OPT_D;
            break;
        case 'i':
            *option = OPT_I;
            break;
        case 's':
            *option = OPT_S;
            break;
        case 'a':
            *option = OPT_A;
            break;
        default:
            return 1;
    }
    //printf("%s\n", *file_name);
    //printf("%s", *file_name_out);

    return 0;
}

void HandlerOptD(FILE* in_file, FILE* out_file) {

    int symbol;
    while ((symbol = fgetc(in_file)) != EOF) {
        if (!isdigit(symbol)) {
            fputc(symbol, out_file);
        }
    }

    printf("Success!!!\n");

    return;
}

void HandlerOptI(FILE* in_file, FILE* out_file) {

    int symbol;
    int counter = 0;
    while ((symbol = fgetc(in_file)) != EOF) {
        if (isalpha(symbol)) {
            counter++;
        }
        else if (symbol == '\n') {
            fprintf(out_file, "%d\n", counter);
            counter = 0;
        }
    }
    if (counter != 0) {
        fprintf(out_file, "%d\n", counter);
    }

    printf("Success!!!\n");

    return;
}

void HandlerOptS(FILE* in_file, FILE* out_file) {

    int symbol;
    int counter = 0;
    while ((symbol = fgetc(in_file)) != EOF) {
        if (symbol == '\n') {
            fprintf(out_file, "%d\n", counter);
            counter = 0;
        } else if (!isalpha(symbol) && !isdigit(symbol) && symbol != ' ' && !(symbol >= 192 && symbol <= 255)) {
            counter++;
            //printf("%c", symbol);
        }
    }
    
    if (counter != 0) {
        fprintf(out_file, "%d\n", counter);
    }

    printf("Success!!!\n");
}

void HandlerOptA(FILE* in_file, FILE* out_file) {

    int symbol;
    while((symbol = fgetc(in_file)) != EOF) {
        if (isdigit(symbol)) {
            fputc(symbol, out_file);
        } else {

            fprintf(out_file, "%02X", symbol);
        }
        fputc(' ', out_file);
    }
    printf("Success!!!\n");
}


int main(int argc, char **argv) {

    kOpts opt = OPT_D;
    char *input_file;
    char *output_file;

    if (getopts(argc, argv, &opt, &input_file, &output_file) == 1) {
        printf("Incorrect options!");
        return 1;
    }

    FILE* in_file = fopen(input_file, "r");

    if (in_file == NULL) {
        printf("Error opening files!!!\n");
        return 1;
    }
    
    FILE* out_file = fopen(output_file, "w");

    callback_t handlers[4] = {
        HandlerOptD,
        HandlerOptI,
        HandlerOptS,
        HandlerOptA  
    };

    if (out_file == NULL) {
        printf("Error opening files!!!\n");
        return 1;
    }

    handlers[opt](in_file, out_file);

    fclose(in_file);
    fclose(out_file);
    
}