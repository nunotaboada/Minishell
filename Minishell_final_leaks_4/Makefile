# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 17:52:53 by nsoares-          #+#    #+#              #
#    Updated: 2023/05/10 21:00:38 by nsoares-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LIBFT = ./libft/libft.a
RM = rm -rf

CPPFLAGS = -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib

SRC = main.c prompt.c init.c signal.c utils.c echo.c builtins.c pwd.c cd.c exit.c envp.c mtr_util.c export.c unset.c env.c ft_token_utils.c aspas.c cmd_utils.c expander.c expander_utils.c expander_utils1.c expander_utils2.c expander_utils3.c expander_utils4.c error.c input.c input_utils.c parser.c parser_utils.c path.c exec.c exec_utils.c free.c redirect_in.c redirect_out.c redirects_utils.c heredoc.c heredoc_utils.c heredoc_utils2.c heredoc_utils3.c heredoc_utils4.c operators.c aspas1.c aspas2.c


# OBJS_FILES = $(SRC:.c=.o)

# __________COLORS____________

BOLD_PURPLE	=	\033[1;35m
BOLD_CYAN	=	\033[1;36m
BOLD_YELLOW	=	\033[1;33m
NO_COLOR	=	\033[0m

# _________MESSAGE_____________

COMPILATION_START	=	echo "\n$(BOLD_YELLOW)Make: $(NO_COLOR)Compilation start...\n"

MINISHELL_READY  =   echo "\n$(BOLD_YELLOW)minishell $(NO_COLOR)ready! ✅ \n"

CLEANED		=	echo "\n$(BOLD_YELLOW)Clean: $(NO_COLOR)Removed all the \".o\" files \n"

FCLEANED	=	echo "\n$(BOLD_YELLOW)Fclean: $(NO_COLOR)Removed the executables \n"

RE          =   echo "\n$(BOLD_YELLOW)Re: $(NO_COLOR)Compilation restarted \n"

OBJ_DIR = obj

OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: compilation_start $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	$(MAKE) --no-print-directory -C ./libft
	$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -o $(NAME) -lreadline
	@ $(MINISHELL_READY)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/utils/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/builtins/%.c
	$(CC) $(CFLAGS) -c $< -o $@

compilation_start:
	@ $(COMPILATION_START)

clean:
	@ $(RM) $(OBJS) -r $(OBJ_DIR)
	@ cd libft && make clean
	@ $(CLEANED)
	
fclean: clean
	@ $(RM) $(NAME)
	@ cd libft && make fclean
	@ $(FCLEANED)
		
re:	fclean all
	@ $(RE)

# noleaks: re
# 	valgrind ./minishell

# noleaksfull: re
# 	valgrind --leak-check=full --show-leak-kinds=all -s ./minishell

# noleakslog: re
# 	valgrind --leak-check=full --show-leak-kinds=all --error-limit=no --gen-suppressions=all --log-file=output.log ./minishell

rerun: re
	./minishell

exec:
	./minishell

.PHONY: all clean fclean re bonus exec rerun

.SILENT:
