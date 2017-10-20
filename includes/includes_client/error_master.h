#ifndef ERROR_H
# define ERROR_H

# define MALLOC_FAIL "memory allocation failed."
# define FSTAT_FAILED "fstat() failed."
# define MMAP_FAILED "mmap() failed."
# define CLOSE_FAILED "close() failed."
# define UNKNOW_ARG "Unknown command line argument."

int	ft_error(char const *exec_name, char const *filename,
				char const *type, int ret);

#endif
