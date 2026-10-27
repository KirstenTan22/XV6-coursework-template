#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int p[2];
int f = fork();
int pid = getpid(f);

pipe(p)
if (pid > 0) {
    printf()
    close(p[1])
} else {
    close(p[0]);
    write(p[1], "P", 1);
    close(p[1]);
}