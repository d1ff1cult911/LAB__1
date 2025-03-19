#include "int_matrix.h"
#include <stdio.h>
#include <stdlib.h>

static void int_add(const void* a, const void* b, void* result, int size) {
    const int* a_data = a;
    const int* b_data = b;
    int* res = result;
    for (int i = 0; i < size; i++) res[i] = a_data[i] + b_data[i];
}

static void int_multiply(const void* a, const void* b, void* result, 
                        int rows_a, int cols_a, int cols_b) {
    const int* a_data = a;
    const int* b_data = b;
    int* res = result;
    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_b; j++) {
            int sum = 0;
            for (int k = 0; k < cols_a; k++)
                sum += a_data[i * cols_a + k] * b_data[k * cols_b + j];
            res[i * cols_b + j] = sum;
        }
    }
}

static void int_scale(const void* matrix, const void* scalar, void* result, int size) {
    const int* mat = matrix;
    int scale = *(const int*)scalar;
    int* res = result;
    for (int i = 0; i < size; i++) res[i] = mat[i] * scale;
}

static void int_transpose(const void* matrix, void* result, int rows, int cols) {
    const int* mat = matrix;
    int* res = result;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[j * rows + i] = mat[i * cols + j];
}

static void int_fill(void* matrix, const void* value, int size) {
    int* mat = matrix;
    int val = *(const int*)value;
    for (int i = 0; i < size; i++) mat[i] = val;
}

MatrixOperations int_matrix_ops = {
    .add = int_add,
    .multiply = int_multiply,
    .scale = int_scale,
    .transpose = int_transpose,
    .fill = int_fill
};

Matrix* create_int_matrix(int rows, int cols) {
    return matrix_create(rows, cols, sizeof(int), &int_matrix_ops);
}

Matrix* create_int_matrix_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);
    Matrix* mat = create_int_matrix(rows, cols);
    for (int i = 0; i < rows * cols; i++) 
        fscanf(file, "%d", (int*)mat->data + i);
    fclose(file);
    return mat;
}