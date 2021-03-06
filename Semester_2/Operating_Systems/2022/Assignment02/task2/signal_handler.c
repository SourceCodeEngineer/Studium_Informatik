#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handlerSIGINT()
{
    write(STDOUT_FILENO, "Signal SIGINT received\n", 23);
}
void handlerSIGUSR1()
{
    write(STDOUT_FILENO, "Signal SIGUSR1 received\n", 23);
}
void handlerSIGTERM()
{
    write(STDOUT_FILENO, "Signal SIGTERM received\n", 23);
}
void handlerSIGKILL()
{
    write(STDOUT_FILENO, "Signal SIGKILL received\n", 23);
}

int main(){

    struct sigaction sa;
    sa.sa_handler = &handlerSIGINT;
    sa.sa_flags = SA_RESTART;

    struct sigaction sb;
    sb.sa_handler = &handlerSIGUSR1;
    sb.sa_flags = SA_RESTART;

    struct sigaction sc;
    sc.sa_handler = &handlerSIGTERM;
    sc.sa_flags = SA_RESTART;

    struct sigaction sd;
    sd.sa_handler = &handlerSIGKILL;
    sd.sa_flags = SA_RESTART;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR1, &sb, NULL);
    sigaction(SIGTERM, &sc, NULL);
    sigaction(SIGKILL, &sd, NULL);

    while(1){
        usleep(1000000);
    }
}
