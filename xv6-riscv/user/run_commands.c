#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"
#include <ctype.h>

void execute_left_side(char** args, int *p) {

  // Create a child process for executing the
  // left-side command.
  int f = fork();
  if (f < 0) {
    fprintf(2, "run_command: fork failed\n");
    exit(1);
  } else if (f == 0) {
    // TODO: Use close and dup to close FD 1, and reopen it by
    // duplicating p[1].
    close(1);
    dup(p[1]);

    // TODO: Execute the command with the exec() system call
    exec(args[0], args);
  }
  // Do not use wait() here as before. Parent should continue
  // in the main method.
}

void execute_right_side(char** args, int *p) {

  // Create a child process for executing the
  // right-side command.
  int f = fork();
  if (f < 0) {
    fprintf(2, "run_command: fork failed\n");
    exit(1);
  } else if (f == 0) {
    // TODO: Use close and dup to close FD 0, and reopen it by
    // duplicating p[0].
    close(0);
    dup(p[0]);

    // TODO: Execute the command with the exec() system call
    exec(args[0], args);
  } else {
    // Use wait to wait for both child processes to complete separately.
    wait(0);
  }
}

int main(int argc, char *argv[]) {

  // Array of pointers for storing a command and a null terminator.
  char *args[6] = {0};
  args[2] = 0;
  args[5] = 0;

  // Pipe for communication between commands.
  int p[2];

  // Storage for reading in data from the standard input.
  char buf[512], *b;
  args[0] = buf;

  // Point b to the first character in the line.
  b = buf;

  while (1) {
    // Read characters from the standard input. When we find '\n' that
    // means one line has terminated.
    b = buf;
    // TODO: Create a new pipe here on every iteration.
    pipe(p);
    fprintf(2, "\nPlease enter the first command and press enter (type 'q' to exit):\n");
    while (read(0, b, 1) > 0) {
      if (*b == '\n') {
        // Replace the end of line character by the string terminating
        // character.
        *b = '\0';
        if (buf[0] == 'q')
          // TODO: Exit with the exit() system call.
            exit(0);
        else {
          // TODO: Execute the left-hand side.
          char *sub_array[] = {args[0], args[1], args[2]};
          execute_left_side(sub_array, p);

          // TODO: Close write-end of a pipe, otherwise right-hand side child process
          // will continously wait for the data.
          close(p[1]);
          break;
        }
      } else if (*b == ' ') {
        // Terminate the string.
        *b = '\0';
        b++;
        // Save the pointer to the next string.
        args[1] = b;
      } else
        b++;
    }

    fprintf(2, "\nPlease enter the second command and press enter:\n");
    args[3] = b;
    while (read(0, b, 1) > 0) {
      if (*b == '\n') {
        // Replace the end of line character by the string terminating
        // character.
        *b = '\0';
        // TODO: execute the right-hand side command.
        char *sub_array[] = {args[3], args[4], args[5]};
        execute_right_side(sub_array, p);
        break;
      } else if (*b == ' ') {
        // Terminate the string.
        *b = '\0';
        b++;
        // Save the pointer to the next string.
        args[4] = b;
      }
      else
        b++;
    }
  }

  exit(0);
}
