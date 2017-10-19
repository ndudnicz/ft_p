#include <unistd.h>
#include <fcntl.h>

int my_pipe(char *filename_pipe)
{
	int fd;

	if((fd = open(filename_pipe, O_RDWR | O_CREAT | O_TRUNC, 0600))==-1)
	{
		ADD ERROR HANDLING HERE
		return (1);
	}
	dup2(fd,STDOUT_FILENO);
	dup2(fd,STDERR_FILENO);
	close(fd);
	return (0);
}
