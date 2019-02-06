/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 14:05:54 by ahonchar          #+#    #+#             */
/*   Updated: 2018/09/16 17:43:52 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define ENV_CP glob_data()->g_env_cp

char		**get_copy_env(void)
{
	int			i;
	char		*temp;
	extern char	**environ;

	i = 0;
	while (environ[i])
		i++;
	if (!(ENV_CP = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	ENV_CP[i] = NULL;
	i = 0;
	while (environ[i])
	{
		if (!(ENV_CP[i] = ft_strdup(environ[i])))
			return (NULL);
		i++;
	}
	i = (get_env_var("SHLVL")) ? ft_atoi(get_env_var("SHLVL")) + 1 : 1;
	temp = ft_itoa(i);
	change_env_var("SHLVL=", temp);
	free(temp);
	return (ENV_CP);
}

static int	add_new_var(char *var)
{
	char	**temp;
	int		i;

	i = 0;
	while (var[i])
		i++;
	var[i] = '=';
	i = 0;
	while (ENV_CP[i])
		i++;
	if (!(temp = (char **)malloc(sizeof(char *) * (i + 2))))
		return (0);
	temp[i + 1] = NULL;
	i = 0;
	while (ENV_CP[i])
	{
		temp[i] = ENV_CP[i];
		i++;
	}
	temp[i] = var;
	free(ENV_CP);
	ENV_CP = temp;
	return (1);
}

char		*get_env_var(const char *var)
{
	int		i;

	i = 0;
	while (ENV_CP[i])
	{
		if (find_var(ENV_CP[i], var))
			return (&(ENV_CP[i][ft_strlen(var) + 1]));
		i++;
	}
	return (NULL);
}

int			ft_setenv(char **args)
{
	int		i;
	char	*var;
	char	*equ_sign;

	if (!args[1])
		return (print_env());
	if (!(var = ft_strchr(args[1], '=')) || var[1] == '=')
		return (print_error("misishell: bad assigment", NULL));
	var = ft_strdup(args[1]);
	equ_sign = ft_strchr(var, '=');
	*equ_sign = '\0';
	i = 0;
	while (ENV_CP[i])
	{
		if (find_var(ENV_CP[i], var))
		{
			free(ENV_CP[i]);
			ENV_CP[i] = var;
			*equ_sign = '=';
			return (1);
		}
		i++;
	}
	return (add_new_var(var));
}

int			change_env_var(const char *var, const char *value)
{
	char	**temp;

	if (!value)
		return (0);
	temp = (char **)malloc(sizeof(char *) * 3);
	temp[0] = ft_strdup("\0");
	temp[1] = ft_strjoin(var, value);
	temp[2] = NULL;
	if (ft_setenv(temp))
	{
		free(temp[0]);
		free(temp[1]);
		free(temp);
		return (1);
	}
	free(temp[0]);
	free(temp[1]);
	free(temp);
	return (1);
}
