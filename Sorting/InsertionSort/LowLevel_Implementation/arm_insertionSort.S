 /*
 The MIT License (MIT)
 
 Copyright (c) 2014 Paul Tomchik
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/


@ TODO: Improve the efficiency of the "memcpy" code by transfering words for as long as possible
@
@ See <stddef.h> for int value of NULL
@ 
@ This file implements the following function:
@ void arm_insertionSort(void *array, int numElems, size_t elemSize, int (*comparator)(void *elem1, void*elem2));

# define NULL #0

  .syntax unified
  .text
  .code   32

  .global arm_insertionSort
  .type   arm_insertionSort, %function
  .func   arm_insertionSort
arm_insertionSort:

  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  @@
  @@  PARAMS
  @@  r0: base address of the array
  @@  r1: number of elements in array
  @@  r2: size of an element
  @@  r3: pointer to the comparator function
  @@
  @@  LOCAL VARS
  @@  r4: array base
  @@  r5: outer loop cursor 
  @@  r6: elemSize
  @@  r7: comparator function pointer
  @@  r8: end of array
  @@  r9: &key
  @@ r10: inner loop cursor

  @ Early exit checks
  cmp     r0, NULL  @ Check array ref not NULL
  bxeq    lr
  cmp     r2, #1     @ Sanity check for elem size
  bxlt    lr

  @ INIT
  push    {r4, r5, r6, r7, r8, r9, r10, lr}  @ Preserve register values
  sub     sp, sp, r2         @ make room on the stack for the key
  mov     r9, sp

  @ Put params into preserved registers
  mov     r4, r0        @ r4 := arr
  mov     r5, r0        @ r5 := arr; init the outer loop cursor 
  mov     r6, r2        @ r6 := elemSize
  mov     r7, r3        @ r7 := ptr to comparator func
  mul     r8, r1, r2    @ get num of bytes in array
  add     r8, r0, r8    @ r8 := end of the array

outerLoop:
  add     r5, r5, r6    @ increment the outer loop cursor
  cmp     r5, r8        @ Are we at the end of the array?
  bge     done

  @ Move the key onto the stack 
  mov     r0, #0         @ r0 := 0; num of bytes transfered
storeKey:              
  ldr     r12, [r5, r0]  @ r12 := r5[r2]   
  str     r12, [r9, r0]  @ r9[r0] := r12; r10 = base of key
  add     r0, r0, #1     @ ++r2
  cmp     r0, r6         @ have we transfered the entire key ?
  bne     storeKey

  mov     r10, r5        @ inner cursor = outer cursor
innerLoop:
  sub     r10, r10, r6   @ decrement the inner loop cursor

  cmp     r10, r4        @ ? inner cursor before array base ?
  blt     breakInner     @ break the inner loop

  @ call comparator(innerCursor, &key)
callComparator:
  mov     r0, r10
  mov     r1, r9
  blx     r7            @ call comparator

  @ what did the comparator say?
  cmp     r0, #0        @ ? [inner cursor] <= key ?
  blt     breakInner    @ if so, break inner loop

  @ Neither break condition holds
  @ *(innerCursor+1) = *innerCursor
  mov     r0, #0
  add     r1, r10, r6   @ r1 := & next elem after inner cursor
swapElem:
  ldrb    r2, [r10, r0]     
  strb    r2, [r1, r0]
  add     r0, r0, #1
  cmp     r0, r6
  bne     swapElem
  beq     innerLoop

breakInner:
  @ *(innerCursor+1) = key
  mov     r0, #0
  add     r1, r10, r6   @ r1 := & next elem after inner cursor
swapKey:
  ldrb    r2, [r9, r0]     
  strb    r2, [r1, r0]
  add     r0, r0, #1
  cmp     r0, r6
  bne     swapKey
  b       outerLoop

done:
  add     sp, sp, r6
  pop     {r4, r5, r6, r7, r8, r9, r10, lr}   @ restore variables
  bx      lr                                  @ DONE
.endfunc
