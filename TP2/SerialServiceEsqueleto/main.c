#include <stdio.h>
#include <stdlib.h>
#include "SerialManager.h"



int main(void)
{
	printf("Inicio Serial Service\r\n");

	while (1)
	{
		int a=0;

		if ((a = serial_open(0, 115200)) < 1)
		{
			perror("Error de conexión");	
		}
		else
		{
			printf("Conexión establecida");
			break;
		}
		

	}
	
	
	exit(EXIT_SUCCESS);
	return 0;
}

