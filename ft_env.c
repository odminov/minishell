/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 14:56:25 by ahonchar          #+#    #+#             */
/*   Updated: 2018/09/16 17:44:43 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

#define ENV_CP glob_data()->g_env_cp

static char	**copy_current(void)
{
	int		i;
	char	**temp;

	i = 0;
	while (ENV_CP[i])
		i++;
	if (!(temp = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	temp[i] = NULL;
	i = 0;
	while (ENV_CP[i])
	{
		temp[i] = ft_strdup(ENV_CP[i]);
		i++;
	}
	return (temp);
}

static int	return_old_env(char **temp)
{
	int		i;

	i = 0;
	while (ENV_CP[i])
	{
		free(ENV_CP[i]);
		i++;
	}
	free(ENV_CP);
	ENV_CP = temp;
	return (1);
}

int			ft_env(char **args)
{
	int		i;
	char	**temp;
	char	**temp_env;

	i = 1;
	if (!args)
		return (0);
	temp_env = copy_current();
	if (args[i] && ft_strchr(args[i], '='))
	{
		ft_setenv(args);
		i++;
	}
	if (!args[i])
	{
		print_env();
		return_old_env(temp_env);
		return (1);
	}
	temp = args;
	args = &args[i];
	run_command(args);
	return_old_env(temp_env);
	args = temp;
	return (1);
}
