#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h> // Include this library to make management of Signals

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 300

void my_handler (int signum)
{
    if (signum == SIGUSR1)
    {
        printf("Recibido SIGUSR1!\n");
    }
}

void my_handler2 (int signum2)
{
    if (signum2 == SIGUSR2)
    {
        printf("Recibido SIGUSR2!\n");
    }
}


int main(void)
{
   
    char outputBuffer[BUFFER_SIZE];
    char outputBufferPrefix[BUFFER_SIZE]={"DATA: "};
    char outputBufferPrefix2[BUFFER_SIZE]={"SIGN:1"};
    char outputBufferPrefix3[BUFFER_SIZE]={"SIGN:2"};

	uint32_t bytesWrote;
	int32_t returnCode, fd;
    int32_t returnCode2, returnCode3; // Variable that storage management error from SIGUSR1 and SIGUSR2

    /* Create named fifo. -1 means already exists so no action if already exists */
    if ( (returnCode = mknod(FIFO_NAME, S_IFIFO | 0666, 0) ) < -1 )
    {
        printf("Error creating named fifo: %d\n", returnCode);
        exit(1);
    }

    /* Open named fifo. Blocks until other process opens it */
	printf("waiting for readers...\n");
	if ( (fd = open(FIFO_NAME, O_WRONLY) ) < 0 )
    {
        printf("Error opening named fifo file: %d\n", fd);
        exit(1);
    }
    
    /* open syscalls returned without error -> other process attached to named fifo */
	printf("got a reader--type some stuff\n");

    /* Loop forever */
	while (1)
	{
        /* Get some text from console */
		fgets(outputBuffer, BUFFER_SIZE, stdin);

        //This detects me when someone sends SIGUSR1 signal
        if (returnCode2 = signal(SIGUSR1, my_handler) < -1)
        {
            perror("Error");
        }
        else
        {
            printf("Valor returnCode2 = %d\n",returnCode2);
        }
        
        
        //This detects me when someone sends SIGUSR2 signal
                 
        if (returnCode3 = signal(SIGUSR2, my_handler2) < -1)
        {
            perror("Error");
        }

        //Put prefix "DATA:" in BUFFER_SIZE
        strcat(outputBufferPrefix,outputBuffer); 
        
        /* Write buffer to named fifo. Strlen - 1 to avoid sending \n char */
		if ((bytesWrote = write(fd, outputBufferPrefix, strlen(outputBufferPrefix)-1)) == -1)
        {
			perror("write");
        }
        else
        {
			printf("writer: wrote %d bytes\n", bytesWrote);
        }

        strcpy(outputBufferPrefix,"DATA: ");
        strcpy(outputBuffer," ");
	}
	return 0;
}
