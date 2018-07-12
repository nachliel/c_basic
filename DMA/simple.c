/* malloc example: random string generator*/
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */

int cmain()
{
	int i, n;
	char * buffer;

	printf("How long do you want the string? ");
	scanf_s("%d", &i);

	buffer = (char*)malloc(i);
	if (buffer == NULL) exit(1);
	
	for (n = 0; n<i; n++)
		buffer[n] = rand() % 26 + 'a';
	buffer[i] = '\0';
	printf("Random string: %s\n", buffer);

	printf("Whould you wish to longer the string? by: ");
	int j;
	scanf_s("%d", &j);
	buffer = (char*)realloc(buffer, (i+j+1) * sizeof(int));
	buffer[i+j] = '\0';
	for (n; n<i+j; n++)
		buffer[n] = rand() % 26 + 'a';
	
	printf("Random string: %s\n", buffer);
	free(buffer);
	scanf_s("%d", &i);
	return 0;
}