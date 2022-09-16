#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// anonymous type alias name InputBuffer for struct InputBuffer
// the type can be named when we need self-referential struct (typedef struct
// InputBuffer) or sometime for debugging ?
//
// self referential type can also be written like this :
//
// typedef struct InputBuffer_S InputBuffer;
// struct InputBuffer_S {
//  InputBuffer *input_buffer;
// };
//
//
typedef struct {
  char *buffer;
  // size_t -> size of an allocated block of memory
  size_t buffer_length;
  // ssize_t == size_t, but signed
  ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer() {
  // malloc allocate a block of memory on the heap and return a pointer to it
  // to deallocate the memory, we need to pass the pointer to free()
  InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

// C use 3 types of memory allocation area : stack, heap and static
// stack -> memory allocated for local variables
// heap -> memory allocated for dynamic memory allocation
// static -> memory allocated for global variables

void print_prompt() { printf("db > "); }

// & return a pointer
// pointer are just variable that store memory address
// in c everything is passed by value,
// if we want to modify a variable i with a function,
// we need to pass a pointer to i to the function to then manipulate the memory
// address
//
// simply passing the value of i to the function will not work
// because the value of i will be copied
//
// In this case, we pass the address of i to the function
// then we can manipulate the value of i with the address
//
// void f(int *j) {
//	*j = 1;
// }
//
// int main() {
// 	int i = 0;
// 	f(&i);
// }
//
// main()
// i will be equal to 1
//
// a variable not declared as a pointer will be pre allocated on the stack at
// compile time and cannot be deferenced
//
// local variable are automatically freed at the end of their scope
// to prevent this we can use static variable
// static variable lifetime is the lifetime of the program
//
// NULL
// a null pointer is a pointer that points to nothing (no memory address)
// accessing the value pointed by a null pointer will result in a segmentation
// fault
//

void read_input(InputBuffer *input_buffer) {
  // getline() read a line and return the number of bytes read or -1 if error
  // getline() need a double pointer as a first argument because
  // in case buffer point to null it will modify buffer to point to a new buffer
  // so we need to pass the address of buffer to modify it
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer *input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

int main(int argc, char *argv[]) {
  InputBuffer *input_buffer = new_input_buffer();
  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, ".exit") == 0) {
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
  }
}
