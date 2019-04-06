#include <stddef.h>

/*@ predicate monotone_slice(int* a, size_t low, size_t up) =
  (\forall integer i,j; low <= i <= j < up ==> a[i] < a[j]) ||
  (\forall integer i,j; low <= i <= j < up ==> a[i] >= a[j]);

*/

/*@
	requires length < 100;
    requires a_valid: \valid(a + (0 .. length - 1));
    requires res_valid: \valid(cutpoints + (0 .. length));
    assigns cutpoints[0 .. length];
    ensures pos: \result > 0;
    ensures beg: cutpoints[0] == 0;
    ensures end: cutpoints[\result - 1] == length;
    ensures bounds: \forall integer i; 0 <= i < \result ==>
      0<= cutpoints[i] <= length;
    ensures monotonic:
      \forall integer i; 0 <= i < \result - 1 ==>
      monotone_slice(a,cutpoints[i],cutpoints[i+1]);
*/
size_t monotonic(int* a, size_t length, size_t* cutpoints) {
  cutpoints[0] = 0;
  if(length == 0) return 1;
  size_t x = 0, y = 1;
  size_t res = 1;
  /*@
    loop invariant outer_bound: 1 <= y <= length;
    loop invariant x: x == y - 1;
    loop invariant monotone:
      \forall integer i; 0 <= i < res - 1 ==>
      monotone_slice(a,cutpoints[i],cutpoints[i+1]);
    loop invariant res_bounds: 1 <= res <= length;
    loop invariant content_bounds:
      \forall integer i; 0 <= i < res ==> 0<= cutpoints[i] <= length;
    loop assigns x,y,res,cutpoints[1 .. length];
    loop variant length - y;
   */
  while (y < length) {
    int increasing = a[x] < a[y];
    /*@
      loop invariant inner_bound: x + 1 <= y <= length;
      loop invariant mono_slice: monotone_slice(a,x,y);
      loop assigns y;
      loop variant length - y;
    */
    while (y < length && (a[y-1] < a[y]) == increasing) y++;
    cutpoints[res] = y;
    res++;
    x = y;
    if (y < length) y++;
  }
  if (x < length) {
    /*@ assert monotone_slice(a,x,length); */
    cutpoints[res] = length;
    res++;
  }
  return res;
}