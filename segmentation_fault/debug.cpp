# include <execinfo.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# define SIZE 100

//dump mem map
void dumpmap()
{
        char cmd[30] = {'\0'};
        sprintf(cmd,"cat /proc/%d/maps",getpid());

        system(cmd);

        exit(0);
}

//dump stack trace
void print_trace(void)
{
		int i, addr_num;
		void *buffer[100];
		char **strings;

    	/*The backtrace() return the number of buffer address*/
		addr_num = backtrace(buffer, SIZE);
		printf("backtrace() returned %d addresses\n", addr_num);

		/*The backtrace_symbols_fd return the symbol of function*/
		strings = backtrace_symbols(buffer, addr_num);
		if (strings == NULL)
		{
				perror("backtrace_symbols");
				exit(EXIT_FAILURE);
		}

		for (i = 0; i < addr_num; i++)
		{
				printf("%d:%s\n", i,strings[i]);
		}

		free(strings);
}

void dump(int nu)
{
	
	        printf("stack dump!\n");
        printf("##############\n");
	print_trace();
	
	printf("memory dump!\n");
	printf("##############\n");
	dumpmap();
}

void fun(void)
{
		int *p = NULL;
		*p = 9;
}

int main(void)
{
	signal(SIGSEGV,dump);
		fun();

		return 0;
}
