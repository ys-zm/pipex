NAME = pipex
CC = gcc
C_FLAGS = -Wall -Werror -Wextra -g
F_SAN = -g -fsanitize=address

SRC_FILES = pipex.c \
		parsing.c \
		error_handling.c \
		children.c \
		check_access.c

ifdef WITH_BONUS
SRC_FILES = pipex_bonus.c \
			parsing_bonus.c \
			error_handling_bonus.c \
			children_bonus.c \
			process_bonus.c \
			init_bonus.c \
			check_access_bonus.c
endif

SRC_DIR = src

ifdef WITH_BONUS
SRC_DIR = bonus
endif

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INCLUDES = -Iinclude -Ilibft/include
LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT):
	@cd libft && make

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(C_FLAGS) $^ $(INCLUDES) -o $@
	@echo pipex made!

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@ 

bonus: fclean
	@$(MAKE) WITH_BONUS=1 all

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

mem:
	memdetect/memdetect.sh . $(GCC_FLAGS) $(LIBFT) $(INCLUDES) --exclude test.c try_outs.c bonus -a "infile cat \"wc -l\" outfile"
run: all
	./pipex infile "cat" "ls -la" outfile

.PHONY: all re clean fclean bonus rere 