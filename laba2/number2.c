#include <stdio.h>
#include <ctype.h>
//#include <stdlib.h>
#include <string.h>

#if defined(__linux__)
static const char *error_messages[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error"
};
#elif defined(__APPLE__)
static const char *error_messages[] = {
    "Undefined error: 0", 
    "Operation not permitted",
    "No such file or directory", 
    "No such process",
    "Interrupted system call",
    "Input/output error"
};
#else
static const char *error_messages[] = {
    "Success",
    "Operation not permitted", 
    "No such file or directory",
    "No such process",
    "Interrupted system call", 
    "Input/output error"
};
#endif

#define MAX_ERROR 5


void *memchr(const void *str, int c, size_t n) {

    char* res = NULL;

    const char* s = (const unsigned char*)str;
    unsigned char symbol = (unsigned char)c;

    for (size_t i = 0; i < n; i++) {


        if (s[i] == symbol) {
            res = (void*)(s + i);
            break;
        }
    }

    return res;
}

int memcmp(const void *str1, const void *str2, size_t n) {

    char* s_1 = (char*)str1;
    const char* s_2 = (const char*)str2;

    for (size_t i = 0; i < n; i++) {
        if (s_1[i] != s_2[i]) {
            return s_1[i] - s_2[i];
        }
    }
    return 0;
} 

void *memcpy(void *dest, const void *src, size_t n) {

    if (dest == NULL || src == NULL) {
        return NULL;
    }

    const char* str = (const char*)src;
    char* str_copy = (char*)dest;

    for (size_t i = 0; i < n; i++) {
        str_copy[i] = str[i];
    }

    return dest;
}

void *memset(void *str, int c, size_t n) {

    if (str == NULL) {
        return NULL;
    }

    char* s = (char*)str;
    unsigned char symbol = (unsigned char)c;

    for (size_t i = 0; i < n; i++) {
        s[i] = symbol;
    }

    return str;
}

char *strncat(char *dest, const char *src, size_t n) {

    if (dest == NULL || src == NULL) {
        return dest;
    }

    char* dest_c = (char*)dest;
    const char* s = (const char*)src;
    size_t length = strlen(dest);

    for(size_t i = 0; i < n; i++) {
        dest_c[i + length] = s[i];
    }

    dest[n + length] = '\0';

    return dest;
}

char *strchr(const char *str, int c) {

    if (str == NULL) {
        return NULL;
    }

    char* res = NULL;
    size_t length = strlen(str);
    unsigned char symbol = (unsigned char)c;

    for (size_t i = 0; i < length; i++) {
        if(str[i] == symbol){
            res = (char*)(str + i);
            break;
        }

        if (str[i] == '\0') {
            break;
        }
    }

    return res;
}

int strncmp(const char *str1, const char *str2, size_t n) {

    for (size_t i = 0; i < n; i++) {
        if(str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        if (str1[i] == '\0' || str2[i] == '\0') {
            return 0;
        }
    }

    return 0;
}

size_t strcspn(const char *str1, const char *str2) {

    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    size_t counter = 0;
    while (str1[counter] != '\0') {
        size_t i = 0;
        while(str2[i] != '\0') {
            if (str1[counter] == str2[i]) {
                return counter;
            }
            i++;
        }
        counter++;
    }
    return counter;
}

char *strerror(int errnum) {
    if (errnum < 0 || errnum > MAX_ERROR) {
        return "Unknown error";
    }
    return (char *)error_messages[errnum];
}

size_t strlen(const char *str) {

    size_t i = 0;

    while(str[i] != '\0') {
        i++;
    }

    return i;
}

char *strpbrk(const char *str1, const char *str2) {

    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }
    size_t i = 0;
    char* res = NULL;

    while(str1[i] != '\0') {
        size_t j = 0;
        while(str2[j] != '\0') {
            if (str1[i] == str2[j]) {
                return (char*)(str1 + i);
            }
            j++;
        }
        i++;
    }
    return res;
}

char *strrchr(const char *str, int c) {


    if (str == NULL) {
        return NULL;
    }

    unsigned char symbol = (unsigned char)c;
    size_t i = 0;
    char* res = NULL;

    while(str[i] != '\0') {
        if (str[i] == symbol) {
            res = (char*)(str + i);
        }
        i++;
    }
    return res;
}



char *strstr(const char *haystack, const char *needle) {
    if (haystack == NULL || needle == NULL) {
        return NULL;
    }
    
    if (needle[0] == '\0') {
        return (char*)haystack;
    }
    
    for (size_t i = 0; haystack[i] != '\0'; i++) {
        size_t j = 0;
        
        while (needle[j] != '\0' && haystack[i + j] != '\0') {
            if (haystack[i + j] != needle[j]) {
                break;
            }
            j++;
        }
        
        if (needle[j] == '\0') {
            return (char*)(haystack + i);
        }
        
        if (haystack[i + j] == '\0') {
            break;
        }
    }
    
    return NULL;
}

char *strtok(char *str, const char *delim) {

    static char *strtok_save = NULL;

    if (str != NULL) {
        strtok_save = str;
    }
    
    if (strtok_save == NULL || *strtok_save == '\0') {
        return NULL;
    }
    
    while (*strtok_save != '\0' && strchr(delim, *strtok_save) != NULL) {
        strtok_save++;
    }
    
    if (*strtok_save == '\0') {
        strtok_save = NULL;
        return NULL;
    }
    
    char *token_start = strtok_save;
    
    while (*strtok_save != '\0' && strchr(delim, *strtok_save) == NULL) {
        strtok_save++;
    }
    
    if (*strtok_save != '\0') {
        *strtok_save = '\0';
        strtok_save++;
    } else {
        strtok_save = NULL;
    }
    
    return token_start;
}

int main() {
    
    // Test memchr
    char str1[] = "Hello World";
    printf("1. memchr: %s\n", (char*)memchr(str1, 'W', 11));
    
    // Test memcmp
    char str2[] = "Hello";
    char str3[] = "Hello";
    printf("2. memcmp: %d\n", memcmp(str2, str3, 5));
    
    // Test memcpy
    char buffer1[20];
    memcpy(buffer1, "Test", 5);
    printf("3. memcpy: %s\n", buffer1);
    
    // Test memset
    char buffer2[10];
    memset(buffer2, 'A', 5);
    buffer2[5] = '\0';
    printf("4. memset: %s\n", buffer2);
    
    // Test strncat
    char dest1[20] = "Hello";
    strncat(dest1, " World", 7);
    printf("5. strncat: %s\n", dest1);
    
    // Test strchr
    printf("6. strchr: %s\n", strchr("Hello", 'e'));
    
    // Test strncmp
    printf("7. strncmp: %d\n", strncmp("Hello", "Help", 3));
    
    // Test strcspn
    printf("8. strcspn: %zu\n", strcspn("Hello", "lo"));
    
    // Test strerror
    printf("9. strerror: %s\n", strerror(2));
    
    // Test strlen
    printf("10. strlen: %zu\n", strlen("Hello"));
    
    // Test strpbrk
    printf("11. strpbrk: %s\n", strpbrk("Hello", "le"));
    
    // Test strrchr
    printf("12. strrchr: %s\n", strrchr("Hello", 'l'));
    
    // Test strstr
    printf("13. strstr: %s\n", strstr("Hello World", "World"));
    
    // Test strtok
    char str4[] = "one,two,three";
    printf("14. strtok: ");
    char *token = strtok(str4, ",");
    while (token) {
        printf("%s ", token);
        token = strtok(NULL, ",");
    }
    printf("\n");
    
    return 0;
}
