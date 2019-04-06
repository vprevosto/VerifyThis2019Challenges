#include <stddef.h>

/*@ requires \valid(s + (0 .. length - 1));
    requires \valid(stack + (0 .. length - 1));
    requires \valid(left + (0 .. length - 1));
    requires \separated(stack + (0 .. length - 1),left + (0 .. length - 1));
    assigns stack[0 .. length - 1], left[0 .. length - 1];

    ensures wf_left: \forall integer i; 0 <= i < length ==> left[i] <= i;
    ensures left_small:
    \forall integer i; 0 <= i < length ==>
     left[i] > 0 ==> s[left[i]-1] < s[i];
     ensures left_smallest:
     \forall integer i; 0 <= i < length ==>
        \forall integer j; left[i] <= j < i ==> s[j] >= s[i];
*/
void neighbor(int* s, size_t length, size_t* stack, size_t* left) {
  size_t sidx = 0;
  /*@ loop invariant 0 <= x <= length;
      loop invariant 0 <= sidx <= x;
      loop invariant stack_left:
        \forall integer i; 0 <= i < sidx ==> 0 < stack[i] <= x;
      loop invariant wf_left:
        \forall integer i; 0 <= i < x ==> left[i] <= i;
      loop invariant left_small:
        \forall integer i; 0 <= i < x ==> s[left[i] - 1] < s[i];
      loop invariant left_smallest:
        \forall integer i; 0 <= i < x ==>
          \forall integer j; left[i] <= j < i ==> s[j] >= s[i];
      loop invariant stack_order:
        \forall integer i, j; 0<= i < j < sidx ==> stack[i] < stack[j];
      loop invariant stack_sorder:
        \forall integer i, j;
          0<= i < j < sidx ==> s[stack[i]-1] < s[stack[j]-1];
      loop invariant stack_wf:
        \forall integer j; 0 <= j < x ==>
        s[j] < s[x] ==> \exists integer sj; 0 <= sj < sidx && stack[sj] == j+1;
      loop invariant stack_push: sidx > 0 ==> stack[sidx-1] == x;
      loop assigns x, sidx, stack[0 .. length - 1], left[0 .. length - 1];
      loop variant length - x;
   */
  for (size_t x = 0; x < length; x++) {
    /*@
        loop invariant 0 <= sidx <= \at(sidx,LoopEntry);
        loop invariant stack:
          \forall integer i;
             sidx <= i < \at(sidx,LoopEntry) ==> s[stack[i]-1] >= s[x];
        loop assigns sidx;
        loop variant sidx;
     */
    while (sidx > 0 && s[stack[sidx-1]-1] >= s[x]) sidx--;
    if (sidx == 0) {
      left[x] = 0;
    } else {
      left[x] = stack[sidx - 1];
    }
    stack[sidx] = x + 1;
    sidx++;
  }
}
