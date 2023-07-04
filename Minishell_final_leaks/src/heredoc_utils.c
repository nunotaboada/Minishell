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

static char	*heredoc_nstrex(char *str, char *buffer)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(str, "\n");
	free(str);
	str = ft_strjoin(tmp, buffer);
	free(tmp); // adicinado devido aos leaks
	return (str);
}

static void	setup_signal_handlers(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static char	*process_buffer(char *str, char *buffer, t_shell *sh)
{
	char	*tmp;

	tmp = NULL;
	tmp = her_env(sh, buffer);
	if (ft_strchr(buffer, '$'))
		str = heredoc_nstrex(str, tmp);
	else
		str = heredoc_nstrex(str, buffer);
	return (str);
}

static char	*process_first_buffer(char *buffer, t_shell *sh)
{
	char	*tmp;

	tmp = NULL;
	tmp = her_env(sh, buffer);
	if (ft_strchr(buffer, '$'))
	{
		if (tmp)
			return (ft_strdup(tmp));
		else
			return (ft_strdup(" "));
	}
	else
		return (ft_strdup(buffer));
}

int	redheredocex(t_shell *sh, t_cmds *node, char *delimeter)
{
	char	*str;
	char	*buffer;

	str = NULL;
	buffer = NULL;
	while (1)
	{
		setup_signal_handlers();
		buffer = readline("> ");
		if (!buffer)
			return (node->infd = -2);
		if (str && ft_strcmp(buffer, delimeter) != 0)
			str = process_buffer(str, buffer, sh);
		else if (ft_strcmp(buffer, delimeter) != 0)
			str = process_first_buffer(buffer, sh);
		if (ft_strcmp(buffer, delimeter) == 0)
		{
			free(buffer);
			return (heredocfdex(node, str));
		}
		free(buffer);
	}
	return (1);
}
