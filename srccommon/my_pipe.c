#include <unistd.h>
#include <fcntl.h>

int my_pipe(int sock)
{
	// int fd;

	// if((fd = open(filename_pipe, O_RDWR | O_CREAT | O_TRUNC, 0600))==-1)
	// {
	// 	ADD ERROR HANDLING HERE
	// 	return (1);
	// }
	dup2(sock, STDOUT_FILENO);
	dup2(sock, STDERR_FILENO);
	return (0);
}
