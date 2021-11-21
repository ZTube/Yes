// compile with 'gcc yes.c -o yes -O2 -march=native -masm=intel'
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// Defines how often the characters in yes should be repeated
// in an exponential way as 2^YES_MAG
#define YES_MAG 25

void main() {
  // Declare the characters to be printed out repeatedly
  char yes[] = {'y', '\n'};
  // Calculate the size of the output buffer
  size_t size = sizeof(yes) * pow(2, YES_MAG);

  char *buffer = malloc(size);

  // Initialize the buffer with a repetition of the
  // characters in yes
  for (long i = 0; i < size; i++) {
    buffer[i] = yes[i % sizeof(yes)];
  }

  __asm__ (
      "mov %%rdi, 1;" // Write to stdout
      "mov %%rsi, %0;" // The buffer containing the output
      "mov %%rdx, %1;" // The size of the buffer
      "print_loop:"
      "mov %%rax, 1;" // Set the syscall to be 'write'
      "syscall;"
      "jmp print_loop;" // Repeat the write call
      :
      :"r" (buffer), "r" (size)
      :"%rax","%rdi","%rsi","%rdx"
  );
}
