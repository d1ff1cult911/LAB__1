#include "double_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void double_add(const void* a, const void* b, void* result, int size) {
    const double* a_data = a;
    const double* b_data = b;
    double* res = result;
    for (int i = 0; i < size; i++) res[i] = a_data[i] + b_data[i];
}

static void double_multiply(const void* a, const void* b, void* result, int rows_a, int cols_a, int cols_b) {
    const double* a_data = a;
    const double* b_data = b;
    double* res = result;
// Явно инициализируем результат нулями
    memset(res, 0, rows_a * cols_b * sizeof(double));
    for (int i = 0; i < rows_a; i++) {
        for (int k = 0; k < cols_a; k++) { // Оптимизированный порядок циклов
        double a_val = a_data[i * cols_a + k];
            for (int j = 0; j < cols_b; j++) {
                res[i * cols_b + j] += a_val * b_data[k * cols_b + j];
            }
        }
    }
}

static void double_scale(const void* matrix, const void* scalar, void* result, int size) {
    const double* mat = matrix;
    double scale = *(const double*)scalar;
    double* res = result;
    for (int i = 0; i < size; i++) res[i] = mat[i] * scale;
}

static void double_transpose(const void* matrix, void* result, int rows, int cols) {
    const double* mat = matrix;
    double* res = result;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[j * rows + i] = mat[i * cols + j];
}

static void double_fill(void* matrix, const void* value, int size) {
    double* mat = matrix;
    double val = *(const double*)value;
    for (int i = 0; i < size; i++) mat[i] = val;
}

MatrixOperations double_matrix_ops = {
    .add = double_add,
    .multiply = double_multiply,
    .scale = double_scale,
    .transpose = double_transpose,
    .fill = double_fill
};

Matrix* create_double_matrix(int rows, int cols) {
    return matrix_create(rows, cols, sizeof(double), &double_matrix_ops);
}

Matrix* create_double_matrix_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);
    Matrix* mat = create_double_matrix(rows, cols);
    for (int i = 0; i < rows * cols; i++)
        fscanf(file, "%lf", (double*)mat->data + i);
    fclose(file);
    return mat;
}