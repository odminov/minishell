/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inline_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:25:18 by ahonchar          #+#    #+#             */
/*   Updated: 2018/08/23 14:25:27 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>

char	*g_list_inline_func[] = {
	"cd",
	"help",
	"exit",
	"env",
	"setenv"
};
int	(*g_inline_func[]) (char **) = {
	ft_cd,
	ft_help,
	ft_exit,
	ft_env,
	ft_setenv
};

int			num_func(void)
{
	return (sizeof(g_list_inline_func) / sizeof(char *));
}

int			ft_cd(char **args)
{
	char	*dir;

	if (args[1] == NULL)
	{
		if ((dir = get_env_var("HOME")))
		{
			if (chdir(dir) != 0)
				ft_printf("error: cd: %s\n", dir);
		}
	}
	else
	{
		if ((ft_strcmp(args[1], "-") == 0) && (dir = get_env_var("OLDPWD")))
		{
			if (chdir(dir) != 0)
				ft_printf("error - : cd: %s\n", dir);
			return (1);
		}
		if (chdir(args[1]) != 0)
			ft_printf("error: cd: %s\n", args[1]);
	}
	return (1);
}

int			ft_help(char **args)
{
	int		i;

	if (args[1])
		ft_printf("Надо просить помощи без аргументов\n");
	ft_printf("ahonchar's minishell\n");
	ft_printf("Please type command name and its arguments\n");
	ft_printf("List of inline commands:\n");
	i = 0;
	while (i < num_func())
		ft_printf("\t%s\n", g_list_inline_func[i++]);
	return (1);
}

int			ft_exit(char **args)
{
	if (args[1])
		return (0);
	return (0);
}
