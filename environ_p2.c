/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_p2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 22:44:03 by ahonchar          #+#    #+#             */
/*   Updated: 2018/09/16 17:44:13 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

#define ENV_CP glob_data()->g_env_cp

int			print_env(void)
{
	int		i;

	i = 0;
	while (ENV_CP[i])
	{
		ft_putstr(ENV_CP[i++]);
		ft_putchar('\n');
	}
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
	while (ENV_CP[i])
	{
		if (ENV_CP[i][0] != '\0')
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
	while (ENV_CP[i])
	{
		if (ENV_CP[i][0] == '\0')
		{
			free(ENV_CP[i]);
			i++;
		}
		temp[j] = ENV_CP[i];
		j++;
		if (ENV_CP[i])
			i++;
	}
	free(ENV_CP);
	ENV_CP = temp;
	return (1);
}

int			ft_unsetenv(char **args)
{
	int		i;

	if (!args[1])
		return (1);
	i = 0;
	while (ENV_CP[i])
	{
		if (find_var(ENV_CP[i], args[1]))
		{
			ENV_CP[i][0] = '\0';
			return (update_env());
		}
		i++;
	}
	return (1);
}
