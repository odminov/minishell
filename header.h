/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 11:49:59 by ahonchar          #+#    #+#             */
/*   Updated: 2018/08/23 11:50:01 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"

int			ft_cd(char **args);/*
int			ft_echo(char **args);
int			ft_setenv(char **args);
int			ft_unsetenv(char **args);
int			ft_env(char **args);*/
int			ft_help(char **args);
int			ft_exit(char **args);
int			num_func(void);
int			ft_env(char **args);
char		**get_copy_env(void);
int			ft_setenv(char **args);
char		*get_env_var(const char *var);