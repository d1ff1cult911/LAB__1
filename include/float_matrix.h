// include/float_matrix.h
#ifndef FLOAT_MATRIX_H
#define FLOAT_MATRIX_H

#include "matrix.h"
extern MatrixOperations float_matrix_ops;
Matrix* create_float_matrix(int rows, int cols);
Matrix* create_float_matrix_from_file(const char* filename);

#endif