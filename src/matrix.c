#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Matrix* matrix_create(int rows, int cols, size_t element_size, MatrixOperations* ops) {
    Matrix* mat = malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->element_size = element_size;
    mat->data = malloc(rows * cols * element_size);
    mat->ops = ops;
    return mat;
}

void matrix_free(Matrix* mat) {
    free(mat->data);
    free(mat);
}

void matrix_add(const Matrix* a, const Matrix* b, Matrix* result) {
    if (a->rows != b->rows || a->cols != b->cols || a->rows != result->rows || a->cols != result->cols) {
        fprintf(stderr, "Matrix addition dimension mismatch\n");
        exit(EXIT_FAILURE);
    }
    a->ops->add(a->data, b->data, result->data, a->rows * a->cols);
}

void matrix_multiply(const Matrix* a, const Matrix* b, Matrix* result) {
    if (a->cols != b->rows || result->rows != a->rows || result->cols != b->cols) {
        fprintf(stderr, "Matrix multiplication dimension mismatch\n");
        exit(EXIT_FAILURE);
    }
    a->ops->multiply(a->data, b->data, result->data, a->rows, a->cols, b->cols);
}

void matrix_scale(const Matrix* mat, const void* scalar, Matrix* result) {
    if (mat->rows != result->rows || mat->cols != result->cols) {
        fprintf(stderr, "Matrix scaling dimension mismatch\n");
        exit(EXIT_FAILURE);
    }
    mat->ops->scale(mat->data, scalar, result->data, mat->rows * mat->cols);
}

void matrix_transpose(const Matrix* mat, Matrix* result) {
    if (mat->rows != result->cols || mat->cols != result->rows) {
        fprintf(stderr, "Transpose dimension mismatch\n");
        exit(EXIT_FAILURE);
    }
    mat->ops->transpose(mat->data, result->data, mat->rows, mat->cols);
}

void matrix_fill(Matrix* mat, const void* value) {
    mat->ops->fill(mat->data, value, mat->rows * mat->cols);
}
void matrix_add_linear_combination(Matrix* mat, int base_row, const void* coefficient) {
    if (base_row < 0 || base_row >= mat->rows) {
        fprintf(stderr, "Invalid base row index: %d\n", base_row);
        return;
    }
    mat->ops->add_linear_combination(mat->data, base_row, coefficient, mat->rows, mat->cols);
}
Matrix* matrix_from_file(const char* filename, size_t element_size, MatrixOperations* ops) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }
    int rows, cols;
    if (fscanf(file, "%d %d", &rows, &cols) != 2) {
        fprintf(stderr, "Error reading dimensions from %s\n", filename);
        fclose(file);
        return NULL;
    }
    Matrix* mat = matrix_create(rows, cols, element_size, ops);
    if (!mat) {
        fclose(file);
        return NULL;
    }
    for (int i = 0; i < rows * cols; i++) {
        if (element_size == sizeof(int)) {
            if (fscanf(file, "%d", (int*)mat->data + i) != 1) {
                fprintf(stderr, "Error reading int data at element %d\n", i);
                matrix_free(mat);
                fclose(file);
                return NULL;
            }
        } else if (element_size == sizeof(float)) {
            if (fscanf(file, "%f", (float*)mat->data + i) != 1) {
                fprintf(stderr, "Error reading float data at element %d\n", i);
                matrix_free(mat);
                fclose(file);
                return NULL;
            }
        } else if (element_size == sizeof(double)) {
            if (fscanf(file, "%lf", (double*)mat->data + i) != 1) {
                fprintf(stderr, "Error reading double data at element %d\n", i);
                matrix_free(mat);
                fclose(file);
                return NULL;
            }
        }
    }
    fclose(file);
    return mat;
}