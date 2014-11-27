  .syntax unified
  .text
  .code   32

  .global radixsort
  .type   radixsort, %function
  .func   radixsort

/*********************************************************
*
* parameters:
*   r0 = pointer the array of integers
*   r1 = length of the array
*
* variables:
*   r4 = pointer to the input array
*   r5 = pointer to the output array
*   r6 = pointer to counting sort's workspace array
*   r7 = size of the input array in bytes
*   r8 = end of counting sort's workspace array
*
* NOTES:
*   The digit size on which counting sort works is 16bits.
*
*********************************************************/

radixsort:

 // SETUP
  push  {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
  mov   r4, r0                  // Pointer to the input array
  mov   r7, r1, lsl #2          // size of the input array in bytes TODO limits max arr size

  // Allocate n*4 bytes for the output array.
  mov   r0, r7
  bl    malloc                
  mov   r5, r0                   // r5 := &outputArray
  mov   r0, #-1
  cmp   r5, #0
  beq   exit

  // Allocate 2^16 * 4 bytes for counting sort's workspace
  mov   r8, #1         
  mov   r8, r8, lsl #16          // r8 <- size of counting sort's workspace        
  mov   r0, r8
  mov   r1, #4
  bl    calloc
  mov   r6, r0
  add   r8, r6, r8               // r8 <- workspace end address
  mov   r0, #-1
  cmp   r6, #0
  beq   exit

  /**************************************
  *
  *  Counting Sort subroutine 
  *
  *  r9  : the bitmask
  *  r10 : cursor
  *  r11 : input array
  *  r12 : output array
  *
  ***************************************/

  mov   r9, #0xFF                // r0 <- init the bitmask for counting sort.
  orr   r9, r9, #0xFF00

  // Counting sort first pass initialization.
  mov   r11, r4                  // r11 :=
  mov   r12, r5
  mov   r3, #0
 
 tallyValueCounts:
  mov   r10, r11
  add   r2, r10, r7              // r2 <- end of the input array
 // Tally number of occurances of each digit.
 tallyLoop:
  ldr   r0, [r10], #4            // r0 <- inputArr[i++] 
  and   r0, r0, r9               // r0 <- apply the mask
  lsr   r0, r0, r3               // r0 <- rightshift 0 || 16
  ldr   r1, [r6, r0, lsl #2]     // r1 <- workspace[r0]
  add   r1, r1, #1               // ++r1
  str   r1, [r6, r0, lsl #2]     // workspace[r0] <- r1
  cmp   r2, r10
  bgt   tallyLoop
 
  mov   r10, r6                  // r10 := beginning of workspace
  mov   r0, #0 
 // Create running rum from the tallys.
 runningSumLoop:
  ldr   r1, [r10]
  add   r0, r0, r1
  str   r0, [r10], #4 
  cmp   r8, r10
  bgt   runningSumLoop

  add   r10, r11, r7           // r10 <- init cursor to end of input array
 // Fill the output array.
 transferValuesToOutputArray:
  ldr   r0, [r10, #-4]!        // r0 := *cursor
  and   r1, r0, r9             // r1 := r0 && mask
  lsr   r1, r3                 // r1 := r1 >> r3 
  ldr   r2, [r6, r1, lsl #2]   // r2 := r5[r1]
  sub   r2, r2, #1             // decrement the value in r5[r1]; gives you index into array.
  str   r2, [r6, r1, lsl #2]
  str   r0, [r12, r2, lsl #2]  // r12[r2] := r0
  cmp   r10, r11               // have we transfered all values in the input array?
  bne   transferValuesToOutputArray

  cmp   r3, #0
  bne   radixsortDONE         

  // Counting sort's second pass initialization.
  mov   r0, r6                 
  mov   r1, #0
  mov   r2, r8
  bl    __aeabi_memset          // Zero out counting sort's workspace

  mov   r3, #16                 // Now looking at bits 17-32
  mov   r11, r5                 // Input array to counting sort now last pass' output
  mov   r12, r4                 // Output array now radix sort's input array/
  lsl   r9, r9, #16             // Leftshift the mask.
  b     tallyValueCounts 

 // TEAR DOWN
 radixsortDONE:
  // Free the output array
  mov   r0, r5
  bl    free 

  // Free counting sort's workspace
  mov   r0, r6
  bl    free 

  pop   {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
  bx    lr
.endfunc
