#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    cpulim(1000, atoi(argv[1]) * 1024);
    for (int i = 0; i < 4; i++)
    {
        if (malloc(atoi(argv[2]) * 1024) == 0)
        {
            printf(1, "allocation failed\n");
            break;
        }
        printf(1, "allocation succesful on %dth itr\n", i + 1);
    }
    exit();
}
