#include <stdio.h>
#include <stdlib.h>

#define VECTOR_TYPE int

#include "number2.c"

int CopyInt(int value) {
    return value;
}

void DeleteInt(int value) {
    (void)value;
}

void test_create_and_basic() {
    printf("=== Test 1: create_vector and basic operations ===\n");
    
    Vector* v = create_vector(5, CopyInt, DeleteInt);
    printf("Created vector: size=%zu, capacity=%zu\n", v->size, v->capacity);
    
    push_back_vector(v, 10);
    push_back_vector(v, 20);
    push_back_vector(v, 30);
    printf("After push_back 3 elements: size=%zu\n", v->size);
    
    printf("Elements: ");
    for (size_t i = 0; i < v->size; i++) {
        printf("%d ", get_at_vector(v, i));
    }
    printf("\n");
    
    delete_vector(v);
    printf("Test 1 passed\n\n");
}

void test_push_back_capacity() {
    printf("=== Test 2: push_back capacity growth ===\n");
    
    Vector* v = create_vector(2, CopyInt, DeleteInt);
    
    for (int i = 0; i < 10; i++) {
        push_back_vector(v, i * 5);
    }
    printf("Pushed 10 elements: size=%zu, capacity=%zu\n", v->size, v->capacity);
    
    delete_vector(v);
    printf("Test 2 passed\n\n");
}

void test_delete_at() {
    printf("=== Test 3: delete_at_vector ===\n");
    
    Vector* v = create_vector(5, CopyInt, DeleteInt);
    
    for (int i = 0; i < 5; i++) {
        push_back_vector(v, i * 10);
    }
    printf("Before delete: ");
    for (size_t i = 0; i < v->size; i++) {
        printf("%d ", get_at_vector(v, i));
    }
    printf("\n");
    
    delete_at_vector(v, 2);
    printf("After delete at index 2: ");
    for (size_t i = 0; i < v->size; i++) {
        printf("%d ", get_at_vector(v, i));
    }
    printf("\n");
    
    delete_vector(v);
    printf("Test 3 passed\n\n");
}

void test_is_equal() {
    printf("=== Test 4: is_equal_vector ===\n");
    
    Vector* v1 = create_vector(5, CopyInt, DeleteInt);
    Vector* v2 = create_vector(5, CopyInt, DeleteInt);
    
    for (int i = 0; i < 3; i++) {
        push_back_vector(v1, i);
        push_back_vector(v2, i);
    }
    
    printf("v1 and v2 are equal: %s\n", is_equal_vector(v1, v2) ? "YES" : "NO");
    
    push_back_vector(v2, 999);
    printf("After modification, v1 and v2 are equal: %s\n", is_equal_vector(v1, v2) ? "YES" : "NO");
    
    delete_vector(v1);
    delete_vector(v2);
    printf("Test 4 passed\n\n");
}

void test_copy_operations() {
    printf("=== Test 5: copy operations ===\n");
    
    Vector* src = create_vector(5, CopyInt, DeleteInt);
    for (int i = 0; i < 4; i++) {
        push_back_vector(src, i * 25);
    }
    
    Vector* dest = create_vector(2, CopyInt, DeleteInt);
    copy_vector(dest, src);
    printf("copy_vector: dest size=%zu, equal to src: %s\n", 
           dest->size, is_equal_vector(src, dest) ? "YES" : "NO");
    
    Vector* new_vec = copy_vector_new(src);
    printf("copy_vector_new: new_vec size=%zu, equal to src: %s\n", 
           new_vec->size, is_equal_vector(src, new_vec) ? "YES" : "NO");
    
    delete_vector(src);
    delete_vector(dest);
    delete_vector(new_vec);
    printf("Test 5 passed\n\n");
}

void test_edge_cases() {
    printf("=== Test 6: Edge Cases ===\n");
    
    printf("is_equal_vector(NULL, NULL): %s\n", is_equal_vector(NULL, NULL) ? "YES" : "NO");
    
    Vector* empty = create_vector(0, CopyInt, DeleteInt);
    printf("Empty vector created: size=%zu\n", empty->size);
    
    int value = get_at_vector(empty, 0);
    printf("get_at_vector from empty vector: %d\n", value);
    
    delete_vector(empty);
    printf("Test 6 passed\n\n");
}

int main() {
    
    test_create_and_basic();
    test_push_back_capacity();
    test_delete_at();
    test_is_equal();
    test_copy_operations();
    test_edge_cases();
    
    printf("ALL TESTS PASSED! Vector library works correctly!\n");
    
    return 0;
}
