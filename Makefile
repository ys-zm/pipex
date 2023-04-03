NAME = pipex
CC = gcc
C_FLAGS = -Wall -Werror -Wextra
F_SAN = -g -fsanitize=address

SRC_FILES = pipex.c \
		env_parsing.c \
		command_parsing.c \
		error_handling.c \
		children.c

BONUS_DIR = bonus
SRC_DIR = src
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INCLUDES = -Iinclude -Ilibft/include
LIBFT = libft/libft.a

all: $(NAME)

bonus: b_obj | $(NAME)

$(LIBFT):
	@cd libft && make

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(C_FLAGS) $^ $(INCLUDES) -o $@
	@echo pipex made!

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

b_obj:
	$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@ 
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@ 

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C libft clean
	@echo "cleaned!"

fclean: clean
	@rm -rf $(NAME)
	@echo "fcleaned!"

depclean:
	@rm -rf $(LIBFT)
	@echo "cleaned dependencies"

re: fclean all

rere: fclean depclean all

.PHONY: all re clean fclean