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
	if (tmp)
		free(tmp);
	return (str);
}

static char	*process_buffer(char *str, char *buffer, t_shell *sh)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strchr(buffer, '$'))
	{
		tmp = her_env(sh, buffer);
		if (!tmp)
			tmp = ft_strdup(" ");
		str = heredoc_nstrex(str, tmp);
		free(tmp);
	}
	else
		str = heredoc_nstrex(str, buffer);
	return (str);
}

static char	*process_first_buffer(char *buffer, t_shell *sh)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strchr(buffer, '$'))
	{
		tmp = her_env(sh, buffer);
		if (tmp)
			return (tmp);
		else
			return (ft_strdup(" "));
	}
	else
		return (ft_strdup(buffer));
}

static char	*handle_bufferex(t_shell *sh, char *str, char *buffer, char *end)
{
	char	*new_str;

	new_str = NULL;
	if (str && ft_strcmp(buffer, end) != 0)
		new_str = process_buffer(str, buffer, sh);
	else if (ft_strcmp(buffer, end) != 0)
		new_str = process_first_buffer(buffer, sh);
	return (new_str);
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
		{
			write(1, "\n", 1);
			free(str);
			return (node->infd = -2);
		}
		if (ft_strcmp(buffer, delimeter) == 0)
		{
			free(buffer);
			return (heredocfdex(node, str));
		}
		str = handle_bufferex(sh, str, buffer, delimeter);
		free(buffer);
	}
	return (1);
}
