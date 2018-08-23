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
#include "./libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define STDIN 0

extern char	*g_list_func[];
extern int	(*g_inln_func[]) (char **);

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

int		execute(char **args, char **envp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	ft_printf("envp: %s\n", envp[14]);
	if (pid == 0)
	{
		if (execve("/bin/ls", args, envp) == -1)
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

int		check_command(char **args, char **envp)
{
	int		i;

	if (!args[0])
		return (1);
	i = 0;
	while (i < num_func())
	{
		if (ft_strcmp(args[0], g_list_func[i]) == 0)
			return ((*g_inln_func[i])(args));
		i++;
	}
	return (execute(args, envp));
}

void	main_loop(char **envp)
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
		status = check_command(args, envp);
		free(line);
		free(args);
	}
}

int		main(int ac, char **av, char **envp)
{
	if (ac < 2)
		if (av[1])
			;
	main_loop(envp);
	return (0);
}
