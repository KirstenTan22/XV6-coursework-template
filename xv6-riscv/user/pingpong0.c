#include "kernel/types.h"
#include "user/user.h"

int main() {
  // Declare two pipes
  // p2c - a parent to a child communication
  // c2p - a child to a parent communication
  int p2c[2];
  int c2p[2];

  // Call the pipe() system call to create p2c and c2p
  pipe(p2c);
  pipe(c2p);

  // Declare one byte for sending to the child process
  char our_byte = 'P';

  // Fork a new process
  int pid = fork();
  if (pid > 0) {
    close(p2c[0]);
    close(c2p[1]);

    // 1. PLACE YOUR CODE HERE TO SEND A BYTE TO THE OTHER PROCESS
    write(p2c[1], &our_byte, 1);
    // 5. PLACE YOUR CODE HERE TO RECEIVE THE MODIFIED BYTE
    read(c2p[0], &our_byte, 1);
    printf("Received pong: %c\n", our_byte);

    close(p2c[1]);
    close(c2p[0]);

    wait(0);
    exit(0);

  }
  else if (pid == 0) {
    close(p2c[1]);
    close(c2p[0]);

    // 2. PLACE YOUR CODE HERE TO READ A BYTE IN THE PIPE p2c
    read(p2c[0], &our_byte, 1);
    printf("Received ping: %c\n", our_byte);
    // 3. PLACE YOUR CODE HERE TO MODIFY THE BYTE TO LETTER 'R'
    our_byte = 'R';
    // 4. PLACE YOUR CODE HERE TO SEND THE BYTE BACK OVER c2p PIPE
    write(c2p[1], &our_byte, 1);

    close(p2c[0]);
    close(c2p[1]);
    exit(0);
  }
  exit(0); // Exit parent process
}
