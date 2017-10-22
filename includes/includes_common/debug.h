#ifndef DEBUG_H
# define DEBUG_H

void print_packet(t_packet *packet, int print_data);
void print_forged_packet(t_packet *packet, int print_data);
void print_command_type(t_packet *packet);

#endif
