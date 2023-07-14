/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:50:55 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/24 17:50:55 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

char	*get_rest(const char *str, int start, int end)
{
	if (end - start > 0)
		return (ft_substr(str, start, end - start));
	return (NULL);
}

void	initdatamini(t_datamini *data)
{
	data->i = 0;
	data->start = 0;
	data->rest = NULL;
	data->env = NULL;
	data->conc = NULL;
}

void	initcicle(char *str, t_datamini *data)
{
	data->start = data->i;
	data->rest = NULL;
	data->env = NULL;
	while (str[data->i] != '$' && str[data->i] != '\0')
		data->i++;
}
