/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 14:05:54 by ahonchar          #+#    #+#             */
/*   Updated: 2018/08/25 14:05:56 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

char		**g_env_cp;

char		**get_copy_env(void)
{
	int			i;
	char		dir[PATH_MAX];
	char		*temp;
	extern char	**environ;

	i = 0;
	while (environ[i])
		i++;
	if (!(g_env_cp = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	g_env_cp[i] = NULL;
	i = 0;
	while (environ[i])
	{
		if (!(g_env_cp[i] = ft_strdup(environ[i])))
			return (NULL);
		i++;
	}
	temp = ft_strjoin(getcwd(dir, PATH_MAX), "/minishell");
	change_env_var("SHELL=", temp);
	free(temp);
	return (g_env_cp);
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
	while (g_env_cp[i])
		i++;
	if (!(temp = (char **)malloc(sizeof(char *) * (i + 2))))
		return (0);
	temp[i + 1] = NULL;
	i = 0;
	while (g_env_cp[i])
	{
		temp[i] = g_env_cp[i];
		i++;
	}
	temp[i] = var;
	free(g_env_cp);
	g_env_cp = temp;
	return (1);
}

char		*get_env_var(const char *var)
{
	int		i;

	i = 0;
	while (g_env_cp[i])
	{
		if (find_var(g_env_cp[i], var))
			return (&(g_env_cp[i][ft_strlen(var) + 1]));
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
	if ((!ft_strchr(args[1], '=')))
		return (print_error("misishell: bad assigment\n", NULL));
	var = ft_strdup(args[1]);
	equ_sign = ft_strchr(var, '=');
	*equ_sign = '\0';
	i = 0;
	while (g_env_cp[i])
	{
		if (find_var(g_env_cp[i], var))
		{
			free(g_env_cp[i]);
			g_env_cp[i] = var;
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
