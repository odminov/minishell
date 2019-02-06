/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:10:09 by ahonchar          #+#    #+#             */
/*   Updated: 2018/09/16 17:45:49 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "header.h"
#include <limits.h>

#define ENV_CP glob_data()->g_env_cp

char	check_esc_sequ(char c)
{
	if (c == 'a')
		c = '\a';
	else if (c == 'b')
		c = '\b';
	else if (c == 'f')
		c = '\f';
	else if (c == 'n')
		c = '\n';
	else if (c == 'r')
		c = '\r';
	else if (c == 't')
		c = '\t';
	else if (c == 'v')
		c = '\v';
	return (c);
}

void	parse_double_quotes(t_inpt **list, char *dst, int *symb)
{
	int		i;
	int		j;
	char	*temp;
	char	name[2048];

	i = 0;
	while ((*list)->c)
	{
		j = 0;
		if (!(*list)->prev && (*list)->c == glob_data()->quotes)
			break ;
		else if ((*list)->prev && (*list)->prev->c != '\\' && (*list)->c == glob_data()->quotes)
			break ;
		if ((*list)->c == '\\' && (*list)->next->c)
		{
			(*list) = (*list)->next;
			(*list)->c = check_esc_sequ((*list)->c);
		}
		if ((*list)->c == '$' && (*list)->prev && (*list)->prev->c != '\\' && (*list)->next->c && (*list)->next->c != ' ')
		{
			while ((*list)->c && !ft_iswhite_sp((*list)->c) && (*list)->c != glob_data()->quotes)
			{
				name[j++] = (*list)->c;
				(*list) = (*list)->next;
			}
			temp = get_env_var(name);
			j = ft_strlen(temp);
		}
		if (dst)
		{
			while (temp && *temp)
				dst[i++] = *temp++;
			dst[i++] = (*list)->c;
		}
		if (symb)
			*symb = (j) ? *symb + j : *symb + 1;
		if ((*list)->c == glob_data()->quotes)
			break ;
		if ((*list)->c)
			(*list) = (*list)->next;
	}
}

void	parse_single_quotes(t_inpt **list, char *dst, int *symb)
{
	int		i;

	i = 0;
	while ((*list)->c)
	{
		if (!(*list)->prev && (*list)->c == glob_data()->quotes)
			break ;
		else if ((*list)->prev && (*list)->prev->c != '\\' && (*list)->c == glob_data()->quotes)
			break ;
		if ((*list)->c == '\\' && (*list)->next->c)
		{
			(*list) = (*list)->next;
			(*list)->c = check_esc_sequ((*list)->c);
		}
		if (dst)
			dst[i++] = (*list)->c;
		if (symb)
			(*symb)++;
		if ((*list)->c)
			(*list) = (*list)->next;
	}
}


static int	parse_quotes(t_inpt **list, char *dst, int *symb)
{
	glob_data()->quotes = (*list)->c;
	(*list) = (*list)->next;
	if (glob_data()->quotes == '\"')
		parse_double_quotes(list, dst, symb);
	else
		parse_single_quotes(list, dst, symb);
	if ((*list)->c == glob_data()->quotes)
	{
		(*list) = (*list)->next;
		glob_data()->quotes = 0;
	}
	else
		return (0);
	return (1);
}

static int	count_words(t_inpt *list)
{
	int	wd;

	wd = 0;
	while (list->c)
	{
		if (list->c && !ft_iswhite_sp(list->c))
		{
			wd++;
			if (list->c == '\"' || list->c == '\'')
			{
				if (!parse_quotes(&list, NULL, NULL))
					return (wd);
			}
			else if (list->c == '\\' && list->next->c)
				list = list->next;
			else
				while (list->c && !ft_iswhite_sp(list->c))
					list = list->next;
		}
		while (list->c && ft_iswhite_sp(list->c))
			list = list->next;
		if (list->c)
			list = list->next;
	}
	return (wd);
}

static int	count_symb(t_inpt **temp)
{
	t_inpt		*list;
	static int	all_symb;
	static int	old_val;

	old_val = all_symb;
	list = *temp;
	while (list->c && ft_iswhite_sp(list->c))
		list = list->next;
	while (list->c && !ft_iswhite_sp(list->c))
	{
		all_symb++;
		if (list->c == '\"' || list->c == '\'')
		{
			if (!parse_quotes(&list, NULL, &all_symb))
				return (all_symb - old_val);
		}
		if (list->c == '\\' && list->next->c)
			list = list->next;
		if (list->c)
		list = list->next;
	}
	*temp = list;
	return (all_symb - old_val);
}

char		**parse_input(t_inpt *list)
{
	t_inpt	*copy;
	char	**res;
	int		wd;
	int		i;
	int		t;

	if (!(copy = list))
		return (NULL);
	glob_data()->quotes = 0;
	wd = count_words(list);
	if (!(res = (char **)malloc(wd * (sizeof(char *) + 1))))
		return (NULL);	
	printf("wd: %d\n", wd);
	res[wd] = NULL;
	i = 0;
	while (i < wd)
	{
		t = count_symb(&list);
		if (!(res[i] = (char *)malloc(t + 1)))
			return (NULL);
		printf("ret[%d] = malloc(%d + 1)\n", i, t);
		i++;
	}
	exit(1);
	return (NULL);
//	return (copy_result(copy));
}
