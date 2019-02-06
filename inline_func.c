/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inline_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:25:18 by ahonchar          #+#    #+#             */
/*   Updated: 2018/09/16 17:45:06 by ahonchar         ###   ########.fr       */
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
	"echo"
};

int	(*g_inline_func[]) (char **) = {
	ft_cd,
	ft_help,
	ft_exit,
	ft_env,
	ft_setenv,
	ft_unsetenv,
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
		ft_putstr("Help: \n");
	ft_putstr("ahonchar's minishell\n");
	ft_putstr("Please type command name and its arguments\n");
	ft_putstr("List of inline commands:\n");
	i = 0;
	while (i < num_func())
	{
		ft_putchar('\t');
		ft_putstr(g_list_inline_func[i++]);
		ft_putchar('\n');
	}
	return (1);
}

int			ft_echo(char **args)
{
	int	i;

	i = 1;
	while (args && args[i])
	{
		if (i > 1)
			write(1, " ", 1);
		write(1, args[i], ft_strlen(args[i]));
		i++;
	}
	write(1, "\n", 1);
	return (1);
}

int			print_error(const char *error1, const char *error2)
{
	if (error1)
		ft_putstr_fd(error1, STDERR);
	if (error2)
		ft_putstr_fd(error2, STDERR);
	ft_putchar('\n');
	return (1);
}

int			ft_exit(char **args)
{
	if (args[1])
		return (0);
	return (0);
}
