#ifndef ERROR_H
# define ERROR_H

# define MALLOC_FAIL "memory allocation failed."
# define FSTAT_FAILED "fstat() failed."
# define MMAP_FAILED "mmap() failed."
# define CLOSE_FAILED "close() failed."
# define UNKNOW_ARG "Unknown command line argument."
# define CONNECT_ERROR "connect() error."
# define BIND_ERROR "bind() error."
# define GETPROTOBYNAME_FAIL "getprotobyname() failed."
# define INET_ADDR_FAILED "inet_addr(), malformed requests."
# define SOCKET_FAILED "socket() failed."
# define CANT_ESTABLISH_CONNECTION "Unable to reach the client."

int	ft_error(char const *exec_name, char const *filename,
				char const *type, int ret);

#endif
