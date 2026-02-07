#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_cpulim(void)
{
  int cpu_lim, mem_lim;
  if(argint(0, &cpu_lim) < 0 || argint(1, &mem_lim) < 0){
    return -1;
  }

  if(cpu_lim > 1000 || cpu_lim < 0){
    return -1;
  }

  if(mem_lim < 0){
    return -1;
  }

  cpu_time_limit = cpu_lim;
  mem_limit = mem_lim;
  return 0;
}

int 
sys_memuse(void){
  int amount;
  if(argint(0, &amount) < 0){
    return -1;
  }

  struct proc *p = myproc();
  int new_amount = p->mem_used + amount;
  if(new_amount < 0 || new_amount > mem_limit){
    return -1;
  }
  p->mem_used += amount;
  cprintf("process %d and uasge %d\n", p->pid, p->mem_used);
  return 0;
}
int
sys_memfree(void)
{
  return kfreebytes();
}
