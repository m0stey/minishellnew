# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/25 10:35:46 by alegeber          #+#    #+#              #
#    Updated: 2025/11/25 10:35:46 by alegeber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

# Compiler & Flags
CC          = cc
# -I include: For minishell.h
# -I libft:   For libft.h (if needed directly)
CFLAGS      = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -g3

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
LIBFT_DIR   = libft

# Libraries
LIBFT       = $(LIBFT_DIR)/libft.a
# Link libft and readline
LIBS        = -L$(LIBFT_DIR) -lft -lreadline

# SOURCE FILES

# 1. Main Entry Point
SRCS_MAIN   = $(SRC_DIR)/main.c

# 2. Parsing Module
# Matches all .c files in src/parsing/* subdirectories
SRCS_PARSE  = $(wildcard $(SRC_DIR)/parsing/lexer/*.c) \
              $(wildcard $(SRC_DIR)/parsing/expander/*.c) \
              $(wildcard $(SRC_DIR)/parsing/parser/*.c) \
              $(wildcard $(SRC_DIR)/parsing/heredoc/*.c) \
              $(wildcard $(SRC_DIR)/parsing/env_pars/*.c) \
              $(wildcard $(SRC_DIR)/parsing/signals/*.c)

# 3. Execution Module
# Matches all .c files in src/execution/* subdirectories
SRCS_EXEC   = $(wildcard $(SRC_DIR)/execution/builtins/*.c) \
              $(wildcard $(SRC_DIR)/execution/env/*.c) \
              $(wildcard $(SRC_DIR)/execution/executor/*.c)

# Combine all sources
SRCS        = $(SRCS_MAIN) $(SRCS_PARSE) $(SRCS_EXEC)

# Create object file paths (e.g., src/parser/file.c -> obj/parser/file.o)
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# RULES

all: $(LIBFT) $(NAME)

# Link the executable
$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "Minishell compiled successfully! ✨"

# Compile objects
# mkdir -p $(dir $@) creates the necessary subdirectories in obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile Libft
$(LIBFT):
	@echo "Compiling Libft..."
	@make -C $(LIBFT_DIR)

# Clean objects
clean:
	@echo "Cleaning objects..."
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

# Full clean
fclean: clean
	@echo "Cleaning executables..."
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re
