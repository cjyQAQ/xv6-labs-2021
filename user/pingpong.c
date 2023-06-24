#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char *argv[])
{
    int p2cfds[2];
    int c2pfds[2];
    int err1 = pipe(p2cfds);
    int err2 = pipe(c2pfds);
    char prbuf[64] = "";
    char crbuf[64] = "";
    if(err1 < 0)
    {
        printf("create parent pipe error\n");
        exit(0);
    }
    if(err2 < 0)
    {
        printf("create parent pipe error\n");
        exit(0);
    }
    int pid = fork();
    if(pid > 0)
    {   
        close(p2cfds[0]);
        write(p2cfds[1],"ping",strlen("ping"));
        close(p2cfds[1]);
        close(c2pfds[1]);
        read(c2pfds[0],prbuf,sizeof(prbuf));
        printf("%d: received %s\n",getpid(),prbuf);  
        exit(0);
    }
    else if(pid == 0)
    {
        close(c2pfds[0]);
        read(p2cfds[0],crbuf,sizeof(crbuf));
        printf("%d: received %s\n",getpid(),crbuf);    
        close(p2cfds[1]);
        write(c2pfds[1],"pong",strlen("pong"));
        close(c2pfds[1]);   
        exit(0);
    }
    else
    {
        printf("fork error\n");
        exit(0);
    }
    exit(0);
}