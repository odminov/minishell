/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 11:41:30 by ahonchar          #+#    #+#             */
/*   Updated: 2018/08/27 11:41:31 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <stdlib.h>

static char	*check_dir(const char *dir, const char *binary)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(dir, "/");
	path = ft_strjoin(temp, binary);
	free(temp);
	temp = NULL;
	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char		*find_command(char **args)
{
	int		i;
	char	**dirs;
	char	*path;

	if (!(dirs = ft_strsplit(get_env_var("PATH"), ':')))
		return (NULL);
	i = 0;
	path = NULL;
	while (dirs[i])
	{
		if ((path = check_dir(dirs[i], args[0])))
			break ;
		free(path);
		i++;
	}
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (path);
}

void		check_dollar(char **args)
{
	int		i;
	char	*var;
	char	*temp;

	i = 0;
	while (args && args[i])
	{
		if ((var = ft_strchr(args[i], '$')))
		{
			*var = '\0';
			var++;
			temp = args[i];
			args[i] = ft_strjoin(args[i], get_env_var(var));
			free(temp);
		}
		i++;
	}
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
