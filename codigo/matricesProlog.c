#include "definitions.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <SWI-Prolog.h>


/*
  Class in charge of calling the logic functions for the matrices done by C 
  and installing the the foreign predicates so that they can be called from SWI-Prolog
*/

/*
   Foreign predicate for the addition of two matrices
*/
foreign_t pl_matrices_addition(term_t matrix1, term_t matrix2, term_t result){
   
    Matrix* m1 = parse_list_of_lists_into_matrix(matrix1);
    Matrix* m2 = parse_list_of_lists_into_matrix(matrix2);
    if (!m1 || !m2) {
        PL_fail;
    }
    Matrix* matrix_result = new_matrix(m1->rows, m1->columns);
    if (!matrix_result) {
        PL_fail;
    }
  
    if (matrices_addition(m1 ,m2 ,matrix_result) == FAILURE) { 
        PL_fail;
    }
    term_t matrix_list = PL_new_term_ref();

    if(parse_matrix_into_list_of_lists(matrix_result, matrix_list) == FAILURE) {
        PL_fail;
    }
    return PL_unify(result, matrix_list);
}
/*
 Foreign predicate for the substraction of two matrices
*/
foreign_t pl_matrices_substraction(term_t matrix1, term_t matrix2, term_t result){
    Matrix* m1 = parse_list_of_lists_into_matrix(matrix1);
    Matrix* m2 = parse_list_of_lists_into_matrix(matrix2);
    if (!m1 || !m2) {
        PL_fail;
    }
    Matrix* matrix_result = new_matrix(m1->rows, m1->columns);
    if (!matrix_result) {
        PL_fail;
    }

    if (matrices_substraction(m1 ,m2 ,matrix_result) == FAILURE) { 
        PL_fail;
    }
    term_t matrix_list = PL_new_term_ref();

    if(parse_matrix_into_list_of_lists(matrix_result, matrix_list) == FAILURE) {
        PL_fail;
    }
    return PL_unify(result, matrix_list);
}

/*
  Foreign predicate for the multiplication of two matrices
*/

foreign_t pl_matrices_multiplication(term_t matrix1, term_t matrix2, term_t result) {
    Matrix* m1 = parse_list_of_lists_into_matrix(matrix1);
    Matrix* m2 = parse_list_of_lists_into_matrix(matrix2);
    if (!m1 || !m2) {
      PL_fail;
    }
    Matrix* matrix_result = new_matrix(m1->rows, m2->columns);
    if (matrices_multiplication(m1 ,m2 ,matrix_result) == FAILURE) { 
        PL_fail;
    }
    
    term_t matrix_list = PL_new_term_ref();
    if(parse_matrix_into_list_of_lists(matrix_result, matrix_list) == FAILURE) {
      PL_fail;
    }
  return PL_unify(result, matrix_list);
}

/*
  Foreign predicate to obtain the transpose of a matrix
*/

foreign_t pl_matrices_transpose(term_t matrix, term_t result) {
    Matrix* m = parse_list_of_lists_into_matrix(matrix);
    if (!m) {
        PL_fail;
    }
    Matrix* matrix_result = new_matrix(m->columns, m->rows); 
    if (matrix_transpose(m, matrix_result) == FAILURE) {
        PL_fail;
    }
    term_t matrix_list = PL_new_term_ref();
    if(parse_matrix_into_list_of_lists(matrix_result, matrix_list) == FAILURE) {
      PL_fail;
    }
  return PL_unify(result, matrix_list);
}

/*
  Foreign predicate to obtain the dot product of two vectors
*/

foreign_t pl_vectors_dot_product(term_t vector1, term_t vector2, term_t result) {
    Matrix* v1 = parse_list_of_lists_into_matrix(vector1);
    Matrix* v2 = parse_list_of_lists_into_matrix(vector2);
    if (!v1 || !v2) {
      PL_fail;
    }
    double dot_product = 0;
    if (calculate_dot_product(v1, v2, &dot_product) == FAILURE) {
      PL_fail;
    }
    return PL_unify_float(result, dot_product);
}

/*
  Foreign predicate to obtain the maximum value of a matrix
*/

foreign_t pl_obtain_maximum_value_from_matrix(term_t matrix, term_t result) {
    Matrix* m = parse_list_of_lists_into_matrix(matrix);
    if (!m) {
      PL_fail;
    }
    double maximum_value = -INFINITY;
    if (obtain_maximum_value_from_matrix(m, &maximum_value) == FAILURE) {
      PL_fail;
    }
    return PL_unify_float(result, maximum_value);
}

/*
  Foreign predicate to check whether a matrix is diagonal
*/

foreign_t pl_is_diagonal(term_t matrix) {
    Matrix* m = parse_list_of_lists_into_matrix(matrix);
    if (!m) {
      PL_fail;
    }
    if (is_matrix_diagonal(m) == FAILURE) {
      PL_fail;
    }
    PL_succeed;
}
/*
  Foreign predicate to obtain a matrix in which all its elements have been 
  multiplied by a factor
*/

foreign_t pl_multiply_matrix_by_factor(term_t matrix, term_t factor, term_t result) {
    Matrix* m = parse_list_of_lists_into_matrix(matrix);
    if (!m) {
      PL_fail;
    }
    double double_factor;
    int integer_factor;
     if (PL_get_integer(factor, &integer_factor)) {
        double_factor = (double)integer_factor;
     } else if (PL_get_float(factor, &double_factor) == FAILURE) {
        PL_fail;
     }

    Matrix* matrix_factor = new_matrix(m->rows, m->columns);
    if (multiply_matrix_by_factor(m, &double_factor, matrix_factor) == FAILURE) {
      PL_fail;
    }

    term_t matrix_list = PL_new_term_ref();
    if(parse_matrix_into_list_of_lists(matrix_factor, matrix_list) == FAILURE) {
      PL_fail;
    }
    return PL_unify(result, matrix_list);
}

/*
  Foreign predicate to obtain a matrix in which all its elements have been 
  divided by a factor
*/

foreign_t pl_divide_matrix_by_factor(term_t matrix, term_t factor, term_t result) {
    Matrix* m = parse_list_of_lists_into_matrix(matrix);
    if (!m) {
      PL_fail;
    }
    double double_factor;
    int integer_factor;
     if (PL_get_integer(factor, &integer_factor)) {
        double_factor = (double)integer_factor;
     } else if (PL_get_float(factor, &double_factor) == FAILURE) {
        PL_fail;
     }

    Matrix* matrix_factor = new_matrix(m->rows, m->columns);
    if (divide_matrix_by_factor(m, &double_factor, matrix_factor) == FAILURE) {
      PL_fail;
    }

    term_t matrix_list = PL_new_term_ref();
    if(parse_matrix_into_list_of_lists(matrix_factor, matrix_list) == FAILURE) {
      PL_fail;
    }
    return PL_unify(result, matrix_list);
}

/* 
  Foreign predicates to obatin the sum of all the elements of a matrix
*/

foreign_t pl_sum_elements_from_matrix(term_t matrix, term_t result) {
    Matrix* m = parse_list_of_lists_into_matrix(matrix);
    if (!m) {
      PL_fail;
    }
    double sum;
    if (sum_elements_from_matrix(m, &sum) == FAILURE) {
      PL_fail;
    }
    return PL_unify_float(result, sum);
}
/*
  Foreign predicate to check whether a matrix is an upper triangular matrix 
*/
foreign_t pl_is_upper_triangular_matrix(term_t matrix) {
  Matrix* m = parse_list_of_lists_into_matrix(matrix);
  if (!matrix) {
        PL_fail;
    }
    if (is_upper_triangular_matrix(m) == FAILURE) {
      PL_fail;
    }
    PL_succeed;
}

/*
  Check whether two matrices have the same number of columns and rows
*/

foreign_t pl_matrices_with_same_dimensions(term_t matrix1, term_t matrix2) {
    Matrix* m1 = parse_list_of_lists_into_matrix(matrix1); 
    Matrix* m2 = parse_list_of_lists_into_matrix(matrix2);
    if (!m1 || !m2) {
      PL_fail;
    }
    if (do_matrices_have_same_dimensions(m1,m2) == FAILURE) {
      PL_fail;
    }
    PL_succeed;
}

install_t
install() {
    PL_register_foreign("sumar_matrices", 3 , pl_matrices_addition, 0);
    PL_register_foreign("restar_matrices", 3 , pl_matrices_substraction, 0);
    PL_register_foreign("multiplicar_matrices", 3, pl_matrices_multiplication, 0);
    PL_register_foreign("transponer_matriz", 2, pl_matrices_transpose, 0);
    PL_register_foreign("producto_escalar", 3, pl_vectors_dot_product, 0);
    PL_register_foreign("obtener_valor_maximo", 2, pl_obtain_maximum_value_from_matrix, 0);
    PL_register_foreign("es_diagonal", 1, pl_is_diagonal, 0);
    PL_register_foreign("multiplicar_matriz_por_factor", 3, pl_multiply_matrix_by_factor, 0);
    PL_register_foreign("dividir_matriz_por_factor", 3, pl_divide_matrix_by_factor, 0);
    PL_register_foreign("sumar_elementos_de_matriz", 2, pl_sum_elements_from_matrix, 0);
    PL_register_foreign("es_matriz_diagonal_superior", 1, pl_is_upper_triangular_matrix, 0);
    PL_register_foreign("matrices_mismas_dimensions", 2, pl_matrices_with_same_dimensions, 0);
}



