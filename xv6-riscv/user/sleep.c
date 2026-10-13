#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int timer;

    if (argc < 2) {
        printf("Error: Please pass one argument");
        exit(1);
    }

    timer = atoi(argv[1]);

    pause(timer);

    exit(0);
}