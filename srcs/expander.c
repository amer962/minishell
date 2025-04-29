/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:37:56 by aalquraa          #+#    #+#             */
/*   Updated: 2025/04/29 19:54:11 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_cmds(t_cmd **cmd, char **env)
{
	t_list	*current;
	char	*expanded_cmd;

	current = (*cmd)->word;
	while (current != NULL)
	{
		expanded_cmd = expander_input(current, env);
		free(current->content);
		current->content = expanded_cmd;
		current = current->next;
	}
}

static char	*get_env_value(char *name, char **env)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
		{
			return (ft_strdup(env[i] + len + 1));
		}
		i++;
	}
	return (NULL);
}

static char	*expantions(char *input, int i, char **env)
{
	char	*name;
	char	*value;
	int		start;
	int		end;

	start = i + 1;
	if (!input[start] || (!ft_isalnum(input[start]) && input[start] != '_'))
		return (ft_strdup(""));
	i = start;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	end = i;
	name = ft_substr(input, start, end - start);
	if (!name)
		return (NULL);
	value = get_env_value(name, env);
	if (!value)
		value = ft_strdup("");
	free(name);
	return (value);
}

char	*expander_input(t_list *input, char **env)
{
	char *expanded = ft_strdup("");
	char *expand_var;
	char *temp;
	char c[2];
	int i;
	int start = 0;
	int end = 0;

	int flag_single = 0;
	int flag_double = 0;
	i = 0;

	char *content = (char *)input->content;
	while (content[i])
	{
		if (content[i] == '\'' && !flag_double)
		{
			flag_single = !flag_single;
			i++;
		}
		else if (content[i] == '\"' && !flag_single)
		{
			flag_double = !flag_double;
			i++;
		}
		else if (content[i] == '$' && !flag_single)
		{
			expand_var = expantions(content, i, env);
			temp = ft_strjoin(expanded, expand_var);
			free(expanded);
			free(expand_var);
			expanded = temp;
			i++;
			while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
				i++;
		}
		else
		{
			c[0] = content[i];
			c[1] = '\0';
			temp = ft_strjoin(expanded, c);
			free(expanded);
			expanded = temp;
			i++;
		}
	}
	return (expanded);
}
