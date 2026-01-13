# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbylund <tbylund@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 13:49:59 by tbylund           #+#    #+#              #
#    Updated: 2025/11/23 15:48:35 by tbylund          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a
COM     = cc
FLAGS   = -Wall -Wextra -Werror

DIR     = .

SRC     = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
          ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
          ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
          ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
          ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
          ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
          ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
          ft_toupper.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
          ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		  ft_lstlast.c ft_lstmap.c ft_strcmp.c ft_append_str.c get_next_line.c \
		  get_next_line_utils.c ft_triple_join.c

OBJ     = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "Library $(NAME) created!"

bonus: $(OBJ) $(BONUS_OBJ)
	@ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
	@echo "Library $(NAME) with bonus created!"

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

update_makefile:
	@sed '20d' Makefile > Makefile.tmp
	@awk 'NR==19{print $$0 "\nSRC\t\t= $(SRC_ILL)"; next}1' Makefile.tmp > Makefile
	@rm Makefile.tmp

party:
	@curl parrot.live

.PHONY: all clean fclean re update_makefile party
