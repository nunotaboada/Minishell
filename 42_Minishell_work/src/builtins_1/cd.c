/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:07:46 by nsoares-          #+#    #+#             */
/*   Updated: 2023/06/07 14:15:00 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int cd_back(t_shell *shell, t_cmds *cmds)
{
    cmds->cmd_line[1] = get_env("OLDPWD", shell);
    if (cmds->cmd_line[1] == NULL) 
    {
        printf("minishell: cd: OLDPWD not set\n");
        return (g_ex_status = 1);
    }
    cmds->oldpwd = getcwd(NULL, 0);
    if (chdir(cmds->cmd_line[1]) != 0)
    {
        free(cmds->oldpwd);
        printf("minishell: cd: ");
		printf("%s", get_env("OLDPWD", shell));
		printf(": No such file or directory\n");
        return (g_ex_status = 1);
    }
    cmds->pwd = getcwd(NULL, 0);
    put_var_env("PWD", cmds->pwd, shell);
    put_var_env("OLDPWD", cmds->oldpwd, shell);
    printf("%s\n", cmds->cmd_line[1]);
    free(cmds->pwd);
    free(cmds->oldpwd);
    return (g_ex_status = 0);
}

int get_cd_home(t_shell *shell)
{
    char *go_home;

    go_home = get_env("HOME", shell);
    if (!go_home)
    {
        printf("minishell: cd: HOME not set\n");
        return (g_ex_status = 1); 
    }
    chdir(go_home);
    free(go_home);
    return (g_ex_status = 0);
}

int built_cd_2(t_cmds *cmds, t_shell *shell)
{
    cmds->oldpwd = getcwd(NULL, 0);
    if (chdir(cmds->cmd_line[1]) == -1)
    {
        free(cmds->oldpwd);
        ft_putstr_fd("minishell: cd: ", STDOUT_FILENO);
		ft_putstr_fd(cmds->cmd_line[1], STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
        return (g_ex_status = 1);
    }
    cmds->pwd = getcwd(NULL, 0);
    put_var_env("PWD", cmds->pwd, shell);
    put_var_env("OLDPWD", cmds->oldpwd, shell);
    free(cmds->pwd);
    free(cmds->oldpwd);
    return (g_ex_status = 0);
}

int built_cd(t_cmds *cmds, t_shell *shell)
{
    if (!cmds->cmd_line[1] || ft_strcmp(cmds->cmd_line[1], "~") == 0)
        return (get_cd_home(shell));
    if ((nb_of_args(cmds) == 2) && (ft_strcmp(cmds->cmd_line[1], "-") == 0))
        return (cd_back(shell, cmds));
    if (nb_of_args(cmds) > 2)
    {
        printf("minishell: cd: too many arguments\n");
        return (g_ex_status = 2);
    }
    else
        built_cd_2(cmds, shell);
    return (g_ex_status);
}
