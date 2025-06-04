/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:37:56 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/04 19:53:20 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env_value(char *name, t_cmd *cmd)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], name, len) && cmd->env[i][len] == '=')
		{
			return (ft_strdup(cmd->env[i] + len + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}

static char	*expantions(char *input, int *i, t_cmd *cmd)
{
	char	*name;
	char	*value;
	int		start;

	if (input[*i + 1] && input[*i + 1] == '?')
	{
		*i += 2;
		return (ft_itoa(cmd->exit_status));
	}
	if (!input[*i + 1] || (!ft_isalnum(input[*i + 1]) && input[*i + 1] != '_'))
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	start = *i + 1;
	*i = start;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	name = ft_substr(input, start, *i - start);
	value = get_env_value(name, cmd);
	free(name);
	return (value);
}

char *expander_input(char *input, char **env)
{
    char *expanded = ft_strdup("");
    char *expand_var;
    char *temp;
    char c[2];
    int i;
    int flag_single = 0;
    int flag_double = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == '\'' && !flag_double)
        {
            flag_single = !flag_single;
            i++;
        }
        else if (input[i] == '\"' && !flag_single)
        {
            flag_double = !flag_double;
            i++;
        }
        else if (input[i] == '$' && !flag_single)
        {
            expand_var = expantions(input, &i, env);
            temp = ft_strjoin(expanded, expand_var);
            free(expanded);
            free(expand_var);
            expanded = temp;
        }
        else 
        {
            c[0] = input[i];
            c[1] = '\0';
            temp = ft_strjoin(expanded, c);
            free(expanded);
            expanded = temp;
            i++;
        }
    }
    return (expanded);
}
