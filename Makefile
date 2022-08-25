NAME = program

SERVER = server

CLIENT = client

CC = gcc

LIBFT = ./ft_printf/libftprintf.a

CFLAGS = -Wall -Werror -Wextra

all: $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER):
	@echo "\x1b[32mcreating server...\x1b[0m"
	@make bonus -C ./ft_printf
	@$(CC) $(CFLAGS) server.c $(LIBFT) -o $(SERVER)
	@echo "\x1b[35mserver created.\x1b[0m"

$(CLIENT):
	@echo "\x1b[32mcreating client...\x1b[0m"
	@make bonus -C ./ft_printf
	@$(CC) $(CFLAGS) client.c $(LIBFT) -o $(CLIENT)
	@echo "\x1b[35mclient created.\x1b[0m"

clean:
	@make fclean -C ./ft_printf

fclean: clean
	@rm -rf $(SERVER)
	@echo "\x1b[31mserver removed.\x1b[0m"
	@rm -rf $(CLIENT)
	@echo "\x1b[31mclient removed.\x1b[0m"

re: fclean all

.PHONY: all flean clean re