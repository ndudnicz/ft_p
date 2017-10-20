CLIENT = client

SERVEUR = serveur

CC = gcc

FLAGS = #-Werror -Wextra -Wall

SRC_CLIENT_DIR = srcclient

SRC_SERVEUR_DIR = srcserveur

OBJ_CLIENT_DIR = objclient

OBJ_SERVEUR_DIR = objserveur

PATH_CLIENT_INCLUDES = includes/includes_client

PATH_SERVEUR_INCLUDES = includes/includes_serveur

SRC_CLIENT = main.c error.c user_input.c establish_connection.c

SRC_SERVEUR = main.c

OBJ_CLIENT = $(SRC_CLIENT:%.c=objclient/%.o)

OBJ_SERVEUR = $(SRC_SERVEUR:%.c=objserveur/%.o)

all: lib obj $(CLIENT) $(SERVEUR)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) -o $@ $(OBJ_CLIENT) -L. -lft -lftasm

$(OBJ_CLIENT_DIR)/%.o: $(SRC_CLIENT_DIR)/%.c
	$(CC) $(FLAGS) -o $@ -c $< -I $(PATH_CLIENT_INCLUDES) -I libft/includes -I includes/ #-L. -lft -lftasm

$(SERVEUR): $(OBJ_SERVEUR)
	$(CC) -o $@ $(OBJ_SERVEUR) -L. -lft -lftasm

$(OBJ_SERVEUR_DIR)/%.o: $(SRC_SERVEUR_DIR)/%.c
	$(CC) $(FLAGS) -o $@ -c $< -I $(PATH_SERVEUR_INCLUDES) -I libft/includes -I includes/ #-L. -lft -lftasm

obj:
	mkdir -p $(OBJ_CLIENT_DIR) $(OBJ_SERVEUR_DIR)

lib:
	make -s -C libft
	ln -sf libft/libft.a libft.a
	ln -sf libft/libftasm/libfts.a libftasm.a

clean:
		make clean -s -C libft
		/bin/rm -rf $(OBJ_CLIENT) $(OBJ_SERVEUR)

fclean: clean
		make fclean -s -C libft
		/bin/rm -rf $(CLIENT) $(SERVEUR) libft.a libftasm.a

re: clean fclean all
