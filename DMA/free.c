/* free example */
#include <stdlib.h>     /* malloc, calloc, realloc, free */

char* returnme(char* a) {
	if (a[0] == '0')
		return "hereree";
	char *final = (char*)malloc(5,sizeof(char));
	*final = "00000000";
	final[0] = '1';
	final[1] = '0';
	final[2] = '1';
	final[4] = '1';
	final[5] = '0';
	final[6] = '\0';
	return final;
}

int main()
{
	int * buffer1, *buffer2, *buffer3;
	buffer1 = (int*)malloc(100 * sizeof(int));
	buffer2 = (int*)calloc(100, sizeof(int));
	buffer3 = (int*)realloc(buffer2, 500 * sizeof(int));
	free(buffer1);
	free(buffer3);
	printf("%s\n", buffer2);

	char* a = returnme("001010");
	printf("%s",a);

	int i;
	scanf_s("%d", &i);
	return 0;
}