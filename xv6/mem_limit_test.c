#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int K = 1024;
    printf(1, "Hello im process with id %d\n", getpid());
    cpulim(1000, atoi(argv[1]) * 1024);
    free(malloc(1*K));
    void *m1 = malloc(1*K); // allocated mem up to now is 1K
    void *m2 = malloc(1*K); // allocated mem up to now is 2K
    free(m1);               // allocated mem up to now is 1K
    malloc(5*K);            // allocated mem up to now is 6K
    malloc(4*K);            // allocation not possible
    exit();
}
