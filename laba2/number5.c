#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void whitespace(int counter, int word_count, char* line, FILE* file_name) {
    if (word_count <= 1 || counter <= 0) {
        fputs(line, file_name);
        fputc('\n', file_name);
        return;
    }

    int white_count = counter / (word_count - 1);
    int ost_white = counter % (word_count - 1);

    char* buffer = line;
    int words = 0;

    while (*buffer != '\0') {

        if (*buffer != ' ') {
            fputc(*buffer, file_name);
        } else {
            fputc(' ', file_name);
            words++;

            for(int i = 0; i < white_count; i++) {
                fputc(' ', file_name);
            }
            if (ost_white != 0) {
                fputc(' ', file_name);
                ost_white--;
            }
            while (*(buffer + 1) == ' ') {
                buffer++;
            }
        }
        buffer++;
    }
    fputc('\n', file_name);
    return;

}

void line_func(char* orig_line, FILE* file_name) {

    int counter = 0;
    int word_count = 0;
    int len = 0;
    char buffer[1000] = {0};
    char word[100] = {0};

    char* line = orig_line;

    while(*line != '\0') {
        if (*line != ' ') {
            word[counter++] = *line;
        } else {
            if (counter > 0) {
                word[counter] = '\0'; 
                word_count++;
                //buffer[counter] = ',';

                if (len + counter + (len > 0 ? 1 : 0) <= 80) {
                    if (len > 0){
                        strcat(buffer, " ");
                        len++;
                    }
                    strcat(buffer, word);
                    len += counter;
                } else {
                    int white_count = 80 - len;
                    whitespace(white_count, word_count, buffer, file_name);

                    strcpy(buffer, word);

                    //fputs(buffer, file_name);
                    len = counter;
                    word_count = 1;
                }
                counter = 0;
            }
        }
        line++;
    }

    if (counter > 0) {
        word[counter] = '\0';
        if (len + counter + (len > 0 ? 1 : 0) <= 80) {
            if (len > 0){
                strcat(buffer, " ");
            }
            strcat(buffer, word);
            len += counter;
            word_count++;

            int space_count = 80 - len;
            whitespace(space_count, word_count, buffer, file_name);

            //fputs(buffer, file_name);
            //fputc('\n', file_name);
        } else {

            if (len > 0) {
                int space_count = 80 - len;
                whitespace(space_count, word_count, buffer, file_name);
            }

            //fputs(word, file_name);
            //fputc('\n', file_name);
        }
    } else if (len > 0) {
        int space_count = 80 - len;
        whitespace(space_count, word_count, buffer, file_name);
        //fputs(buffer, file_name);
        //fputc('\n', file_name);

    }
    return;
}

void process_file(char* input_name, char* output_name) {
    FILE* input_file = fopen(input_name, "r");

    if (input_file == NULL) {
        printf("Error opening the input file");
        return;
    }

    FILE* output_file = fopen(output_name, "w");

    if (output_file == NULL) {
        printf("Error opening the output file");
        return;
    }

    char str[1000];
    while(fgets(str, sizeof(str), input_file)) {
        str[strcspn(str, "\n")] = '\0';

        if (strlen(str) == sizeof(str) - 1 && str[strlen(str) - 1] != '\n') {
            printf("Error: very long line!");
        }
        line_func(str, output_file);
    }


    fclose(input_file);
    fclose(output_file);
    printf("Success");
    
}

int main() {
    process_file("input5.txt", "output5.txt");
    return 0;
}