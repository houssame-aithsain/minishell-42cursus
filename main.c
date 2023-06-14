#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd = open ("file2", O_RDWR | O_TRUNC, 0644);
	if (fd != -1)
		printf("SUCCESS\n");
}