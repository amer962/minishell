/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching_bulidin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:43:49 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/04 17:42:27 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	searching_bulidin_2(char **split, t_cmd **cmd, char *t)
{
	int	s;

	if (ft_strcmp(split[0], "export") == 0)
	{
		ft_export(t, cmd);
		return (13);
	}
	if (ft_strcmp(split[0], "unset") == 0)
	{
		s = 1;
		while (split[s])
		{
			robo_unset(split[s], cmd);
			s++;
		}
		return (-3);
	}
	if (ft_strcmp(split[0], "env") == 0)
	{
		env(*cmd);
		return (-3);
	}
	return (0);
}

int	searching_bulidin_exit(char **split, t_cmd **cmd, char **input)
{
	if (!ft_strchr(*input, '|'))
		return (0);
	ft_printf("%2%s\n", *input);
	printf_split("output:", split);
	robo_exit(split, *cmd);
	ft_printf("%2e: %d\n", (*cmd)->exit_status);
	return (0);
}

int	searching_bulidin(char **split, t_cmd **cmd, char *t, char **input)
{
	int	ret;

	ret = searching_bulidin_2(split, cmd, t);
	if (ret < 0)
		return (ret);
	if (ft_strncmp(split[0], "cd", 2) == 0)
	{
		robo_cd(split);
		free(*input);
		return (-3);
	}
	return (0);
}
