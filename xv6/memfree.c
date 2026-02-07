#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int freebytes = memfree();
  if(freebytes < 0){
    printf(1, "memfree: syscall failed\n");
    exit();
  }
  printf(1, "free bytes: %d\n", freebytes);
  exit();
}
