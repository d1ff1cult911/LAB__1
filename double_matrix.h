#ifndef DOUBLE_MATRIX_H
#define DOUBLE_MATRIX_H

#include "matrix.h"

extern MatrixOperations double_matrix_ops;
Matrix* create_double_matrix(int rows, int cols);
Matrix* create_double_matrix_from_file(const char* filename);

#endif