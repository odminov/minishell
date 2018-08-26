/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 21:51:59 by ahonchar          #+#    #+#             */
/*   Updated: 2018/08/26 21:52:00 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static int	cd_home(void)
{
	char *dir;

	if (!(dir = get_env_var("HOME")))
		return (1);
	if (chdir(dir) != 0)
		return (ft_printf("error: cd: %s\n", dir));
	change_env_var("OLDPWD=", get_env_var("PWD"));
	dir = NULL;
	change_env_var("PWD=", getcwd(dir, PATH_MAX));
	free(dir);
	return (1);
}

int			ft_cd(char **args)
{
	char	*dir;

	if (args[1] == NULL)
		return (cd_home());
	if ((ft_strcmp(args[1], "-") == 0))
	{
		if (!(dir = get_env_var("OLDPWD")))
			return (1);
		if (chdir(dir) != 0)
			return (ft_printf("error: cd: %s\n", dir));
		change_env_var("OLDPWD=", get_env_var("PWD"));
		dir = NULL;
		change_env_var("PWD=", getcwd(dir, PATH_MAX));
		free(dir);
		return (1);
	}
	if (chdir(args[1]) != 0)
		return (ft_printf("error: cd: %s\n", args[1]));
	change_env_var("OLDPWD=", get_env_var("PWD"));
	dir = NULL;
	change_env_var("PWD=", getcwd(dir, PATH_MAX));
	free(dir);
	return (1);
}

int			ft_pwd(char **args)
{
	char	*dir;

	if (args && args[1])
		;
	dir = NULL;
	ft_printf("%s\n", getcwd(dir, PATH_MAX));
	free(dir);
	return (1);
}
