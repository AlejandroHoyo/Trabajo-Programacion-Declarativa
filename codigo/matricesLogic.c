#include "definitions.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <SWI-Prolog.h>

/*
    Create a new matrix with a given number of rows and columns. 
    Returns a valid matrix pointer on success and NULL on failure
*/
Matrix* new_matrix(int rows, int columns) {

    if (rows <= 0 || columns <= 0) {
        return NULL;
    }
    // Allocate a matrix structure
    Matrix* matrix = (Matrix *)malloc(sizeof(Matrix));
    if (matrix == NULL) {
       fprintf(stderr, "Error, No es posible crea la matriz");
        return NULL;
    }
    matrix->rows = rows;
    matrix->columns = columns;
    // Allocate double array of size rows*columns
    matrix->data = (double *)malloc(rows * columns * sizeof(double));

    if (matrix->data == NULL) {
        fprintf(stderr, "Error, no es posible crear la matriz");
        free_matrix(matrix); // Free the allocated Matrix structure
        return NULL;
    }
    return matrix;
}

/*
    Free the memory of a matrix
*/
int free_matrix(Matrix* matrix) {
  if (!matrix) {
    return FAILURE;
  }
  assert (matrix->data);
  free(matrix->data);
  free(matrix);
  return SUCCESS;
}

/*
    Add two matrices and returns Success if everything goes or 0 for failure.
*/
int matrices_addition(Matrix *matrix1, Matrix *matrix2, Matrix *result){

// Check if any of the matrices are NULL
    if (!matrix1 || !matrix2 || !result){
        return FAILURE;
    }

// Check all the matrices has the same dimensions
     if (do_matrices_have_same_dimensions(matrix1, matrix2) == FAILURE) {
        printf("Para realizar la suma, asegúrate que ambas matrices tienen el mismo número de filas que de columnas\n");
        return FAILURE;
        }

    for (int row = 0; row < result->rows; row++) {
        for (int column = 0; column < result->columns; column++) {
        
            ACCESS(result, row, column) = ACCESS(matrix1, row, column) + ACCESS(matrix2, row, column);
        }
    }
    return SUCCESS;
}   
/*
    Substract two matrices and return SUCCEED (1) everythin is correct or FAILURE (0) if something goes wrong
*/
int matrices_substraction(Matrix *matrix1, Matrix *matrix2, Matrix *result)
{
    if (!matrix1 || !matrix2 || !result) {
        return FAILURE;
    }
    // Check all the matrices has the same dimensions
    if (do_matrices_have_same_dimensions(matrix1, matrix2) == FAILURE){
        printf("Para realizar la resta, asegúrate que ambas matrices tienen el mismo número de filas que de columnas\n");
        return FAILURE;
        }

    for (int row = 0; row < result->rows; row++){
        for (int column = 0; column < result->columns; column++){
        
            ACCESS(result, row, column) = ACCESS(matrix1, row, column)- ACCESS(matrix2, row, column);
        }
    }
    return SUCCESS; 
}

/*
    Multiply two matrices with valid dimensions. Returns 
*/
int matrices_multiplication(Matrix* matrix1, Matrix* matrix2, Matrix* result) {

    // Check that pointers are not null
    if (!matrix1 || !matrix2 || !result) {
        return FAILURE;
    }
    // Check the dimensions are compatible
    if (matrix1->columns != matrix2->rows) {
        printf("Para realizar la multiplicación, asegúrate de que el número de columnas de "
       "la primera matriz: %d sea igual al número de filas de la segunda: %d\n", 
        matrix1->columns, matrix2->rows);
        return FAILURE;
    }
    for (int row = 0; row < result->rows; row++){
        for (int column = 0; column < result->columns; column++){
            double value = 0;
            for (int k = 0; k < matrix1->columns; k++) {
                value += ACCESS(matrix1, row, k) * ACCESS(matrix2, k, column);
            }
            ACCESS(result, row, column) = value;
        }
    }
    return SUCCESS;
}

/*
    Writes the transpose of a matrix. If possible, it returns SUCCESS, otherwise FAILURE
*/
int matrix_transpose(Matrix* matrix, Matrix* result) {

  // Check that pointers of matrices are not null
  if (!matrix || !result){
    return FAILURE;
  }
  if (matrix->rows != result->columns || matrix->columns != result->rows){
    return FAILURE;
  }
    for (int row = 0; row < matrix->rows; row++) {
        for (int column = 0; column < matrix->columns; column++) {
            ACCESS(result, column, row) = ACCESS(matrix, row, column);
        }
    }
  return SUCCESS;
}

/*
    Validate the dot product of two vectors. If possible, it returns SUCCESS, otherwise FAILURE.
    In this case, the number of rows of the matrix has to be 1 because we are dealing with vectors.

*/

int calculate_dot_product(Matrix* vector1, Matrix* vector2, double* result) {
    if (!vector1 || !vector2 || !result) {
        return FAILURE;
    }
    // Check that the dimension fo the vectors are valid
    if (vector1->columns != vector2->columns || vector1->rows != 1 || vector2->rows != 1) {
        printf("Debe de ser vectores que tengan el mismo número de elementos"); 
        return FAILURE;
    }
    *result = 0; 
    for (int current_column = 0; current_column < vector1->columns; current_column++) {
        *result += ACCESS(vector1, 0, current_column) * ACCESS(vector2, 0, current_column);
    }
    return SUCCESS;
}

/*
    Obtain the maximum value from a matrix. If possible, 
    it returns SUCCESS, otherwise FAILURE.

*/
int obtain_maximum_value_from_matrix(Matrix* matrix, double* maximum_value) {
    if (!matrix || !maximum_value) {
        return FAILURE;
    }
    for (int row = 0; row < matrix->rows; row++) {
        for (int column = 0; column < matrix->columns; column++) {
            if (ACCESS(matrix, row, column) > *maximum_value) {
                *maximum_value = ACCESS(matrix, row, column);
            }
        }
    }
    return SUCCESS;
}
/*
   Check if a matrix is diagonal. This is is a matrix in which the entries outside the main diagonal are all zero  
   If possible, it returns SUCCESS, otherwise FAILURE.
*/
int is_matrix_diagonal(Matrix* matrix) {
    if (!matrix || matrix->rows != matrix->columns) {
        return FAILURE;
    }
  for (int row = 0; row < matrix->rows; row++)
    for (int column = 0; column < matrix->columns; column++)
      if (row != column && ACCESS(matrix, row, column) != 0.0)
            return FAILURE;

  return SUCCESS;
}

/*
    Multiply a matrix by a factor. If possible, it returns SUCCESS, otherwise FAILURE.
*/

int multiply_matrix_by_factor(Matrix* matrix, double* factor, Matrix* result) {
    if (!matrix || !result) {
        return FAILURE;
    }
    for (int row = 0; row < matrix->rows; row++) {
        for (int column = 0; column < matrix->columns; column++) {
            ACCESS(result, row, column) = ACCESS(matrix, row, column) * (*factor);
        }
    }
    return SUCCESS;
}

/*
    Divide a matrix by a factor. If possible, it returns SUCCESS, otherwise FAILURE.
*/
int divide_matrix_by_factor(Matrix* matrix, double *factor, Matrix* result) {
    if (!matrix || !factor || !result) {
        return FAILURE;
    }
    if (factor == 0) {
        printf("No es posible dividir los valores entre 0\n"); 
        return FAILURE;
    }
    for (int row = 0; row < matrix->rows; row++) {
        for (int column = 0; column < matrix->columns; column++) {
            ACCESS(result, row, column) = ACCESS(matrix, row, column) / (*factor);
        }
    }
    return SUCCESS;
}

int sum_elements_from_matrix(Matrix* matrix, double* result) {
    if (!matrix || !result) {
        return FAILURE;
    }
    *result = 0;
    for (int row = 0; row < matrix->rows; row++) {
        for (int column = 0; column < matrix->columns; column++) {
            *result += ACCESS(matrix, row, column);
        }
    }
    return SUCCESS;
}

/*
   This matrix is an upper triangular matrix when all the elements below the main diagonal are zero.
*/
int is_upper_triangular_matrix(Matrix* matrix) {
    if (!matrix) {
        return FAILURE;
    }
    if (matrix->rows != matrix->columns) {
        return FAILURE;
    }
    
    for (int row = 0; row < matrix->rows; row++) {
        for (int column = 0; column < matrix->columns; column++) {
            if ((row > column && ACCESS(matrix, row, column) != 0)) {
                return FAILURE;
            }
        }
    }
    return SUCCESS;
}

/*
    Check whether two matrices have the same dimensions
*/

int do_matrices_have_same_dimensions(Matrix* matrix1, Matrix* matrix2) {
    if (!matrix1 || !matrix2) {
        return FAILURE;
    }

    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        return FAILURE; 
    }
    return SUCCESS;
}


/*********************************************/
/* 
    Auxiliary methods for parsing data
*/

/**********************************************/
/* 
    Parse a list of lists representing a term in SWI-Prolog into a matrix struct.
    Returns valid matrix pointer on success and NULL on failure
*/

Matrix* parse_list_of_lists_into_matrix(term_t tList) {
    int number_rows = 0; 
    int number_columns = 0;
   
    if (get_correct_dimensions(tList, &number_rows, &number_columns) ==  FAILURE){
        return NULL; 
    }
     Matrix* matrix = new_matrix(number_rows, number_columns); 
    // Check that the matrix is not null 
    if (!matrix) {
        return NULL; 
    }
    term_t tTail = PL_copy_term_ref(tList);
    term_t tHead = PL_new_term_ref();
    int current_row = 0;

    while (PL_get_list(tTail, tHead, tTail)) {

        if (!PL_is_list(tHead)) { // Check if the current element is a list
        printf("No se está pasando correctamente una lista de elementos\n");
        return NULL;
            }

        term_t inner_tail = PL_copy_term_ref(tHead);
        term_t inner_head = PL_new_term_ref();

        int integer_value; // The input could be an integer
        double double_value; // The input could be a double
        int current_column = 0;

        while (PL_get_list(inner_tail, inner_head, inner_tail)) {
            if (PL_get_integer(inner_head, &integer_value)) {
                ACCESS(matrix, current_row, current_column) = (double) integer_value;
                current_column++;

            } else if (PL_get_float(inner_head, &double_value)) {
                ACCESS(matrix, current_row, current_column) = double_value;
                current_column++;

            } else {
                printf("Asegúrate que todos los valores que se introduce a la matriz son valores numéricos\n");
                return NULL;
            }
        }
        current_row++;
        }

        return matrix;
    }

/*
    Parse a matrix struct into a list of lists. Returns SUCCESS if the operation is successful (if it is possible to unify the result with the list of lists), 
    otherwise returns FAILURE
*/
int parse_matrix_into_list_of_lists(Matrix* matrix, term_t resutltListofLists) {
    if (!matrix || !matrix->data || !matrix->rows || !matrix->columns) {
        return FAILURE; 
    }
    term_t tLists = PL_new_term_refs(matrix->rows); // These are consecutive references for all the lists. Each list represnts a row of the matrix

    for (int current_row = 0; current_row < matrix->rows; current_row++) {
        if (assign_matrix_row_values_to_list(matrix, tLists + current_row, current_row) == FAILURE) {
            return FAILURE;
        }
    }
    term_t allLists = PL_new_term_ref(); // This concatenates all the lists of for the rows into a single list makin a lists of lists. It has to be in ord
    PL_put_nil(allLists); // Make the the empty list
    for (int i = matrix->rows - 1; i >= 0; i--){ 
        if (!PL_cons_list(allLists, tLists + i, allLists)) {
            return FAILURE;
        }
    }
    return PL_unify(resutltListofLists, allLists);
}
/*
    Pass the values of the a row of a struct matrix into a list. Returns SUCCESS if the operation is successful, otherwise FAILURE
*/

int assign_matrix_row_values_to_list(Matrix* matrix, term_t tList, int current_row) {
    if (!matrix) {
        return FAILURE;
    }
    PL_put_nil(tList); // Concatenate the list of values for a row
    term_t current_value = PL_new_term_ref(); // Current double value of a row of the matrix
    for (int current_column = matrix -> columns - 1; current_column >= 0; current_column--) {
        if (!PL_put_float(current_value, ACCESS(matrix, current_row, current_column))) {
            return FAILURE;
        }
        if (!PL_cons_list(tList, current_value, tList)) {
            return FAILURE;
        }
    }    
    return SUCCESS;    
}

/*
    Return the the correct dimensions fo a matrix. Take into account that a single 
    nested list is a row and the elements of each list are the number of columns. 
    For instance, [[1,2,3],[2,3,4]] isas  valid matrix which has 2 rows and 3 columns. 
    Moreover, it will return SUCCESS if the matrix has valid dimensions, otherwise FAILURE.
*/
int get_correct_dimensions(term_t tList, int* rows, int* columns) {
    int total_rows = 0;
    int total_columns = 0;

    term_t head = PL_new_term_ref();
    term_t tail = PL_copy_term_ref(tList);

    // Check if the outer term is a list
    if (!PL_is_list(tList)) {
        printf("No se trata de una lista\n"); 
        return FAILURE;
    }
    // Iterate over the list
    while (PL_get_list(tail, head, tail)) {

        if (!PL_is_list(head)) {
            printf(" No se trata de una list \n");
            return FAILURE;
        }

        int current_columns = 0;
        term_t inner_tail = PL_copy_term_ref(head);
        term_t inner_head = PL_new_term_ref();

        // Iterate over the inner list to count the number of columns
        while (PL_get_list(inner_tail, inner_head, inner_tail)) {
            current_columns++;
        }
        // Update for the first columns
        if (total_rows == 0) {
            total_columns = current_columns;
        }
        // If the current row has a different number of columns than previous rows, it's not a valid matrix
        if (current_columns != total_columns) {
            printf("La matriz no tiene el mismo número de columnas en todas las filas\n");
            return FAILURE;
            }

        total_rows++;
    }
    if (rows != NULL && columns != NULL) {
        *rows = total_rows;
        *columns = total_columns;
    } else {
        return FAILURE;
    }
    return SUCCESS;
}
