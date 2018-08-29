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
#include <signal.h>

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

void	signal_hendl(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar('\n');
		ft_putstr("$> ");
	}
}

int		execute(char **args)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (!(path = find_command(args)))
		return (print_error("minishell: command not found: ", args[0]));
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(path, args, g_env_cp) == -1)
			print_error("minishell execve", NULL);
		free(path);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		print_error("minishell pid error", NULL);
	else
		{
			signal(SIGINT, signal_hendl_waitpid);
			waitpid(pid, &status, 0);
			signal(SIGINT, signal_hendl);
		}
	free(path);
	return (1);
}

void	check_args(char **args)
{
	char	*temp;
	int		i;

	if (!args)
		return ;
	if (ft_strcmp(args[0], "~") == 0)
	{
		temp = ft_strdup(get_env_var("HOME"));
		free(args[0]);
		args[0] = temp;
	}
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '~')
		{
			temp = args[i];
			args[i] = ft_strjoin(get_env_var("HOME"), &(args[i][1]));
			free(temp);
		}
		i++;
	}
	check_dollar(args);
}

int		check_command(char **args)
{
	int		i;

	if (!args || !args[0])
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

int		main(void)
{
	char	*line;
	char	**args;
	int		status;
	int		i;

	status = 1;
	get_copy_env();
	signal(SIGINT, signal_hendl);
	while (status)
	{
		ft_putstr("$> ");
		line = read_line();
		if (!line || !*line)
			continue ;
		args = strsplit_ws(line);
		check_args(args);
		status = check_command(args);
		free(line);
		i = 0;
		while (args && args[i])
			free(args[i++]);
		free(args);
	}
	return (0);
}
