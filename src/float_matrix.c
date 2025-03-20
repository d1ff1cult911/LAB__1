#include "float_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void float_add(const void* a, const void* b, void* result, int size) {
    const float* a_data = (const float*)a;
    const float* b_data = (const float*)b;
    float* res = (float*)result;
    for (int i = 0; i < size; i++) {
        res[i] = a_data[i] + b_data[i];
    }
}
static void float_add_linear_combination(void* matrix, int base_row, const void* coefficient,int rows, int cols) {
    float* data = (float*)matrix;
    float coeff = *(const float*)coefficient;
    for (int i = 0; i < rows; i++) {
        if (i == base_row) continue;
        for (int j = 0; j < cols; j++) {
            data[i * cols + j] += coeff * data[base_row * cols + j];
        }
    }
}

static void float_multiply(const void* a, const void* b, void* result, int rows_a, int cols_a, int cols_b) {
    const float* a_data = (const float*)a;
    const float* b_data = (const float*)b;
    float* res = (float*)result;
    memset(res, 0, rows_a * cols_b * sizeof(float));
    for (int i = 0; i < rows_a; i++) {
        for (int k = 0; k < cols_a; k++) {
            float a_val = a_data[i * cols_a + k];
            for (int j = 0; j < cols_b; j++) {
                res[i * cols_b + j] += a_val * b_data[k * cols_b + j];
            }
        }
    }
}

static void float_scale(const void* matrix, const void* scalar, void* result, int size) {
    const float* mat = matrix;
    float scale = *(const float*)scalar;
    float* res = result;
    for (int i = 0; i < size; i++) res[i] = mat[i] * scale;
}

static void float_transpose(const void* matrix, void* result, int rows, int cols) {
    const float* mat = matrix;
    float* res = result;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) res[j * rows + i] = mat[i * cols + j];
}

static void float_fill(void* matrix, const void* value, int size) {
    float* mat = matrix;
    float val = *(const float*)value;
    for (int i = 0; i < size; i++) mat[i] = val;
}

MatrixOperations float_matrix_ops = {
    .add = float_add,
    .multiply = float_multiply,
    .scale = float_scale,
    .transpose = float_transpose,
    .fill = float_fill,
    .add_linear_combination = float_add_linear_combination,
};

Matrix* create_float_matrix(int rows, int cols) {
    return matrix_create(rows, cols, sizeof(float), &float_matrix_ops);
}
Matrix* create_float_matrix_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open float matrix file");
        return NULL;
    }
    int rows, cols;
    if (fscanf(file, "%d %d", &rows, &cols) != 2) {
        fclose(file);
        fprintf(stderr, "Error reading matrix dimensions\n");
        return NULL;
    }
    Matrix* mat = create_float_matrix(rows, cols);
    float* data = (float*)mat->data;
    for (int i = 0; i < rows * cols; i++) {
        if (fscanf(file, "%f", &data[i]) != 1) {
            fprintf(stderr, "Error reading float element at position %d\n", i);
            matrix_free(mat);
            fclose(file);
            return NULL;
        }
    }
    fclose(file);   
    return mat;
}