
#include "kernel/types.h"
#include "user.h"


int parse_int(const char *arg)
{
    const char *p = arg;
    for(;*p;p++)
    {
        if(*p < '0' && *p > '9')
        {
            return -1;
        }
    }
    return atoi(arg);
}

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf("input one argument only\n");
    exit(0);
  }

    int time = parse_int(argv[1]);
    if(time < 0)
    {
        printf("time is error : %s\n",argv[1]);
        exit(0);
    }
  sleep(time);
  exit(0);
}
