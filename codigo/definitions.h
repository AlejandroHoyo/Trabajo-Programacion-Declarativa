#ifndef definitions_H
#define definitions_H

#include <SWI-Prolog.h>

/*
Matrix struct to represent a matrix in C and carry out the operations
*/
typedef struct {
    int rows ; // represents the number of rows of the matrix
    int columns; // represents the number of columns the matrix
    double* data; // represents the data that a matrix contains. It is stored as an undimensional array (single pointer)
 } Matrix;


# define SUCCESS 1
# define FAILURE 0

/*
Macro to access or assing an specific element in a bidemensional matrix
which has been stored as a unidimensional matrix.
*/
# define ACCESS(matrix, row, column) matrix -> data[column * matrix -> rows + row]

 /* 
    Function declarations for the matricesLogic class to avoid the warning
 */

// Creation and managment of the matrices
Matrix* new_matrix(int rows, int columns);
int free_matrix(Matrix* matrix);

// Management of matrices
int matrices_addition(Matrix *matrix1, Matrix *matrix2, Matrix *result);
int matrices_substraction(Matrix *matrix1, Matrix *matrix2, Matrix *result);
int matrices_multiplication(Matrix* matrix1, Matrix* matrix2, Matrix* result);
int matrix_transpose(Matrix* matrix, Matrix* result);
int calculate_dot_product(Matrix* vector1, Matrix* vector2, double* result);
int obtain_maximum_value_from_matrix(Matrix* matrix, double* maximum_value);
int is_matrix_diagonal(Matrix* matrix);
int multiply_matrix_by_factor(Matrix* matrix, double* factor, Matrix* result); 
int divide_matrix_by_factor(Matrix* matrix, double *factor, Matrix* result);
int sum_elements_from_matrix(Matrix* matrix, double* result); 
int is_upper_triangular_matrix(Matrix* matrix);
int do_matrices_have_same_dimensions(Matrix* matrix1, Matrix* matrix2); 

// Auxiliary methods for conversion
Matrix* parse_list_of_lists_into_matrix(term_t tList);
int parse_matrix_into_list_of_lists(Matrix* matrix, term_t resutltListOfLists);
int assign_matrix_row_values_to_list(Matrix* matrix, term_t tList, int current_row); 
int get_correct_dimensions(term_t tList, int* rows, int* columns);

# endif 