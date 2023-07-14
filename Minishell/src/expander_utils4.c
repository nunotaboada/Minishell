/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 23:04:13 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/06 23:04:13 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

int	end_varpos(char *s, int pos)
{
	int		len;

	len = ft_strlen(s);
	while (pos < len)
	{
		if (s[pos] == '$' || s[pos] == '\'' \
		|| s[pos] == '\"' || s[pos - 1] == '?' || s[pos] == '\0')
			return (pos);
		pos++;
	}
	return (len);
}

/* tive que retirar free(&data) no if e no fim por naõ ser endereço heap*/
char	*checkenv(char *str, t_shell *sh)
{
	char		*word;
	t_datamini	data;

	if (!str)
		return (NULL);
	initdatamini(&data);
	word = NULL;
	while (str[data.i] != '\0')
	{
		initcicle(str, &data);
		data.rest = get_rest(str, data.start, data.i);
		if (str[data.i] == '$' && str[data.i + 1] == '\0')
		{
			data.conc = ft_result(data.rest, ft_strdup("$"));
			word = concate(word, data.conc);
			free(data.conc);
			return (word);
		}
		data.env = process_env_variable(str, &data, sh);
		data.conc = ft_result(data.rest, data.env);
		word = concate(word, data.conc);
		free(data.conc);
	}
	return (word);
}
