#include "int_matrix.h"
#include "float_matrix.h"
#include "double_matrix.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#define EPSILON_FLOAT 1e-5
#define EPSILON_DOUBLE 1e-10

// Шаблонные функции проверки
int check_int_matrix(const Matrix* result, const int* expected) {
    int* data = (int*)result->data;
    for (int i = 0; i < result->rows * result->cols; i++) {
        if (data[i] != expected[i]) {
            printf("Mismatch at position %d: expected %d, got %d\n", i, expected[i], data[i]);
            return 0;
        }
    }
    return 1;
}

int check_float_matrix(const Matrix* result, const float* expected) {
    float* data = (float*)result->data;
    for (int i = 0; i < result->rows * result->cols; i++) {
        if (fabs(data[i] - expected[i]) > EPSILON_FLOAT) {
            printf("Mismatch at position %d: expected %.2f, got %.2f\n", i, expected[i], data[i]);
            return 0;
        }
    }
    return 1;
}

int check_double_matrix(const Matrix* result, const double* expected) {
    double* data = (double*)result->data;
    for (int i = 0; i < result->rows * result->cols; i++) {
        if (fabs(data[i] - expected[i]) > EPSILON_DOUBLE) {
            printf("Mismatch at position %d: expected %.2lf, got %.2lf\n", i, expected[i], data[i]);
            return 0;
        }
    }
    return 1;
}

void test_int_operations() {
    printf("\n=== Testing INT operations ===\n");
    int a_data[] = {1,2,3,4};
    int b_data[] = {5,6,7,8};
    
    Matrix* a = create_int_matrix(2, 2);
    Matrix* b = create_int_matrix(2, 2);
    memcpy(a->data, a_data, sizeof(a_data));
    memcpy(b->data, b_data, sizeof(b_data));
    
    // Тест сложения
    Matrix* add_result = create_int_matrix(2, 2);
    matrix_add(a, b, add_result);
    int expected_add[] = {6,8,10,12};
    if (check_int_matrix(add_result, expected_add)) {
        printf("INT Addition: OK\n");
    }
    
    // Тест умножения
    Matrix* mul_result = create_int_matrix(2, 2);
    matrix_multiply(a, b, mul_result);
    int expected_mul[] = {19,22,43,50};
    if (check_int_matrix(mul_result, expected_mul)) {
        printf("INT Multiplication: OK\n");
    }
    
    matrix_free(a);
    matrix_free(b);
    matrix_free(add_result);
    matrix_free(mul_result);
}

void test_float_operations() {
    printf("\n=== Testing FLOAT operations ===\n");
    
    // Инициализация данных
    float a_data[] = {1.1f, 2.2f, 3.3f, 4.4f};
    float scalar = 2.0f;
    
    Matrix* a = create_float_matrix(2, 2);
    memcpy(a->data, a_data, sizeof(a_data));
    
    // Тест умножения на скаляр
    Matrix* scale_result = create_float_matrix(2, 2);
    matrix_scale(a, &scalar, scale_result);
    float expected_scale[] = {2.2f, 4.4f, 6.6f, 8.8f};
    if (check_float_matrix(scale_result, expected_scale)) {
        printf("FLOAT Scaling: OK\n");
    }
    
    // Тест транспонирования
    Matrix* transposed = create_float_matrix(2, 2);
    matrix_transpose(a, transposed);
    float expected_transpose[] = {1.1f, 3.3f, 2.2f, 4.4f};
    if (check_float_matrix(transposed, expected_transpose)) {
        printf("FLOAT Transpose: OK\n");
    }
    
    matrix_free(a);
    matrix_free(scale_result);
    matrix_free(transposed);
}

void test_double_operations() {
    printf("\n=== Testing DOUBLE operations ===\n");
    
    // Инициализация данных
    double a_data[] = {1.5, 2.5, 3.5, 4.5};
    double b_data[] = {0.5, 1.5, 2.5, 3.5};
    
    Matrix* a = create_double_matrix(2, 2);
    Matrix* b = create_double_matrix(2, 2);
    memcpy(a->data, a_data, sizeof(a_data));
    memcpy(b->data, b_data, sizeof(b_data));
    
    // Тест сложения
    Matrix* add_result = create_double_matrix(2, 2);
    matrix_add(a, b, add_result);
    double expected_add[] = {2.0, 4.0, 6.0, 8.0};
    if (check_double_matrix(add_result, expected_add)) {
        printf("DOUBLE Addition: OK\n");
    }
    Matrix* transposed = create_double_matrix(2, 2);
    matrix_transpose(a, transposed);
    double expected_transpose[] = {1.5, 3.5, 2.5, 4.5};
    if (check_double_matrix(transposed, expected_transpose)) {
        printf("DOUBLE Transpose: OK\n");
    }
    matrix_free(a);
    matrix_free(b);
    matrix_free(add_result);
}

void test_file_operations() {
    printf("\n=== Testing FILE operations ===\n");
    
    // Тест для int
    Matrix* int_mat = create_int_matrix_from_file("data/INT_INPUT.txt");
    int expected_int[] = {1,2,3,4,5,6};
    if (check_int_matrix(int_mat, expected_int)) {
        printf("INT File Read: OK\n");
    }
    
    // Тест для float
    Matrix* float_mat = create_float_matrix_from_file("data/FLOAT_INPUT.txt");
    float expected_float[] = {1.5f,2.5f,3.5f,4.5f,5.5f,6.5f};
    if (check_float_matrix(float_mat, expected_float)) {
        printf("FLOAT File Read: OK\n");
    }
    
    matrix_free(int_mat);
    matrix_free(float_mat);
}

int main() {
    test_int_operations();
    test_float_operations();
    test_double_operations();
    test_file_operations();
    return 0;
}