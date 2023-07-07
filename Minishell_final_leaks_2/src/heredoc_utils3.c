/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:54:15 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/01 14:54:15 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

static char	*handle_exit_status_var(int *i)
{
	char	*env;

	env = ft_itoa(g_ex_status);
	(*i) += 2;
	return (env);
}

static int	end_varpos_her(char *s, int pos)
{
	while (s[pos] != '\0')
	{
		if (s[pos] == '$' || s[pos] == 34 || s[pos] == 39
			|| s[pos] == ' ' || s[pos - 1] == '?')
			return (pos);
		pos++;
	}
	return (pos);
}

char	*dorexpher(int *i, char *str, t_shell *sh)
{
	int		start;
	char	*var;
	char	*env;

	start = 0;
	env = NULL;
	var = NULL;
	if (str[*i] == '$' && (str[*i + 1] == '\'' || str[*i + 1] == '$' \
	|| str[*i + 1] == ' ' || str[*i + 1] == '\0' || str[*i + 1] == '\"'))
	{
		env = ft_strdup("$");
		(*i)++;
	}
	else if (str[*i] == '$' && str[*i + 1] == '?')
		env = handle_exit_status_var(i);
	else if (str[*i] == '$')
	{
		start = *i + 1;
		*i = end_varpos_her(str, *i + 1);
		var = ft_substr(str, start, (*i) - start);
		env = get_env(var, sh);
		free(var);
	}
	return (env);
}

void	handle_default(t_cmds *node, int fd[2])
{
	write(fd[1], "\n", 2);
	close(fd[1]);
	node->infd = fd[0];
}

int	heredocfdex(t_cmds *node, char *str)
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
		handle_default(node, fd);
	return (0);
}
