#include "types.h"
#include "stat.h"
#include "user.h"

// Assuming cpu_time_limit is set to 500 (500 ticks)
#define cpu_time_limit 500

void cpu_intensive_task(int num) {
    int i;
    int sum = 0;
    for (i = 0; i < num; i++) {
        sum += i;
        printf(1, "%d\n", i);
        // Busy loop to consume CPU
    }
}

int main(int argc, char *argv[]) {
    cpulim(200, 16*1024*1024);
    printf(1, "cpulim is set 200\n");
    int num = atoi(argv[1]);
    uint start_tick = uptime();
    cpu_intensive_task(num);
    uint end_tick = uptime();
    uint elapsed_tick = (end_tick - start_tick);
    printf(1, "passed time with 200 cpulim %d\n", elapsed_tick);

    cpulim(400, 16*1024*1024);
    printf(1, "cpulim is set 400\n");
    start_tick = uptime();
    cpu_intensive_task(num);
    end_tick = uptime();
    elapsed_tick = (end_tick - start_tick);
    printf(1, "passed time with 400 cpulim %d\n", elapsed_tick);

    cpulim(800, 16*1024*1024);
    printf(1, "cpulim is set 800\n");
    start_tick = uptime();
    cpu_intensive_task(num);
    end_tick = uptime();
    elapsed_tick = (end_tick - start_tick);
    printf(1, "passed time with 800 cpulim %d\n", elapsed_tick);
    exit();
}
