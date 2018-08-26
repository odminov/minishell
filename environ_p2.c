/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_p2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 22:44:03 by ahonchar          #+#    #+#             */
/*   Updated: 2018/08/26 22:44:05 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

extern char	**g_env_cp;

int			ft_env(char **args)
{
	int		i;

	if (args[1])
		return (ft_printf("env: Invalid argument\n"));
	i = 0;
	while (g_env_cp[i])
		ft_printf("%s\n", g_env_cp[i++]);
	return (1);
}

char		*find_var(char *str, const char *name)
{
	int		i;

	i = 0;
	while (str[i] && name[i] && (str[i] == name[i]))
		i++;
	if (name[i] == '\0' && str[i] == '=')
		return (str);
	return (NULL);
}

static int	count_vars(void)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_env_cp[i])
	{
		if (g_env_cp[i][0] != '\0')
			j++;
		i++;
	}
	return (j);
}

static int	update_env(void)
{
	int		i;
	int		j;
	char	**temp;

	j = count_vars();
	temp = (char **)malloc(sizeof(char *) * j + 1);
	temp[j] = NULL;
	i = 0;
	j = 0;
	while (g_env_cp[i])
	{
		if (g_env_cp[i][0] == '\0')
		{
			free(g_env_cp[i]);
			i++;
		}
		temp[j] = g_env_cp[i];
		j++;
		i++;
	}
	free(g_env_cp);
	g_env_cp = temp;
	return (1);
}

int			ft_unsetenv(char **args)
{
	int		i;

	if (!args[1])
		return (1);
	i = 0;
	while (g_env_cp[i])
	{
		if (find_var(g_env_cp[i], args[1]))
		{
			g_env_cp[i][0] = '\0';
			return (update_env());
		}
		i++;
	}
	return (1);
}
