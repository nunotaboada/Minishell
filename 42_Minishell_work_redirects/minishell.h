/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:12:18 by nsoares-          #+#    #+#             */
/*   Updated: 2023/05/17 15:30:38 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <dirent.h> // para o dir na função isdir
#include <sys/wait.h>

extern int g_ex_status;

typedef struct s_token
{
	char			*word;
	char			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmds
{
	char **cmd_line;
	char *new_dir;
	char *path;
	char *oldpwd;
	char *pwd;
	int infd;
	int outfd;
	int fork; //flag que diz se o nó foi feito fork
	char	*var;
	char	*value;
	int	index; // index de cada cmd - processo a criar
	int	total; // total de processo a criar
	struct s_cmds *next;
	struct s_cmds *prev;
}				t_cmds;

typedef struct s_shell
{
	t_cmds *cmds;
	t_token *head_token;
    char *cmd_line;
	int		i; // posição na string
	int		wd_lim; // posição na string
	int		dquotes; // double quotes
	int		squotes; // single quotes
	int		pipeOp;// nº of pipes
	int		proc;// nº de processos criados
	char		**envp;
	pid_t		pid;
}	t_shell;

// main
void init(int ac, char **av, char **envp, t_shell *shell);
char *show_prompt();
void signals();
int operators(t_shell *sh);

// Builtins
int builtins(t_cmds *cmds, t_shell *shell);
int checkBuiltins(t_cmds *cmd);
int built_echo(t_cmds *cmds);
int built_pwd();
int built_cd(t_cmds *cmds, t_shell *shell);
int built_exit(t_cmds *cmds);
int built_env(t_shell *shell);
int built_export(t_shell *shell ,t_cmds *cmds);
int built_unset(t_cmds *cmds, t_shell *shell);
void clear_screen();

// Env
int put_var_env(char *var, char *value, t_shell *shell);
int pos_envp(char *var, char **envp);
void remv_var_env(char *var, t_shell *shell);
char *get_env(char *var, char **envp);

// Utils
int nb_of_args(t_cmds *cmds);
int	pos_char(char *str, char c);
int args_numbers(char *str);

// Utils Env
char **mtr_dup(char **matriz);
int mtr_len(char **matriz);
void mtr_free(char **matriz);
char **mtr_addnew(char *str, char **matrizold);
char **mtr_rmv(int pos, char **matrizold);

// Utils list - token
void node_type(t_shell *sh, char c);
void	print_list(t_shell *sh);
void	*node(t_shell *sh, char *word);
void	free_listtoken(t_token *list);
void token_node(t_shell *sh, char c);

// Utils cmds
void	free_listcmds(t_cmds *list);

/*lexer*/
int words(t_shell *sh);
int div_input(t_shell *sh);
void spaces(t_shell *sh);
void lexer_op(t_shell *sh);
int is_operator(char c); //main
int countAspas(char *str);
void	wordOutAspas(t_token *node);
int rmvAspas(t_shell *sh);
int checkdAspas(t_shell *sh);
bool verificarAspas(t_shell *sh);

// Errors
int error_quotes(char erro);
void errorFork (char *str1, char *str2, char *str3, int code);
void errorMinishell (char *str1, char *str2, char *str3);

/*free*/
void	free_all(t_shell *sh);

/*expander*/
int expand(t_shell *sh);
char *new_word(t_shell *sh, char *temp);
char *allWord(t_shell *sh, char *temp);
char *concate(char *new_str, char *rest);
char *restexp(t_shell *sh, char *temp);
char *doExp(t_shell *sh, char *temp);
char *allWord(t_shell *sh, char *temp);

/*parser*/
void	*node_cmds(t_cmds **node);
void initNodeCmds(t_cmds *node);
int checkOperators(t_shell *sh, t_token *token, t_cmds *node);
void createNewCmd(t_cmds *node, char *str);
int parser(t_shell *sh);
void	free_listcmd(t_cmds *list);
void	print_cmds(t_shell *sh);
void fill_index(t_shell *sh);

/*path*/
char *search_path(t_shell *shell, t_cmds *cmds);
char **get_paths(t_shell *shell);
char *find_executable(char **paths, const char *command);

/*exec*/
int is_dir(const char *path);
int execCmd (t_shell *sh);
int is_fork(t_shell *sh, t_cmds *cmd, int *fd);
void makeFork(t_shell *sh, t_cmds *cmd, int *fd);

/*redirects*/
char *dirPath(t_shell *sh);
char *fullPath(char *path, t_token *token);
int	parse_redirecs(t_shell *sh, t_cmds *node, t_token *token);
int	fileIn(char *allPath, t_cmds *node, t_token *token);
int openFileRedirIn(char *path, t_cmds *node, t_token *token);
int redIn (t_shell *sh, t_cmds *node, t_token *token);
int fileOut(char *allPath, t_cmds *node, t_token *token);
int openFileRedirOut(char *path, t_cmds *node, t_token *token);
int redOut (t_shell *sh, t_cmds *node, t_token *token);

#endif
