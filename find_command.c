/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 11:41:30 by ahonchar          #+#    #+#             */
/*   Updated: 2018/09/16 17:44:27 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <stdlib.h>
#define GET_VAR get_env_var

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

	if (args[0] && (access(args[0], X_OK) == 0))
		return (ft_strdup(args[0]));
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

static void	join_env(char **args, int i, char *temp2)
{
	char	*var;

	var = args[i];
	temp2--;
	*temp2 = '$';
	args[i] = ft_strjoin(args[i], temp2);
	free(var);
}

void		check_dollar(char **args)
{
	int		i;
	char	*var;
	char	*temp;
	char	*temp2;

	i = 0;
	temp2 = NULL;
	while (args && args[i])
	{
		if ((var = ft_strchr(args[i], '$')))
		{
			*var++ = '\0';
			if ((temp2 = ft_strchr(var, '$')))
				*temp2++ = '\0';
			temp = args[i];
			args[i] = ft_strjoin(args[i], (GET_VAR(var)) ? GET_VAR(var) : "");
			if (temp2)
				join_env(args, i, temp2);
			free(temp);
			if (ft_strchr(args[i], '$'))
				continue ;
		}
		i++;
	}
}
