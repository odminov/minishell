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
#include <stdlib.h>

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
	char	*temp;

	if (args[1] == NULL)
	{
		if ((dir = get_env_var("HOME")))
		{
			if (chdir(dir) != 0)
				return (ft_printf("error: cd: %s\n", dir));
			change_env_var("OLDPWD=", get_env_var("PWD"));
			change_env_var("PWD=", dir);
		}
	}
	else
	{
		if ((ft_strcmp(args[1], "-") == 0) && (dir = get_env_var("OLDPWD")))
		{
			if (chdir(dir) != 0)
				return (ft_printf("error - : cd: %s\n", dir));
			temp = ft_strdup(get_env_var("OLDPWD"));
			change_env_var("OLDPWD=", get_env_var("PWD"));
			change_env_var("PWD=", temp);
			free(temp);
			return (1);
		}
		if (chdir(args[1]) != 0)/*fix cd .. in env OLDPWD and PWD */
			return (ft_printf("error: cd: %s\n", args[1]));
		change_env_var("OLDPWD=", get_env_var("PWD"));
		if (args[1][0] == '/')
			change_env_var("PWD=", args[1]);
		else
		{
			temp = ft_strjoin(get_env_var("PWD"), "/");
			change_env_var("PWD=", (dir = ft_strjoin(temp, args[1])));
			free(dir);
			free(temp);
		}
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
