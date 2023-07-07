/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 22:12:06 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/27 22:12:06 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

static int	heredocfd(t_cmds *node, char *str)
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

static char	*heredoc_nstr(char *str, char *buffer)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(str, "\n");
	free(str);
	str = ft_strjoin(tmp, buffer);
	free(tmp);
	return (str);
}

void	rmvaspashe(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] != c)
				str[j++] = str[i++];
			i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

int	redheredoc(t_cmds *node, char *delimeter)
{
	char	*buffer;
	char	*str;

	str = NULL;
	buffer = NULL;
	rmvaspashe(delimeter);
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		buffer = readline("> ");
		if (!buffer)
		{
			write(1, "\n", 1);
			free(str);
			return (node->infd = -2);
		}
		if (str && ft_strcmp(buffer, delimeter) != 0)
			str = heredoc_nstr(str, buffer);
		else if (ft_strcmp(buffer, delimeter) != 0)
			str = ft_strdup(buffer);
		if (ft_strcmp(buffer, delimeter) == 0)
		{
			free(buffer);
			return (heredocfd(node, str));
		}
		free(buffer);
	}
	return (1);
}

int	checkheredoc(t_shell *sh, t_cmds *node, char *delimeter)
{
	if (ft_strlen(delimeter) == 1)
	{
		if (delimeter[0] == '\"' || delimeter[0] == '\'')
		{
			write(1, "minishell: unexpected error heredoc \n", 38);
			return (1);
		}
	}
	if (countaspas(delimeter) > 0)
		return (redheredoc(node, delimeter));
	else
		return (redheredocex(sh, node, delimeter));
}
