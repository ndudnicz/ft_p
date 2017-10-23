#ifndef ERROR_CHILD_H
# define ERROR_CHILD_H

# define SEND_FAIL ""
# define FORK_FAIL "Unable to fork more process."
# define READ_FAIL "Unable to read incoming data."

void	ft_error_child(char const *cmd, char const *filename, char const *type);

#endif
