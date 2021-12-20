# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 00:57:37 by coder             #+#    #+#              #
#    Updated: 2021/12/20 12:32:47 by fbonini          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_LIBFT = ./includes/42_libft/
PATH_SRC = ./src/
PATH_OBJ = ./obj/

FILE = $(PATH_SRC)minishell.c $(PATH_SRC)ft_prompt.c \
		$(PATH_SRC)ft_env_variables.c $(PATH_SRC)ft_env_utils.c \
		$(PATH_SRC)ft_tolken.c $(PATH_SRC)ft_tolken_utils.c \
		$(PATH_SRC)ft_echo.c $(PATH_SRC)ft_echo_utils.c \
		$(PATH_SRC)ft_minishell_utils.c \

LIBFT = $(PATH_LIBFT)libft.a
CC = clang
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
LEAK = -fsanitize=address

OBJ = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(FILE)) 

NAME = minishell

all: make_libft $(NAME)

$(NAME): $(OBJ)
	@echo done!!
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LEAK) -lreadline -g -o minishell

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJ)
	$(CC) $(CFLAGS) -g -I. -c $< -o $@

make_libft:
	@make -C $(PATH_LIBFT)

clean:
	@$(RM) $(PATH_OBJ)
	@make -C $(PATH_LIBFT) clean
	@echo obj removed!

fclean: clean
	@$(RM) $(NAME)
	@make -C $(PATH_LIBFT) clean fclean
	@echo clean everything

re: fclean all