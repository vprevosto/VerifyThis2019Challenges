#include <stddef.h>

typedef struct {
  size_t row;
  size_t col;
  int v;
} coo;

/*@ logic integer l_vec_mult(int* vec, int** m,
                             integer length, integer idx, integer j) =
      j == length ? 0 : l_vec_mult(vec,m,length,idx,j+1) + vec[j] * m[idx][j];
*/

/*@ predicate repr(coo* mat, size_t mat_length, int** rep) =
  \forall integer i; 0 <= i < mat_length ==>
  rep[mat[i].row][mat[i].col] == mat[i].v
  &&
  \forall integer i,j;
  (\forall integer k; 0<= k < mat_length ==>
    mat[k].row != i || mat[k].col !=j)
  ==> rep[i][j] == 0;
*/

/*@ requires \valid(vec + (0 .. length - 1));
    requires \valid(out + (0 .. length - 1));
    requires \valid(mat + (0 .. mat_length - 1));
    requires \separated (vec + (0 .. length - 1), mat + (0 .. length - 1),
                         out + (0 .. length - 1));
    requires \forall integer i; 0 <= i < mat_length - 1 ==> mat[i].row < length;

    requires
      \forall integer i, j; 0 <= i <= j < length ==>
         mat[i].row < mat[j].row ||
           (mat[i].row == mat[j].row &&
            mat[i].col <= mat[j].col);

   requires repr(mat,mat_length,rep);

   assigns out[0 .. length - 1];

   ensures \forall integer i; 0 <= i < length ==>
            out[i] == l_vec_mult(vec,rep,length,i,0);

*/
void vec_mult(int * vec, size_t length, coo* mat, size_t mat_length, int* out,
              int ** rep) {
  /*@ loop invariant 0 <= i <= length;
      loop invariant \forall integer j; 0 <= j < i ==> out[j] == 0;
      loop assigns i,out[0 .. length - 1];
      loop variant length - i;
  */
  for(size_t i = 0; i < length; i++) out[i] == 0;
  /*@ loop invariant bound: 0 <= i <= mat_length;
      loop invariant lower_rows:
        i > 0 ==>
        \forall integer j;
           0 <= j < mat[i-1].row ==> out[j] == l_vec_mult(vec,rep,length,j,0);
      loop invariant current_row:
        i > 0 ==> out[mat[i-1].row] ==
                  l_vec_mult(vec,rep,mat[i-1].col,mat[i-1].row,0);

      loop assigns i, out[0 .. length-1];
   */
  for(size_t i = 0; i < mat_length; i++) {
    out[mat[i].col]+= vec[mat[i].row] * mat[i].v;
  }
}
