CLIENT = client
SERVEUR = serveur
LIBCOMMON = libcommon.a
CC = gcc
FLAGS = #-Werror -Wextra -Wall

# SOURCE FOLDERS ==============================================================#

SRC_CLIENT_DIR = srcclient
SRC_SERVEUR_DIR = srcserveur
SRC_COMMON_DIR = srccommon

# OBJECTS FOLDERS =============================================================#

OBJ_CLIENT_DIR = objclient
OBJ_SERVEUR_DIR = objserveur
OBJ_COMMON_DIR = objcommon

# INCLUDES FOLDERS ============================================================#

PATH_CLIENT_INCLUDES = includes/includes_client
PATH_SERVEUR_INCLUDES = includes/includes_serveur
PATH_COMMON_INCLUDES = includes/includes_common

# SOURCES LIST ================================================================#

SRC_COMMON = debug.c packet.c my_pipe.c error_master.c options_handling.c \
			error_child.c config.c

SRC_CLIENT = main.c user_input.c receive_packet.c \
			establish_connection.c send_packet.c

SRC_SERVEUR = main.c switch_packet_type.c open_connection.c waiting_loop.c

# OBJECTS LIST ================================================================#

OBJ_CLIENT = $(SRC_CLIENT:%.c=objclient/%.o)
OBJ_SERVEUR = $(SRC_SERVEUR:%.c=objserveur/%.o)
OBJ_COMMON = $(SRC_COMMON:%.c=objcommon/%.o)

# GENERIC RULES ===============================================================#

all: $(CLIENT) $(SERVEUR)

clean:
		make clean -C libft
		/bin/rm -rf $(OBJ_CLIENT) $(OBJ_SERVEUR) $(OBJ_COMMON)

fclean: clean
		make fclean -C libft
		/bin/rm -rf $(CLIENT) $(SERVEUR) libft.a libftasm.a $(LIBCOMMON)

re: clean fclean all

# CLIENT RULES ================================================================#

$(CLIENT): $(LIBCOMMON) $(OBJ_CLIENT)
	make -sC libft
	$(CC) -o $@ $(OBJ_CLIENT) -L. -lft -lcommon -lftasm

$(OBJ_CLIENT_DIR)/%.o: $(SRC_CLIENT_DIR)/%.c
	$(CC) $(FLAGS) -o $@ -c $< -I $(PATH_CLIENT_INCLUDES) -I $(PATH_COMMON_INCLUDES) -I libft/includes -I includes/

# SERVEUR RULES ===============================================================#

$(SERVEUR): $(LIBCOMMON) $(OBJ_SERVEUR)
	make -sC libft
	$(CC) -o $@ $(OBJ_SERVEUR) -L. -lft -lcommon -lftasm

$(OBJ_SERVEUR_DIR)/%.o: $(SRC_SERVEUR_DIR)/%.c
	$(CC) $(FLAGS) -o $@ -c $< -I $(PATH_SERVEUR_INCLUDES) -I $(PATH_COMMON_INCLUDES) -I libft/includes -I includes/

# LIBCOMMON RULES =============================================================#

$(LIBCOMMON): $(OBJ_COMMON)
	make -sC libft
	ar rc $(LIBCOMMON) $(OBJ_COMMON)

$(OBJ_COMMON_DIR)/%.o: $(SRC_COMMON_DIR)/%.c
	make -sC libft
	$(CC) $(FLAGS) -o $@ -c $< -I $(PATH_COMMON_INCLUDES) -I libft/includes -I includes/
