#include "config.h"
#include "packet.h"
#include "debug.h"

int		put(t_config *config, char const *filename, char const *remote_filename)
{
	t_packet	hello;

	forge_packet(&hello, (HEADER_SIZE << 16 | ASK_NEW_DATA_CONNECTION), "", 1);
	print_packet(&hello, 1);
}
