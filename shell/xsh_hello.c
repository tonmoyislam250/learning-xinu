/* xsh_arp.c - xsh_arp */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

void prod2(sid32 consumed, sid32 produced), cons2(sid32 consumed, sid32 produced);
void sndA(void), sndB(void);
int32 n = 0;

shellcmd xsh_hello(int nargs, char *args[])
{
	printf("Hello World Tohidul\n");

	// resume(create(sndA, 1024, 20, "process 1", 0));
    // resume(create(sndB, 1024, 20, "process 2", 0));


    sid32 produced, consumed;
    consumed = semcreate(0);
    produced = semcreate(1);
	//pid of semaphore
    pid32 pid = getpid();
	printf("Hello: %d\n", pid);
    resume(create(cons2, 1024, 20, "cons", 2, consumed, produced));
    resume(create(prod2, 1024, 20, "prod", 2, consumed, produced));
	return 0;
}

void prod2(sid32 consumed, sid32 produced)
{
    int32 i;
	pid32 pid = getpid();
	printf("Produce : %d\n", pid);
    for (i = 1; i <= 20; i++)
    {
        wait(consumed);
        n++;
        signal(produced);
    }
}


void cons2(sid32 consumed, sid32 produced)
{
    int32 i;
	pid32 pid = getpid();
	printf("Consumer: %d\n", pid);
    for (i = 1; i <= 20; i++)
    {
        wait(produced);
        printf("n is %d \n", n);
        signal(consumed);
    }
}


void sndA(void)
{
    while (1)
        putc(CONSOLE, 'A');
}

void sndB(void)
{
    while (1)
        putc(CONSOLE, 'B');
}
