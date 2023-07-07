/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:29:56 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/22 19:29:56 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_dir(const char *path)
{
	DIR		*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int	is_fork(t_shell *sh, t_cmds *cmd, int *fd)
{
	if (cmd->infd == -1 || cmd->outfd == -1)
		return (0);
	else if ((cmd->path && !access(cmd->path, X_OK) \
	&& !is_dir(cmd->path)) || checkbuiltins(cmd))
	{
		makefork(sh, cmd, fd);
		sh->fork = 1;
		sh->proc++;
	}
	else if (!cmd->path && ft_strchr(cmd->cmd_line[0], '/'))
		errorfork("minishell: ", cmd->cmd_line[0], \
		": No such file or directory\n", 127);
	else if (!cmd->path && !ft_strchr(cmd->cmd_line[0], '/'))
		errorfork("minishell: ", cmd->cmd_line[0], ": command not found\n", 127);
	else if (is_dir(cmd->path))
		errorfork("minishell: ", cmd->cmd_line[0], ": Is directory\n", 126);
	else if (access(cmd->path, X_OK) == -1)
		errorfork("minishell: ", cmd->cmd_line[0], ": Permission denied\n", 126);
	return (1);
}
