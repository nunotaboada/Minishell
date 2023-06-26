/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_teste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:59:33 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/25 21:59:33 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

char* custom_strpbrk(const char* str, const char* charset)
{
    while (*str) {
        const char* ptr = charset;
        while (*ptr) {
            if (*ptr == *str) {
                return (char*)str;
            }
            ptr++;
        }
        str++;
    }

    return NULL;
}

char* custom_strtok_r(char* str, const char* delim, char** rest) {
    if (str != NULL)
        *rest = str;

    if (*rest == NULL)
        return NULL;

    char* token_start = *rest;
    char* token_end = strpbrk(*rest, delim);

    if (token_end != NULL) {
        *token_end = '\0';
        *rest = token_end + 1;
    } else {
        *rest = NULL;
    }

    return token_start;
}

char	*new_word(t_shell *sh, char *temp)
{
	char	*rest;
	char	*new_str;

	new_str = NULL;
	rest = NULL;
	sh->i = 0;
	while (temp[sh->i])
	{
		rest = allword(sh, temp);
		if (rest)
		{
			new_str = concate(new_str, rest);
			free (rest);
		}
		printf("sh->i 3 newword %d\n", sh->i);
	}
	return (new_str);
}

int main ()
{
	char str[] = "Este$e 2$um$exemplo$de$strtok_r";
    char** token;
    char* rest = NULL;

    *token = custom_strtok_r(str, "$", &rest);

    while ((*token) != NULL)
	{
        printf("%s\n", *token);

        *token = custom_strtok_r(NULL, "$", &rest);
    }
	doexp

}
/*int main() {
    char str[] = "Este$e$um$exemplo$de$strtok_r";
    char* token;
    char* rest = NULL;

    token = custom_strtok_r(str, "$", &rest);

    while (token != NULL) {
        printf("%s\n", token);

        token = custom_strtok_r(NULL, "$", &rest);
    }

    return 0;
}*/
