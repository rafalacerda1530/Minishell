# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 00:57:37 by coder             #+#    #+#              #
#    Updated: 2022/01/31 14:18:46 by fbonini          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_LIBFT = ./includes/42_libft/

PATH_SRC = src
PATH_OBJ = obj

ALLOC = allocs/
BUILTIN = builtin/
PARSE = parsers/
PIPE = pipe/
REDIR = redirect/

HEADERS = includes/minishell.h

FILE =	minishell.c ft_prompt.c ft_errors.c \
		ft_minishell_utils.c ft_frees.c \
		ft_execv.c ft_signals.c \
		$(ALLOC)ft_builts_in.c $(ALLOC)ft_env_utils.c \
		$(ALLOC)ft_env_variables.c $(ALLOC)ft_keys.c \
		$(ALLOC)ft_tolken.c $(ALLOC)ft_tolken_utils.c \
		$(BUILTIN)ft_echo.c $(BUILTIN)ft_pwd.c $(BUILTIN)ft_env.c \
		$(BUILTIN)ft_exit.c $(BUILTIN)ft_unset.c \
		$(BUILTIN)ft_export.c $(BUILTIN)ft_export_utils.c \
		$(BUILTIN)ft_cd.c $(BUILTIN)ft_cd_utils.c \
		$(PARSE)ft_parse.c $(PARSE)ft_parse_utils.c \
		$(PIPE)ft_std.c $(PIPE)ft_pipes.c \
		$(REDIR)ft_arrow_left.c $(REDIR)ft_arrow_right.c \
		$(REDIR)ft_d_arrow_left.c $(REDIR)ft_d_arrow_right.c \
		$(REDIR)ft_redir_strings.c $(REDIR)ft_redirects.c \
		$(REDIR)ft_redir_utils.c \

LIBFT = $(PATH_LIBFT)libft.a
CC = clang
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
LEAK = -fsanitize=address

SRC = $(addprefix $(PATH_SRC)/, $(FILE))
OBJ = $(SRC:$(PATH_SRC)/%.c=$(PATH_OBJ)/%.o)

NAME = minishell

all: make_libft $(NAME)

$(NAME): $(OBJ)
	@echo done!!
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LEAK) -lreadline -g -o $(NAME)

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c $(HEADERS)
	@mkdir -p $(PATH_OBJ)
	@mkdir -p $(PATH_OBJ)/$(ALLOC)
	@mkdir -p $(PATH_OBJ)/$(BUILTIN)
	@mkdir -p $(PATH_OBJ)/$(PARSE)
	@mkdir -p $(PATH_OBJ)/$(PIPE)
	@mkdir -p $(PATH_OBJ)/$(REDIR)
	$(CC) -g $(CFLAGS) -c -Iincludes -o $@ $<

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