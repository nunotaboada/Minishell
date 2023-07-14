/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:58:39 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/24 20:58:39 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

static char	*get_environment_variable(const char *str, t_datamini *data)
{
	int		end;
	char	*var;

	var = NULL;
	end = data->i;
	var = ft_substr(str, data->start, end - data->start);
	data->i = end;
	return (var);
}

static char	*get_env_value(char *str, char *var, t_datamini *data, t_shell *sh)
{
	if (sh->dquotes)
		return (get_env(var, sh));
	return (ft_substr(str, data->start - 1, data->i - data->start + 1));
}

/* já considera o espaço no while*/
static void	initcicle2(char *str, t_datamini *data)
{
	(data->i)++;
	data->start = data->i;
	while (str[data->i] != '$' && str[data->i] \
	&& str[data->i] != '\'' && str[data->i] != ' ')
		(data->i)++;
}

/* já considera o espaço no if*/

static char	*process_variable(char *str, t_datamini *d, t_shell *sh)
{
	char	*env;
	char	*var;
	char	*var1;

	env = NULL;
	var = NULL;
	var1 = NULL;
	initcicle2(str, d);
	var1 = get_environment_variable(str, d);
	var = ft_strdup(var1);
	env = get_env_value(str, var, d, sh);
	free(var1);
	free(var);
	return (env);
}

char	*process_env_variable(char *str, t_datamini *d, t_shell *sh)
{
	char	*env;

	env = NULL;
	if (str[d->i] == '$' && (str[d->i + 1] == '\'' || str[d->i + 1] == '$' \
	|| str[d->i + 1] == ' '))
	{
		env = ft_strdup("$");
		(d->i)++;
	}
	else if (str[d->i] == '$' && str[d->i + 1] == '?')
	{
		(d->i) += 2;
		return (ft_itoa(g_ex_status));
	}
	else if (str[d->i] == '$')
		env = process_variable(str, d, sh);
	return (env);
}
