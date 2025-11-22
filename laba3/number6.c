#include <stdio.h>
//#include <stdbool.h>

int check_brackets(const char *str) {
    const char* str_copy = str;

    struct Bracket {
        char* symbol;
        int open_count;
        int close_count;
    };

    struct Bracket counter[] = {
        {"()", 0, 0}, {"[]", 0, 0}, {"{}", 0, 0}, {"<>", 0, 0}
    };

    while (*str_copy != '\0') {

        for (int i = 0; i < 4; i++) {
            if (*str_copy == counter[i].symbol[0]) {
                //printf("found");
                counter[i].open_count++;
            } else if (*str_copy == counter[i].symbol[1]) {
                counter[i].close_count++;
                //printf("found");
            }
        }
        str_copy++;
    }

    int flag = 1;

    for (int i = 0; i < 4; i++) {
        if (counter[i].open_count > counter[i].close_count) {
            printf("Not found %c\n", counter[i].symbol[1]);
            flag = 0;
        } else if (counter[i].open_count < counter[i].close_count) {
            printf("Not found %c\n", counter[i].symbol[0]);
            flag = 0;
        }
    }

    if (flag == 0) {
        return -1;
    }
    printf("All right");

    return 1;
}


int main() {

    char* str = "hfnei<<()()>>ouvne";

    check_brackets(str);

    return 0;
}