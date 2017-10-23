#ifndef DEBUG_H
# define DEBUG_H

#include "user_input.h"
void print_packet(t_packet *packet, int print_data);
void print_forged_packet(t_packet *packet, int print_data);
void print_command_type(t_packet *packet);
void print_input(t_input *input);

#endif
