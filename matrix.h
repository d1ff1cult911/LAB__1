#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

typedef struct MatrixOperations MatrixOperations;

typedef struct {
    void* data;
    int rows;
    int cols;
    size_t element_size;
    MatrixOperations* ops;
} Matrix;

struct MatrixOperations {
    void (*add)(const void* a, const void* b, void* result, int size);
    void (*multiply)(const void* a, const void* b, void* result, 
                    int rows_a, int cols_a, int cols_b);
    void (*scale)(const void* matrix, const void* scalar, 
                 void* result, int size);
    void (*transpose)(const void* matrix, void* result, 
                     int rows, int cols);
    void (*fill)(void* matrix, const void* value, int size);
};

Matrix* matrix_create(int rows, int cols, size_t element_size, MatrixOperations* ops);
void matrix_free(Matrix* mat);
void matrix_add(const Matrix* a, const Matrix* b, Matrix* result);
void matrix_multiply(const Matrix* a, const Matrix* b, Matrix* result);
void matrix_scale(const Matrix* mat, const void* scalar, Matrix* result);
void matrix_transpose(const Matrix* mat, Matrix* result);
void matrix_fill(Matrix* mat, const void* value);
Matrix* matrix_from_file(const char* filename, size_t element_size, MatrixOperations* ops);

#endif