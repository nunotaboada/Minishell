/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:12:18 by nsoares-          #+#    #+#             */
/*   Updated: 2023/07/11 18:18:01 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int	g_ex_status;

typedef struct s_datamini
{
	int			i;
	int			start;
	char		*rest;
	char		*env;
	char		*conc;
}	t_datamini;

typedef struct s_token
{
	char			*word;
	char			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmds
{
	char			**cmd_line;
	char			*new_dir;
	char			*path;
	char			*oldpwd;
	char			*pwd;
	int				infd;
	int				outfd;
	char			*var;
	char			*value;
	int				index;
	int				total;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_shell
{
	t_cmds			*cmds;
	t_token			*head_token;
	char			*cmd_line;
	int				i;
	int				wd_lim;
	int				dquotes;
	int				squotes;
	int				pipeop;
	int				proc;
	int				fork;
	char			**envp;
	pid_t			pid;
}	t_shell;

/*main*/
void	init(int ac, char **av, char **envp, t_shell *shell);
char	*show_prompt(t_shell *sh);
void	signals(void);
void	signal_handler(int sig);
int		operators(t_shell *sh);

/*Builtins*/
int		builtins(t_cmds *cmds, t_shell *shell);
int		checkbuiltins(t_cmds *cmd);
int		built_echo(t_cmds *cmds);
int		built_pwd(void);
int		built_cd(t_cmds *cmds, t_shell *shell);
int		built_exit(t_cmds *cmds);
int		built_env(t_shell *shell);
int		built_export(t_shell *shell, t_cmds *cmds);
int		built_unset(t_cmds *cmds, t_shell *shell);
void	clear_screen(void);

/*Env*/
int		put_var_env(char *var, char *value, t_shell *shell);
int		pos_envp(char *var, char **envp);
void	remv_var_env(char *var, t_shell *shell);
char	*get_env(char *var, t_shell *sh);

/*Utils*/
int		nb_of_args(t_cmds *cmds);
int		pos_char(char *str, char c);
int		args_numbers(char *str);
void	put_var_env_from_cmd(char *cmd, t_shell *shell);

/*Utils Env*/
char	**mtr_dup(char **matriz);
int		mtr_len(char **matriz);
void	mtr_free(char **matriz);
char	**mtr_addnew(char *str, char **matrizold);
char	**mtr_rmv(int pos, char **matrizold);

/*Utils list - token*/
void	node_type(t_shell *sh, char c);
void	print_list(t_shell *sh);
void	*node(t_shell *sh, char *word);
void	free_listtoken(t_token *list);
void	token_node(t_shell *sh, char c);

/*Utils cmds*/
void	free_listcmds(t_cmds *list);

/*lexer*/
int		words(t_shell *sh);
int		div_input(t_shell *sh);
void	spaces(t_shell *sh);
void	lexer_op(t_shell *sh);
int		is_operator(char c);
int		countaspas(char *str);
void	wordoutaspas(t_token *node);
int		rmvaspas(t_shell *sh);
int		checkdaspas(t_shell *sh);
int		checkaspas2(t_shell *sh);
bool	verificaraspas(t_shell *sh);

/*Errors*/
int		error_quotes(char erro);
void	errorfork(char *str1, char *str2, char *str3, int code);
void	errorminishell(char *str1, char *str2, char *str3);

/*free*/
void	free_all(t_shell *sh);

/*expander*/
int		expand(t_shell *sh);
char	*new_word(t_shell *sh, char *temp);
char	*allword(t_shell *sh, char *temp);
char	*concate(char *new_str, char *rest);
char	*restexp(t_shell *sh, char *temp);
char	*doexp(t_shell *sh, char *temp);
char	*allword(t_shell *sh, char *temp);
int		end_varpos(char *s, int pos);
char	*checkenv(char *str, t_shell *sh);
void	initcicle(char *str, t_datamini *data);
void	initdatamini(t_datamini *data);
char	*get_rest(const char *str, int start, int end);
char	*process_env_variable(char *str, t_datamini *data, t_shell *sh);
char	*ft_result(char *str, char *env);

/*parser*/
void	*node_cmds(t_cmds **node);
void	initnodecmds(t_cmds *node);
int		checkoperators(t_shell *sh, t_token *token, t_cmds *node);
void	createnewcmd(t_cmds *node, char *str);
int		parser(t_shell *sh);
void	free_listcmd(t_cmds *list);
void	print_cmds(t_shell *sh);
void	fill_index(t_shell *sh);

/*path*/
char	*search_path(t_shell *shell, t_cmds *cmds);
char	**get_paths(t_shell *shell);
char	*find_executable(char **paths, const char *command);

/*exec*/
int		is_dir(const char *path);
int		execcmd(t_shell *sh);
int		is_fork(t_shell *sh, t_cmds *cmd, int *fd);
void	makefork(t_shell *sh, t_cmds *cmd, int *fd);
void	ft_wait(t_shell *sh);
void	parentprocess(t_cmds *cmd, int *fd);
void	childprocess(t_cmds *cmd, int *fd);

/*redirects*/
char	*dirpath(t_shell *sh);
char	*fullpath(char *path, t_token *token);
int		parse_redirecs(t_shell *sh, t_cmds *node, t_token *token);
int		redheredoc(t_cmds *node, char *delimeter);
int		checkheredoc(t_shell *sh, t_cmds *node, char *delimeter);
void	rmvaspashe(char *str);
int		redheredocex(t_shell *sh, t_cmds *node, char *delimeter);
char	*her_env(t_shell *sh, char *str);
char	*dorexpher(int *i, char *str, t_shell *sh);
int		filein(t_cmds *node, t_token *token);
int		fileout(t_cmds *node, t_token *token);
void	handle_default(t_cmds *node, int fd[2]);
int		heredocfdex(t_cmds *node, char *str);
void	setup_signal_handlers(void);
void	signal_quit(int sig);
void	signal_quit1(int sig);

#endif
