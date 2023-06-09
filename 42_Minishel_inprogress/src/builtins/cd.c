/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:07:46 by nsoares-          #+#    #+#             */
/*   Updated: 2023/05/16 23:22:54 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int built_cd(t_cmds *cmds)
{
    cmds->new_dir = cmds->cmd_line[1];
    if (nb_of_args(cmds) <= 2)
    {
        if (cmds->new_dir == NULL)
            cmds->new_dir = getenv("HOME");
        else if (ft_strcmp(cmds->new_dir, "~"))
            cmds->new_dir = getenv("HOME");
        chdir(cmds->new_dir);
		cmds->new_dir = NULL;
    }
    else
    {
        printf("minishell: cd: too many arguments\n");
        return (g_ex_status = 2);
    }
    return (g_ex_status = 0);
}


// static void	change_to_home(t_root *root)
// {
// 	char	*path;

// 	path = get_env_value(root, "HOME");
// 	chdir(path);
// 	change_value(root, "PWD", path);
// 	if (path)
// 		free(path);
// }

// static int	has_more_params_error(int size)
// {
// 	if (size > 2)
// 	{
// 		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR);
// 		return (1);
// 	}
// 	return (0);
// }

// static void	refresh_pwd_env(t_root *root)
// {
// 	char	*path;

// 	path = get_pwd();
// 	change_value(root, "PWD", path);
// 	free(path);
// }

// static int	check_home(t_root *root)
// {
// 	if (get_array_size(root->tree->command) == 1)
// 	{
// 		change_to_home(root);
// 		return (1);
// 	}
// 	if (is_equal(root->tree->command[1], "~"))
// 	{
// 		change_to_home(root);
// 		return (1);
// 	}
// 	return (0);
// }

// int	built_cd(t_root *root)
// {
// 	char	*old_pwd;

// 	if (check_home(root))
// 		return (0);
// 	if (has_more_params_error(get_array_size(root->tree->command)))
// 		return (1);
// 	else
// 	{
// 		if (chdir(root->tree->command[1]) == 0)
// 		{
// 			old_pwd = get_env_value(root, "PWD");
// 			change_value(root, "OLDPWD", old_pwd);
// 			free(old_pwd);
// 			refresh_pwd_env(root);
// 		}
// 		else
// 		{
// 			ft_putstr_fd("minishell: cd: ", STDERR);
// 			ft_putstr_fd(root->tree->command[1], STDERR);
// 			ft_putstr_fd(": No such file or directory\n", STDERR);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }