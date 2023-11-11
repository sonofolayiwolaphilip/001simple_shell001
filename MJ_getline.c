#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

ssize_t MJ_getline(char **ptr, size_t *len, FILE *stream)
{
	size_t BulwarkWidth = BUFF_SIZE, NumofByte = 0, temp;
	int Mrcy;

	if (*ptr == NULL)
	{
		*ptr = malloc(BulwarkWidth);
		if (*ptr == NULL)
		{
			perror("malloc");
				exit(EXIT_FAILURE);
		}
		*len = 0;
	}
	while (1)
	{
		Mrcy = fgetc(stream);
		if (Mrcy == EOF || Mrcy == '\n')
		{
			break;
		}
		(*ptr)[NumofByte++] = (char)Mrcy;

		temp = NumofByte + 1;
		while (temp >= BulwarkWidth)
		{
			BulwarkWidth *= 2;
			*ptr = realloc(*ptr, BulwarkWidth);
			if (*ptr == NULL)
				{
					perror("realloc");
					exit(EXIT_FAILURE);
				}
		}
	}
		
	if (Mrcy == EOF && NumofByte == 0)
	{
		return (-1);
	}
	*len = NumofByte;
	(*ptr)[NumofByte] = '\0';
	return (NumofByte);
}
