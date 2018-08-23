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

#include "./libft/libft.h"
#include "header.h"
#include <unistd.h>
#define HOME_DIR "/"

char	*g_list_func[] = {
	"cd",
	"help",
	"exit"
};
int	(*g_inln_func[]) (char **) = {
	ft_cd,
	ft_help,
	ft_exit
};

int			num_func(void)
{
	return (sizeof(g_list_func) / sizeof(char *));
}

int			ft_cd(char **args)
{
	if (args[1] == NULL)
	{
		ft_printf("err");
		chdir(HOME_DIR);
	}
	else
	{
		if (chdir(args[1]) != 0)
			ft_printf("err minishell");
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
		ft_printf("\t%s\n", g_list_func[i++]);
	return (1);
}

int			ft_exit(char **args)
{
	if (args[1])
		return (0);
	return (0);
}
