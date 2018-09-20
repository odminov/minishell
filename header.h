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
# define STDIN 0
# define STDERR 2

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
void		check_dollar(char **args);
int			print_error(const char *error1, const char *error2);
void		signal_hendl_waitpid(int signal);
void		signal_hendl(int signal);
char		**strsplit_ws(const char *str);
int			print_env(void);
int			run_command(char **args);

#endif
