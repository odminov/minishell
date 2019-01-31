/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:48:32 by ahonchar          #+#    #+#             */
/*   Updated: 2018/09/16 17:45:36 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>
#include <sys/ioctl.h>
#include <stdio.h>

#define PROMPT_SIZE 3

extern char *g_list_inline_func[];
extern int (*g_inline_func[]) (char **);

char	*cursor_le;
char	*cursor_ri;
char	*cursor_dw;
char	*cursor_up_;

extern char	PC;   /* For tputs.  */
extern char	*BC;  /* For tgoto.  */
extern char	*UP;
extern short ospeed;

t_glob	*glob_data(void)
{
	static t_glob data;

	return (&data);
}

void	print_err(char *err)
{
	if (err)
		ft_putstr_fd(err, STDERR);
	exit(1);
}

void	my_exit(char *err)
{
	if (err)
		ft_putstr_fd(err, STDERR);
	if ((tcsetattr(0, TCSANOW, &(glob_data()->settings))) < 0)
		print_err("Error restore terminal settings\n");
	exit(1);
}

int		execute(char **args)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (!(path = find_command(args)))
		return (check_perm(args));
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(path, args, glob_data()->g_env_cp) == -1)
			print_error("21sh: execve error", NULL);
		free(path);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		print_error("21sh: fork: child couldn't be created", NULL);
	else
	{
		signal(SIGINT, signal_hendl_waitpid);
		waitpid(pid, &status, 0);
		signal(SIGINT, signal_hendl);
	}
	free(path);
	return (1);
}

int		run_command(char **args)
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

int			stdin_putchar(int c)
{
	return (write(0, &c, 1));
}

void	move_right(t_inpt **list)
{
	if ((*list)->next)
	{
		(*list) = (*list)->next;
		glob_data()->c_pos++;
	}
	else
		return ;
	if ((glob_data()->c_pos - 1) % glob_data()->cols == 0)
		tputs(cursor_dw, 1, stdin_putchar);
	else
		tputs(cursor_ri, 1, stdin_putchar);
}

void	move_left(t_inpt **list)
{
	if ((*list)->prev)
	{
		(*list) = (*list)->prev;
		glob_data()->c_pos--;
	}
	else
		return ;
	if (glob_data()->c_pos % (glob_data()->cols) == 0)
	{
		tputs(cursor_up_, 1, stdin_putchar);
		tputs(tgoto(tgetstr("ch", 0), 0, glob_data()->cols), 1, stdin_putchar);
	}
	else
		tputs(cursor_le, 1, stdin_putchar);
}

void	move_up(t_inpt **list)
{
	int		i;

	i = 0;
	if (((glob_data()->c_pos) - glob_data()->cols) < PROMPT_SIZE + 1)
		return ;
	while (*list && i < glob_data()->cols)
	{
		move_left(list);
		i++;
	}
	// tputs(cursor_up_, 1, stdin_putchar);
	// tputs(tgoto(tgetstr("ch", 0), 0, glob_data()->c_pos % glob_data()->cols), 1, stdin_putchar);
	// *list = temp;
}

void	move_down(t_inpt **list)
{
	int		i;

	i = 0;
	if (((glob_data()->c_pos) + glob_data()->cols) > glob_data()->max_id)
		return ;
	while (i < glob_data()->cols)
	{
		move_right(list);
		i++;
	}
}

static void	read_key(unsigned long key, t_inpt **list)
{
	if (key == K_UP || key == K_UP_I)
		move_up(list);
	else if (key == K_DOWN || key == K_DOWN_I)
		move_down(list);
	else if (key == K_LEFT || key == K_LEFT_I)
		move_left(list);
	else if (key == K_RIGHT || key == K_RIGHT_I)
		move_right(list);
	else if (key == K_BACK_SP)
		;
	else if (key == K_SPACE)
		write(1, " ", 1);
}

t_inpt	*init_elem(void)
{
	t_inpt	*ret;

	ret = (t_inpt *)malloc(sizeof(t_inpt));
	if (!ret)
		return (NULL);
	ret->prev = NULL;
	ret->next = NULL;
	ret->c = 0;
	return (ret);
}

void	add_item(t_inpt **list, char c)
{
	t_inpt	*new_item;
	int		save_curs;

	new_item = init_elem();
	new_item->c = c;
	ft_putchar(c);
	if ((glob_data()->c_pos) % (glob_data()->cols) == 0)
	{
		//tputs(tgoto(tgetstr("LE", 0), 0, glob_data()->cols), 1, stdin_putchar);
		tputs(tgoto(tgetstr("DO", 0), 0, 1), 1, stdin_putchar);
		ft_putchar('\r');
		// tputs(tgoto(tgetstr("cm", 0), 0, 0), 1, stdin_putchar);
		//tputs(tgetstr("nw", 0), 1, stdin_putchar);
		ft_putstr_fd("tot samui sluchai\n", STDERR);
	}
	glob_data()->c_pos++;
	save_curs = glob_data()->c_pos;
	// tputs(tgetstr("cd", 0), 1, stdin_putchar);
	if ((*list)->prev)
		(*list)->prev->next = new_item;
	new_item->next = (*list);
	new_item->prev = (*list)->prev;
	(*list)->prev = new_item;
	new_item = (*list);
	while (new_item->next)
	{
		ft_putchar(new_item->c);
		glob_data()->c_pos++;
		new_item = new_item->next;
	}
	glob_data()->max_id++;
	tputs(tgoto(tgetstr("LE", 0), 0, glob_data()->c_pos - save_curs), 1, stdin_putchar);
	glob_data()->c_pos = save_curs;
}

void	parse_char(t_inpt **list, char c)
{
	if (list && *list && (*list)->next)
	{
		add_item(list, c);
	}
	else if (list && *list)
	{
		(*list)->c = c;
		ft_putchar(c);
		if (glob_data()->c_pos % (glob_data()->cols) == 0)
			tputs(cursor_dw, 1, stdin_putchar);
		glob_data()->c_pos++;
		(*list)->next = init_elem();
		(*list)->next->prev = (*list);
		(*list) = (*list)->next;
		if (glob_data()->c_pos > glob_data()->max_id)
			glob_data()->max_id = glob_data()->c_pos;
	}
}

t_inpt	*wait_input(void)
{
	unsigned long	buf;
	t_inpt			*list;
	t_inpt			*head;
	int				i;

	if (!(list = init_elem()))
		return (NULL);
	head = list;
	buf = 0;
	while ((i = read(STDIN, &buf, sizeof(buf))) > 0)
	{
		if (buf == K_ENTER)
		{
			while (list->next)
				move_right(&list);
		 	return (head);
		}
		else if (buf == K_DEL)
			parse_char(&list, '~');
		if (buf < 127)
			parse_char(&list, (char)buf);
		else
			read_key(buf, &list);
		ft_putnbr_fd(glob_data()->c_pos, STDERR);
		ft_putstr_fd(" | max_id ", STDERR);
		ft_putnbr_fd(glob_data()->max_id, STDERR);
		ft_putstr_fd(" | cols ", STDERR);
		ft_putnbr_fd(glob_data()->cols, STDERR);
		write(STDERR, "\n", 1);
		buf = 0;
	}
	if (i < 0)
		perror("");
	return (head);
}

static void	resize(int signal)
{
	struct winsize	window;

	if (signal == SIGWINCH)
	{
		if (ioctl(STDIN, TIOCGWINSZ, &window) < 0)
			my_exit("Cannot detect window size\n");
		glob_data()->cols = window.ws_col;
	}
	ft_putstr_fd("resize interrupt\n", STDERR);
	ft_putnbr_fd(glob_data()->max_id / glob_data()->cols, STDERR);
	ft_putstr_fd("\n", STDERR);
}

int		main_loop(void)
{
	char	**args;
	int		status;
	int		i;
	t_inpt	*input;

	status = 1;
	while (status)
	{
		ft_putstr("$> ");
		input = wait_input();
		// tputs(tgetstr("cd", 0), 1, stdin_putchar);
		printf("\nall simbs: %d\n", glob_data()->c_pos - PROMPT_SIZE + 1);
		my_exit(0);
		args = parse_input(input);
		status = run_command(args);
		i = 0;
		while (args && args[i])
			free(args[i++]);
		free(args);
	}
	return (0);
}

void	term_settings(void)
{
	struct termios	new_settings;

	if ((tcgetattr(0, &(glob_data()->settings))) < 0)
		print_err("Error get terminal settings\n");
	new_settings = glob_data()->settings;
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_lflag &= ~(ICANON | ECHO);
	new_settings.c_lflag |= TOSTOP;
	if ((tcsetattr(0, TCSAFLUSH, &new_settings)) < 0)
		print_err("Error set new terminal settings\n");
	//tputs(tgetstr("RA", 0), 1, stdin_putchar);
}

void	init_glob(void)
{
	struct winsize	window;

	if (ioctl(STDIN, TIOCGWINSZ, &window) < 0)
		my_exit("Cannot detect window size\n");
	cursor_le = tgetstr("le", 0);
	cursor_ri = tgetstr("nd", 0);
	cursor_dw = tgetstr("do", 0);
	cursor_up_ = tgetstr("up", 0);
	glob_data()->c_pos = PROMPT_SIZE + 1;
	glob_data()->max_id = 0;
	glob_data()->cols = window.ws_col;
}

int		main(void)
{
	char			dir[PATH_MAX];
	char			*temp;

	if (!isatty(STDIN))
		print_err("STDIN is not terminal\n");
	temp = getenv("TERM");
	if (tgetent(0, temp) <= 0)
		print_err("Could not access the termcap data base or term type is not defiend\n");
	term_settings();
	signal(SIGINT, signal_hendl);
	signal(SIGWINCH, resize);
	get_copy_env();
	if ((temp = ft_strjoin(getcwd(dir, PATH_MAX), "/21.sh")))
	{
		change_env_var("SHELL=", temp);
		free(temp);
	}
	init_glob();
	return (main_loop());
}
