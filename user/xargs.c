#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc,char *argv[])
{
    int pid;
    char arg[256],*args[MAXARG];
    if(argc < 2)
    {
        fprintf(2,"usage: xargs <command> ...\n");
        exit(0);
    }
    for(int i  = 1;i<argc;i++)
    {
        args[i-1] = argv[i];
    }
    char c;
    int index = 0;
    int n = 0;
    while((n = read(0,&c,1)) > 0)
    {
        if(c == '\n')
        {
            arg[index] = 0;
            pid = fork();
            if(pid > 0)
            {
                wait(0);
                index = 0;
            
            }
            else if(pid == 0)
            {
                args[argc - 1] = arg;
                args[argc] = 0;
                exec(args[0],args);
                
            }
            else
            {
                printf("fork error\n");
                exit(0);
            }
        }
        else
        {
            arg[index++] = c;
        }
    }
    exit(0);
}