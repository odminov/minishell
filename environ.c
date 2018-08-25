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

char		**g_env_cp;

char		**get_copy_env(void)
{
	int			i;
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
	return (g_env_cp);
}

int			ft_env(char **args)
{
	int		i;

	if (args[1])
		ft_printf("Use \"env\" command without arguments\n");
	i = 0;
	while (g_env_cp[i])
		ft_printf("%s\n", g_env_cp[i++]);
	return (1);
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
		temp[i] = g_env_cp[
			i];
		i++;
	}
	temp[i] = var;
	free(g_env_cp);
	g_env_cp = temp;
	return (1);
}

char	*get_env_var(const char *var)
{
	int		i;
	char	*res;

	i = 0;
	while (g_env_cp[i])
	{
		if (ft_strstr(g_env_cp[i], var))
		{
			res = ft_strchr(g_env_cp[i], '=');
			return (!res ? NULL : res + 1);
		}
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
		return (ft_env(args));
	if ((!ft_strchr(args[1], '=')) || args[2])
		return (ft_printf("misishell: bad assigment\n"));
	var = ft_strdup(args[1]);
	equ_sign = ft_strchr(var, '=');
	*equ_sign = '\0';
	i = 0;
	while (g_env_cp[i])
	{
		if (ft_strstr(g_env_cp[i], var))
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

int			ft_unsetenv(char **args)
{
	if (!args[1])
		return (0);
	return (1);
}

int		change_env_var(const char *var, const char *value)
{
	char	**temp;

	temp = (char **)malloc(sizeof(char *) * 3);
	temp[0] = ft_strdup("test");
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
	return (0);
}
