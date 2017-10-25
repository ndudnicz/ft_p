#ifndef SEND_MESSAGE_H
# define SEND_MESSAGE_H

# define INTERNAL_ERROR			"ERROR: INTERNAL ERROR"
# define CMD_CD_INVALID_PATH	"ERROR: COMMAND CD: INVALID PATH"
# define CMD_CD_SUCCESS			"SUCCESS: COMMAND CD"

int	send_message(t_config *config, char const *msg, char const *side);

#endif
