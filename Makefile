NAME = pipex
CC = gcc
C_FLAGS = -Wall -Werror -Wextra
F_SAN = -g -fsanitize=address

SRC_FILES = pipex.c \
		env_parsing.c

SRC_DIR = src
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, SRC_FILES:.c=.o)

INCLUDES = -Iinclude -Ilibft/include
LIBFT = libft.a

all: $(NAME)

$(LIBFT):
	@cd libft && make

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@
	@pipex made!

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) $@ $^ 

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C libft clean
	@echo "cleaned!"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
	@echo "fcleaned!"

re: fclean all

.PHONY: all re clean fclean