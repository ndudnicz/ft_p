#ifndef USER_INPUT_H
# define USER_INPUT_H

typedef struct		s_input
{
	unsigned short	cmd;
	char			*arg;
}					t_input;

int		user_input_loop(t_config *config);
void	fork_and_run(t_config *config, t_input *input);

#endif
