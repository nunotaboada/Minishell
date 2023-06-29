/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 22:26:29 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/27 22:26:29 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

static char *ft_joinstr(char *rest, char *env)
{
	char	*result;

	result = NULL;
	// printf("env dentro do ft_join: %s\n", env);
	// printf("rest dentro do ft_join: %s\n", rest);
	if (rest && env)
		result = ft_strjoin(rest, env);
	else if (rest)
		result = ft_strdup(rest);
	else if (env)
		result = ft_strdup(env);
	// printf("result dentro do ft_join: %s\n", result);
	if (!result)
		return (NULL);
	else
		return (result);
}

static void	*getenvher(t_shell *sh, char *str)
{
	int 	i;
	int start;
	char *rest;
	char *var;
	char *env;
	char *result;

	i = 0;
	rest = NULL;
	var = NULL;
	env = NULL;
	result = NULL;
	start = i;
	while (str[(i)])
	{
		while (str[(i)] != '$' && str[(i)] != '\0' && str[(i)] != ' ')
			(i)++;
		if ((i) > start)
			rest = ft_substr(str, start, (i) - start);
		if (str[i] == '$')
		{
			start = i + 1;
			i = end_varpos(str, i + 1);
			var = ft_substr(str, start, (i) - start);
			env = get_env(var, sh);
		}
		if (result)
			
		result = ft_joinstr(rest, env);
	}
	// printf("result dentro do get: %s\n", result);
	if (result)
		return (result);
	return (NULL);
}

char *her_env(t_shell *sh, char *str)
{
	char *tmp;

	tmp = NULL;
	if(!str)
		return (NULL);
	if (ft_strchr(str, '$'))
	{
		tmp = ft_strdup(str);
		// printf("len do temp no expand %ld\n", ft_strlen(tmp));
		free(str);
		str = getenvher(sh, tmp);
		free(tmp);
	}
	// printf("str dentro do her: %s\n", str);
	return (str);
}

static int	heredocfdex(t_cmds *node, char *str)
{
	char	*tmp;
	int		fd[2];

	tmp = NULL;
	if (node->infd != STDIN_FILENO && node->infd != -2 && node->infd != -1)
		close(node->infd);
	if (pipe(fd) == -1)
		return (g_ex_status = 1);
	if (str)
	{
		tmp = ft_strjoin(str, "\n");
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
		write(fd[1], str, ft_strlen(str));
		free(str);
		close(fd[1]);
		node->infd = fd[0];
	}
	else
	{
		write(fd[1], "\n", 2);
		close(fd[1]);
		node->infd = fd[0];
		// node->infd = -2;
	}
	return (0);
}

static char	*heredoc_nstrex(char *str, char *buffer)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(str, "\n");
	free(str);
	str = ft_strjoin(tmp, buffer);
	// free(tmp);
	return (str);
}

int	redheredocex(t_shell *sh, t_cmds *node, char *delimeter)
{
	char		*buffer;
	char		*str;
	char *		tmp;

	g_ex_status = 0;
	str = NULL;
	buffer = NULL;
	tmp = NULL;
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		buffer = readline("> ");
		if (!buffer)
			return (node->infd = -2);
		if (str && ft_strcmp(buffer, delimeter) != 0)
		{
			tmp = her_env(sh, buffer);
			str = heredoc_nstrex(str, tmp);
		}
		else if (ft_strcmp(buffer, delimeter) != 0)
		{
			tmp = her_env(sh, buffer);
			// printf("buffer: %s\n", buffer);
			if (tmp)
				str = ft_strdup(tmp);
			else
				str = NULL;
			printf("str: %s\n", str);
		}
		if (ft_strcmp(buffer, delimeter) == 0)
		{
			free(buffer);
			return (heredocfdex(node, str));
		}
		free(buffer);
	}
	return (1);
}
