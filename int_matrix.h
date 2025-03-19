#ifndef INT_MATRIX_H
#define INT_MATRIX_H

#include "matrix.h"

extern MatrixOperations int_matrix_ops;
Matrix* create_int_matrix(int rows, int cols);
Matrix* create_int_matrix_from_file(const char* filename);

#endif