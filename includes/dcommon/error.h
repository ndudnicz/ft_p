#ifndef ERROR_H

# define ERROR_H
# define INTERNAL_ERROR "ERROR: INTERNAL ERROR"
# define CMD_CD_INVALID_PATH "ERROR: COMMAND CD: INVALID PATH"
# define INVALID_PATH "INVALID PATH"
# define CMD_CD_SUCCESS "SUCCESS: COMMAND CD"
# define CMD_LCD_SUCCESS "SUCCESS: COMMAND LCD"
# define SEND_FAIL ""
# define FORK_FAIL "Unable to fork more process."
# define READ_FAIL "Unable to read incoming data."
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
# define BAD_PACKET "Bad packet format: wrong magic number."
# define BAD_TYPE "Bad packet format: wrong type number."
# define GETCWD_FAILED "Unable to set root working directory."
# define CHDIR_FAILED "Invalid path."
# define BIND_FAILED "Invalid bind ip."
# define BAD_PORT "Invalid port number."
# define UNKNOWN_CMD "UNKNOWN COMMAND"


int		ft_error(char const *exec_name, char const *filename,
				char const *type, int ret);
void	ft_error_child(char const *cmd, char const *filename, char const *type);
int		error_handler_socket(t_config *config, char const *function, char const *msg);
int		error_handler_local(t_config *config, char const *function, char const *msg);

#endif
