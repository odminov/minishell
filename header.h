/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 11:49:59 by ahonchar          #+#    #+#             */
/*   Updated: 2018/09/16 17:44:55 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "./libft/libft.h"
# include <term.h>
# include <termcap.h>
# define STDIN 0
# define STDERR 2

# define K_DOWN		4345627
# define K_DOWN_I	4348699
# define K_UP		4280091
# define K_UP_I		4283163
# define K_LEFT		4476699
# define K_LEFT_I	4479771
# define K_RIGHT	4411163
# define K_RIGHT_I	4414235
# define K_BACK_SP	127
# define K_DEL		2117294875
# define K_ENTER	10
# define K_SPACE	32
# define K_ESC		27

typedef struct	s_inpt
{
	struct	s_inpt	*prev;
	struct	s_inpt	*next;
	char	c;
}				t_inpt;

typedef struct		s_glob
{
	struct termios	settings;
	char			**g_env_cp;
	char			quotes;
	int				c_pos;
	int				max_id;
	volatile int	cols;
}					t_glob;

t_glob		*glob_data(void);
int			ft_cd(char **args);
int			ft_echo(char **args);
int			ft_setenv(char **args);
int			ft_unsetenv(char **args);
int			ft_env(char **args);
int			ft_help(char **args);
int			ft_exit(char **args);
int			ft_pwd(char **args);
int			num_func(void);
char		**get_copy_env(void);
int			ft_setenv(char **args);
char		*get_env_var(const char *var);
int			change_env_var(const char *var, const char *value);
char		*find_var(char *str, const char *name);
char		*find_command(char **args);
int			print_error(const char *error1, const char *error2);
void		signal_hendl_waitpid(int signal);
void		signal_hendl(int signal);
char		**parse_input(t_inpt *list);
int			print_env(void);
int			run_command(char **args);
int			check_perm(char **args);

#endif
