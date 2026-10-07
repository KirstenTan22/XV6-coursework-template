#include "user/user.h"
#include "kernel/types.h"

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