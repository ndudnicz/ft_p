#include <unistd.h>
#include <fcntl.h>

int		my_pipe(int fd1, int fd2)
{
	dup2(fd2, fd1 /*STDOUT_FILENO*/);
	// dup2(sock, /*STDERR_FILENO*/);
	return (0);
}
