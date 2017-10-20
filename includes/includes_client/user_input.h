#ifndef USER_INPUT_H
# define USER_INPUT_H

# define LS		0x01
# define CD		0x02
# define GET	0x04
# define PUT	0x08
# define PWD	0x10
# define LLS	0x20
# define LCD	0x40
# define LPWD	0x80

typedef struct	s_treated_input
{
	unsigned char	type;
}				t_treated_input;

int		loop(void);

#endif
