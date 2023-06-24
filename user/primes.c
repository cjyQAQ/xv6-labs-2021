#include "kernel/types.h"
#include "user/user.h"

#define READ 0
#define WRITE 1

int is_prime(int num)
{
    if(num <= 1)
    {
        return 0;
    }
    if(num == 2)
    {
        return 1;
    }
    if(num%2 == 0)
    {
        return 0;
    }
    for(int i = 3;i*i<=num;i+=2)
    {
        if(num%i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void child_job(int *fd)
{
    close(fd[WRITE]);
    int pid;
    int cfds[2];
    int err = pipe(cfds);
    if (err < 0)
    {
        printf("pipe call error\n");
    }
    pid = fork();
    if(pid > 0)
    {
        int temp;
        close(cfds[READ]);
        while (read(fd[READ], &temp, sizeof(int)))
        {   
            if (is_prime(temp))
            {
                write(cfds[WRITE],&temp,sizeof(int));
            }
        }
        close(cfds[WRITE]);
        exit(0);
    }
    else if(pid == 0)
    {
        int temp;
        close(cfds[WRITE]);
        while (read(cfds[READ], &temp, sizeof(int)))
        {   
            printf("prime %d\n",temp);
        }
        close(cfds[READ]);
        exit(0);
    }
    else 
    {
        printf("fork error\n");
        exit(0);
    }
    
}

int main(int argc, char *argv[])
{
    int pid;
    int fds[2];
    int err = pipe(fds);
    if (err < 0)
    {
        printf("pipe call error\n");
    }
    pid = fork();
    if (pid == 0)
    {
        child_job(fds);
        exit(0);
    }
    else if (pid > 0)
    {
        close(fds[READ]);
        for (int i = 2; i <= 35; i++)
        {
            write(fds[WRITE], &i, sizeof(int));
        }
        close(fds[WRITE]);
        wait(0);
        exit(0);
    }
    else
    {
        printf("fork error\n");
        exit(0);
    }

    exit(0);
}