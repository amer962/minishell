/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:02:03 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/04 17:42:53 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*skip_quotes(char *split, char ignore)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buff = malloc(ft_strlen(split) + 1);
	if (!buff)
		return (NULL);
	while (split[i])
	{
		if (split[i] != ignore)
		{
			buff[j] = split[i];
			j++;
		}
		i++;
	}
	buff[j] = '\0';
	return (buff);
}

static int	handle_quoted(char **buff, char *token, char ignore)
{
	char	*quoted_str;
	char	*tmp;

	quoted_str = skip_quotes(token, ignore);
	if (!quoted_str)
		return (-1);
	if (**buff != '\0')
	{
		tmp = ft_strjoin(*buff, " ");
		free(*buff);
		if (!tmp)
		{
			free(quoted_str);
			return (-1);
		}
		*buff = tmp;
	}
	tmp = ft_strjoin(*buff, quoted_str);
	free(quoted_str);
	free(*buff);
	if (!tmp)
		return (-1);
	*buff = tmp;
	return (0);
}

static int	handle_unquoted(char **buff, char *token)
{
	char	*tmp;

	if (**buff != '\0')
	{
		tmp = ft_strjoin(*buff, " ");
		free(*buff);
		if (!tmp)
			return (-1);
		*buff = tmp;
	}
	tmp = ft_strjoin(*buff, token);
	free(*buff);
	if (!tmp)
		return (-1);
	*buff = tmp;
	return (0);
}

int	process_token(char **buff, char *token, char *ignore)
{
	int	ret;

	*ignore = '\0';
	ret = ft_echo_quotes(token, ignore);
	if (ret < 0)
		return (-1);
	if (*ignore)
	{
		ret = handle_quoted(buff, token, *ignore);
		if (ret < 0)
			return (-1);
	}
	else
	{
		ret = handle_unquoted(buff, token);
		if (ret < 0)
			return (-1);
	}
	return (0);
}

int	ft_echo(t_list *command)
{
	char	**split;
	char	*buff;
	char	ignore;
	int		i;
	int		n_flag;

	ignore = '\0';
	i = 1;
	n_flag = 0;
	split = ft_split_custom_exp(command->content, ' ');
	if (!split)
		return (-1);
	while (split[i] && ft_strcmp(split[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	if (ft_echo_quotes_manger(split, &i, &ignore, &buff) < 0)
		return (-1);
	printf("%s", buff);
	free(buff);
	if (!n_flag)
		printf("\n");
	frees_split(split);
	return (0);
}
