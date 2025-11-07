#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MARK_COUNT 5

typedef struct {
    unsigned int id;
    char name[100];
    char surname[100];
    char group[100];
    unsigned char* marks;
} Student;

int check_str(const char* str) {
    if (str == NULL || strlen(str) == 0) {
        return 0;
    }
    for (size_t i = 0; i < strlen(str); i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||(str[i] >= 'A' && str[i] <= 'Z'))) {
            return 0;
        }
    }
    return 1;
}

Student* read_student(char* name_input, int* student_count, float* sr_marks) {

    FILE* file_input = fopen(name_input, "r");

    if (file_input == NULL) {
        printf("Error opening the input file");
        return NULL;
    }

    int capacity = 10;
    int count = 0;
    Student* massiv_students = malloc(capacity * sizeof(Student));

    if (massiv_students == NULL) {
        fclose(file_input);
        return NULL;
    }

    char buffer[1000];
    *sr_marks = 0;
    while(fgets(buffer, sizeof(buffer), file_input)) {

        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) continue;

        unsigned int id;
        char name[100];
        char surname[100];
        char group[100];
        unsigned char marks[MARK_COUNT];

        if (sscanf(buffer, "%u;%99[^;];%99[^;];%99[^;];%hhu,%hhu,%hhu,%hhu,%hhu",
                                  &id, name, surname, group, 
                                  &marks[0], &marks[1], &marks[2], &marks[3], &marks[4]) != 9) {
            printf("Uncorrect data");
            continue;
        }

        if (id <= 0) {
            printf("Uncorrect id");
            continue;
        }
        
        if (!check_str(name)) {
            printf("Uncorrect name");
            continue;
        }

        if (!check_str(surname)) {
            printf("Uncorrect surname");
            continue;
        }

        if (strlen(group) == 0) {
            printf("Uncorrect group");
            continue;
        }

        int flag = 0;
        for (int i = 0; i < 5; i++) {
            if (marks[i] < 1 || marks[i] > 5) {
                printf("Uncorrect marks");
                flag = 1;
                break;
            }
        }

        if (flag == 1) continue;

        if (count >= capacity) {
            capacity *= 2;
            Student* temp = realloc(massiv_students, capacity * sizeof(Student));

            if (temp == NULL) {
                break;
            }
            massiv_students = temp;
        }

        massiv_students[count].marks = malloc(MARK_COUNT * sizeof(unsigned char));

        massiv_students[count].id = id;
        strcpy(massiv_students[count].name, name);
        strcpy(massiv_students[count].surname, surname);
        strcpy(massiv_students[count].group, group);
        int sum_marks = 0;
        for (int i = 0; i < MARK_COUNT; i++) {
            sum_marks += marks[i];
            massiv_students[count].marks[i] = marks[i];
        }

        *sr_marks += sum_marks / 5.0;
        
        count++;
    }
        
    fclose(file_input);
    *student_count = count;

    if (count == 0) {
        free(massiv_students);
        return NULL;
    }

    *sr_marks /= count;

    return massiv_students;
}

Student* search_in_id(Student* massiv, unsigned int id, int counter) {

    for (int i = 0; i < counter; i++) {
        if (massiv[i].id == id) {
            return &massiv[i];
        }
    }
    return NULL;
}

int compare_by_id(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;
    const Student* studentB = (const Student*)b;
    
    if (studentA->id < studentB->id) return -1;
    if (studentA->id > studentB->id) return 1;
    return 0;
}

int compare_by_surname(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;
    const Student* studentB = (const Student*)b;
    return strcmp(studentA->surname, studentB->surname);
}

int compare_by_name(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;
    const Student* studentB = (const Student*)b;
    return strcmp(studentA->name, studentB->name);
}

int compare_by_group(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;
    const Student* studentB = (const Student*)b;
    return strcmp(studentA->group, studentB->group);
}

void sort_students(Student* students, int count, int sort_type) {
    switch (sort_type) {
        case 1:
            qsort(students, count, sizeof(Student), compare_by_id);
            break;
            
        case 2:
            qsort(students, count, sizeof(Student), compare_by_name);
            break;
            
        case 3:
            qsort(students, count, sizeof(Student), compare_by_surname);
            break;
            
        case 4:
            qsort(students, count, sizeof(Student), compare_by_group);
            break;
            
        default:
            printf("Uncorrect type of sort\n");
            return;
    }
}

void students_to_file(Student* students, int count, const char* filename) {
    if (students == NULL || count <= 0 || filename == NULL) return;

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%u;%s;%s;%s;%hhu,%hhu,%hhu,%hhu,%hhu\n",
                students[i].id,
                students[i].name,
                students[i].surname, 
                students[i].group,
                students[i].marks[0],
                students[i].marks[1],
                students[i].marks[2],
                students[i].marks[3],
                students[i].marks[4]);
    }

    fclose(file);
}

void print_student(const Student* student) {
    if (student == NULL) {
        printf("Student not found\n");
        return;
    }
    
    printf("ID: %u\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Surname: %s\n", student->surname);
    printf("Group: %s\n", student->group);
    printf("Marks: ");
    
    for (int i = 0; i < MARK_COUNT; i++) {
        printf("%hhu", student->marks[i]);
        if (i < MARK_COUNT - 1) printf(", ");
    }
    
    printf("\n===========================\n");
}

void student_to_trace(const Student* student, const char* file_name) {
    if (student == NULL || file_name == NULL) return;

    FILE* trace_file = fopen(file_name, "a");
    if (trace_file == NULL) {
        printf("Error with opening trace file");
        return;
    }
    
    fprintf(trace_file, "%s %s\n", student->name, student->surname);
    fclose(trace_file);
}

void str_to_trace(const char* phrase, const char* filename) {
    if (phrase == NULL || filename == NULL) return;
    
    FILE* trace_file = fopen(filename, "a");
    if (trace_file == NULL) {
        printf("Error with opening trace file\n");
        return;
    }
    
    fprintf(trace_file, "%s\n", phrase);
    fclose(trace_file);
}

void sr_marks(Student* students, int count, float sr_all_marks, const char* file_name) {
    if (students == NULL || count <= 0 || file_name == NULL) return;
    
    str_to_trace("=== СТУДЕНТЫ С БАЛЛОМ ВЫШЕ СРЕДНЕГО ===\n", file_name);
    
    int found_count = 0;
    for (int i = 0; i < count; i++) {
        int mark_sum = 0;
        for (int j = 0; j < 5; j++) {
            mark_sum += students[i].marks[j];
        }
        float sr_mark = (float)mark_sum / 5;
        
        if (sr_mark > sr_all_marks) {
            student_to_trace(&students[i], file_name);
            found_count++;
        }
    }
    
    if (found_count == 0) {
        str_to_trace("Студенты не найдены\n", file_name);
    }
    str_to_trace("==========================================\n6", file_name);

}

void print_menu() {
    printf("1. Search by ID\n");
    printf("2. Search by name\n");
    printf("3. Search by surname\n");
    printf("4. Search by group\n");
    printf("5. Sort by ID\n");
    printf("6. Sort by name\n");
    printf("7. Sort by surname\n");
    printf("8. Sort by group\n");
    printf("9. Output student by ID to trace file\n");
    printf("10. Output students with above average marks to trace file\n");
    printf("0. Exit\n");
    printf("Choose action: ");
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Enter input file and output file");
        return 1;
    }

    char* name_input = argv[1];
    char* name_output = argv[2];
    int counter = 0;
    float all_sr_marks = 0;

    Student* massiv_student = read_student(name_input, &counter, &all_sr_marks);

    if (massiv_student == NULL || counter == 0) {
        printf("Read error\n");
        return 1;
    }
    
    int choice;

    do {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Error command\n");
            while (getchar() != '\n');
            continue;
        }

        printf("\n\n");

        switch (choice) {
            case 1: {
                unsigned int id;
                printf("Enter ID: ");
                if (scanf("%u", &id) == 1) {
                    Student* results = search_in_id(massiv_student, id, counter);
                    print_student(results);
                } else {
                    printf("Uncorrect ID\n");
                }
                break;
            }
            
            case 2: {
                char name[100];
                printf("Enter name: ");
                if (scanf("%99s", name) == 1) {
                    int found = 0;
                    for (int i = 0; i < counter; i++) {
                        if (strcmp(name, massiv_student[i].name) == 0) {
                            print_student(&massiv_student[i]);
                            found = 1;
                        }
                    }
                    if (!found) {
                        printf("Student with name '%s' not found\n", name);
                    }
                } else {
                    printf("Uncorrect name\n");
                }
                break;
            }
            
            case 3: {
                char surname[100];
                printf("Enter surname: ");
                if (scanf("%99s", surname) == 1) {
                    int found = 0;
                    for (int i = 0; i < counter; i++) {
                        if (strcmp(surname, massiv_student[i].surname) == 0) {
                            print_student(&massiv_student[i]);
                            found = 1;
                        }
                    }
                    if (!found) {
                        printf("Student with surname '%s' not found\n", surname);
                    }
                } else {
                    printf("Uncorrect surname\n");
                }
                break;
            }
            
            case 4: {
                char group[100];
                printf("Enter group: ");
                if (scanf("%99s", group) == 1) {
                    int found = 0;
                    for (int i = 0; i < counter; i++) {
                        if (strcmp(group, massiv_student[i].group) == 0) {
                            print_student(&massiv_student[i]);
                            found = 1;
                        }
                    }
                    if (!found) {
                        printf("Student in group '%s' not found\n", group);
                    }
                } else {
                    printf("Uncorrect group\n");
                }
                break;
            }
            
            case 5:
            case 6:  
            case 7:
            case 8: {
                sort_students(massiv_student, counter, choice - 4);
                students_to_file(massiv_student, counter, name_input);
                break;
            }
            
            case 9: {
                unsigned int id;
                printf("Enter student ID: ");
                if (scanf("%u", &id) == 1) {
                    Student* result = search_in_id(massiv_student, id, counter);
                    if (result != NULL) {
                        student_to_trace(result, name_output);
                        printf("Student data written to trace file\n");
                    } else {
                        printf("Student with ID %u not found\n", id);
                    }
                } else {
                    printf("Uncorrect ID\n");
                }
                break;
            }
            
            case 10: {
                sr_marks(massiv_student, counter, all_sr_marks, name_output);
                printf("Data written to trace file\n");
                break;
            }
            
            case 0:
                break;
                
            default:
                printf("Uncorrect choice\n");
                break;
        }
        
    } while (choice != 0);

    for (int i = 0; i < counter; i++) {
        free(massiv_student[i].marks);
    }
    free(massiv_student);

    return 0;
}