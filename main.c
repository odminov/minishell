/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:48:32 by ahonchar          #+#    #+#             */
/*   Updated: 2018/08/22 15:48:34 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define STDIN 0

extern char	*g_list_inline_func[];
extern int	(*g_inline_func[]) (char **);
extern char	**g_env_cp;

char	*read_line(void)
{
	char	*line;

	line = NULL;
	if (get_next_line(STDIN, &line) < 0)
		return (NULL);
	return (line);
}

char	**split_args(char *line)
{
	char	**args;

	args = ft_strsplit(line, ' ');
	if (!args)
		return (NULL);
	return (args);
}

int		execute(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve("/bin/ls", args, g_env_cp) == -1)
			perror("lsh execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("lsh");
	}
	else
	{
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

int		check_command(char **args)
{
	int		i;

	if (!args[0])
		return (1);
	i = 0;
	while (i < num_func())
	{
		if (ft_strcmp(args[0], g_list_inline_func[i]) == 0)
			return ((*g_inline_func[i])(args));
		i++;
	}
	return (execute(args));
}

void	main_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		ft_printf("$> ");
		line = read_line();
		args = split_args(line);
		status = check_command(args);
		free(line);
		free(args);
	}
}

int		main(void)
{
	get_copy_env();
	main_loop();
	return (0);
}
