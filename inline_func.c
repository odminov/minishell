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
	"setenv",
	"unsetenv",
	"pwd",
	"echo"
};
int	(*g_inline_func[]) (char **) = {
	ft_cd,
	ft_help,
	ft_exit,
	ft_env,
	ft_setenv,
	ft_unsetenv,
	ft_pwd,
	ft_echo
};

int			num_func(void)
{
	return (sizeof(g_list_inline_func) / sizeof(char *));
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

char		*find_echo(char *line)
{
	int			i;
	const char	name[] = "echo";

	while (line && (*line == ' ' || *line == '\t'))
		line++;
	i = 0;
	while (line[i] && name[i] && (line[i] == name[i]))
		i++;
	if (name[i] == '\0' && line[i] == ' ')
		return (line);
	return (NULL);
}

int			ft_echo(char **args)
{
	int	i;

	i = 1;
	while (args && args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		i++;
	}
	write(1, "\n", 1);
	return (1);
}

int			ft_exit(char **args)
{
	if (args[1])
		return (0);
	return (0);
}
