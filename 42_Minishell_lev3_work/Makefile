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
CFLAGS = -Wall -Werror -Wextra -g0
LIBFT = ./libft/libft.a
RM = rm -rf
# são variáveis de ambiente que estão sendo definidas na makefile para serem usadas no processo de compilação/linkagem do programa.

# A variável CPPFLAGS está definindo a opção -I que informa ao compilador que deve incluir o diretório /usr/local/opt/readline/include no caminho de busca dos cabeçalhos de arquivos de inclusão durante a compilação. Isso significa que se houver arquivos de inclusão necessários para compilar o programa localizados nesse diretório, o compilador será capaz de encontrá-los sem problemas.

# Já a variável LDFLAGS está definindo a opção -L que informa ao linker que deve incluir o diretório /usr/local/opt/readline/lib no caminho de busca das bibliotecas durante a linkagem. Isso significa que se houver bibliotecas necessárias para linkar o programa localizadas nesse diretório, o linker será capaz de encontrá-las sem problemas.

CPPFLAGS=-I/usr/local/opt/readline/include
LDFLAGS=-L/usr/local/opt/readline/lib

SRC = main.c prompt.c init.c signal.c utils.c echo.c builtins.c clear.c pwd.c cd.c exit.c envp.c mtr_util.c export.c unset.c env.c ft_token_utils.c aspas.c cmd_utils.c expander.c error.c input_copy.c parser.c path.c exec.c


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

.PHONY: all clean fclean re bonus

.SILENT:
