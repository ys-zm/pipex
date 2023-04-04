NAME = pipex
CC = gcc
C_FLAGS = -Wall -Werror -Wextra
F_SAN = -g -fsanitize=address

ifdef BONUS
SRC_FILES = pipex_bonus.c \
			env_parsing_bonus.c \
			error_handling_bonus.c \
			children_bonus.c \
			process_bonus.c 
else
SRC_FILES = pipex.c \
		env_parsing.c \
		command_parsing.c \
		error_handling.c \
		children.c
endif

ifdef BONUS
SRC_DIR = bonus
elseif
SRC_DIR = src
endif

OBJ_DIR = obj

ifdef BONUS
OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS_FILES:.c=.o))
elseif
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
endif

INCLUDES = -Iinclude -Ilibft/include
LIBFT = libft/libft.a

all: $(NAME)

bonus: $(NAME) BONUS=1 all

$(LIBFT):
	@cd libft && make

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(C_FLAGS) $(F_SAN) $^ $(INCLUDES) -o $@
	@echo pipex made!

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
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