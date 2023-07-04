/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:07:46 by nsoares-          #+#    #+#             */
/*   Updated: 2023/06/27 21:18:32 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	cd_back(t_shell *shell, t_cmds *cmds)
{
	char	*tmp;

	tmp = get_env("OLDPWD", shell);
	if (tmp == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (g_ex_status = 1);
	}
	cmds->oldpwd = getcwd(NULL, 0);
	if (chdir(tmp) != 0)
	{
		printf("minishell: cd: ");
		printf("%s", get_env("OLDPWD", shell));
		printf(": No such file or directory\n");
		return (g_ex_status = 1);
	}
	cmds->pwd = getcwd(NULL, 0);
	put_var_env("PWD", cmds->pwd, shell);
	put_var_env("OLDPWD", cmds->oldpwd, shell);
	printf("%s\n", cmds->pwd);
	return (g_ex_status = 0);
}

static	int	get_cd_home(t_shell *shell, t_cmds *cmds)
{
	char	*go_home;

	go_home = get_env("HOME", shell);
	if (!go_home)
	{
		printf("minishell: cd: HOME not set\n");
		return (g_ex_status = 1);
	}
	cmds->oldpwd = getcwd(NULL, 0);
	chdir(go_home);
	put_var_env("OLDPWD", cmds->oldpwd, shell);
	return (g_ex_status = 0);
}

int	built_cd(t_cmds *cmds, t_shell *shell)
{
	if (!cmds->cmd_line[1] || ft_strcmp(cmds->cmd_line[1], "~") == 0)
		return (get_cd_home(shell, cmds));
	if ((nb_of_args(cmds) == 2) && (ft_strcmp(cmds->cmd_line[1], "-") == 0))
		return (cd_back(shell, cmds));
	if (nb_of_args(cmds) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (g_ex_status = 2);
	}
	cmds->oldpwd = getcwd(NULL, 0);
	if (chdir(cmds->cmd_line[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDOUT_FILENO);
		ft_putstr_fd(cmds->cmd_line[1], STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
		return (g_ex_status = 1);
	}
	cmds->pwd = getcwd(NULL, 0);
	put_var_env("PWD", cmds->pwd, shell);
	put_var_env("OLDPWD", cmds->oldpwd, shell);
	return (g_ex_status = 0);
}
