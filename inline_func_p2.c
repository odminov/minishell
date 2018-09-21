/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 21:51:59 by ahonchar          #+#    #+#             */
/*   Updated: 2018/09/16 17:45:21 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static void	change_old_pwd(void)
{
	char	temp[PATH_MAX];
	char	*dir;

	dir = get_env_var("PWD");
	if (dir)
		change_env_var("OLDPWD=", dir);
	else
		change_env_var("OLDPWD=", getcwd(temp, PATH_MAX));
}

static int	cd_home(void)
{
	char	temp[PATH_MAX];
	char	*dir;

	if (!(dir = get_env_var("HOME")))
	{
		change_env_var("PWD=", getcwd(temp, PATH_MAX));
		change_env_var("OLDPWD=", get_env_var("PWD"));
		return (1);
	}
	if (chdir(dir) != 0)
		return (print_error("error: cd: ", dir));
	change_old_pwd();
	change_env_var("PWD=", getcwd(temp, PATH_MAX));
	return (1);
}

int			ft_cd(char **args)
{
	char	temp[PATH_MAX];
	char	*dir;

	if (args[1] == NULL || args[1][0] == '\0')
		return (cd_home());
	if ((ft_strcmp(args[1], "-") == 0))
	{
		if (!(dir = get_env_var("OLDPWD")))
		{
			change_env_var("PWD=", getcwd(temp, PATH_MAX));
			change_env_var("OLDPWD=", get_env_var("PWD"));
			return (1);
		}
		if (chdir(dir) != 0)
			return (print_error("error: cd: ", dir));
		change_old_pwd();
		change_env_var("PWD=", getcwd(temp, PATH_MAX));
		return (1);
	}
	if (chdir(args[1]) != 0)
		return (print_error("error: cd: ", args[1]));
	change_old_pwd();
	change_env_var("PWD=", getcwd(temp, PATH_MAX));
	return (1);
}

void		signal_hendl(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar('\n');
		ft_putstr("$> ");
	}
}

void		signal_hendl_waitpid(int signal)
{
	if (signal == SIGINT)
		ft_putchar('\n');
}
