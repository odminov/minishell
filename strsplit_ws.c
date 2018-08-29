/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:10:09 by ahonchar          #+#    #+#             */
/*   Updated: 2017/12/16 22:37:41 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdlib.h>

static int	count_words(const char *str)
{
	int		i;
	int		words;
	int		in_word;

	i = 0;
	words = 0;
	in_word = 0;
	while (str[i])
	{
		while (str[i] && !ft_iswhite_sp(str[i]))
		{
			in_word = 1;
			i++;
		}
		if (in_word)
			words++;
		in_word = 0;
		if (str[i])
			i++;
	}
	return (words);
}

static int	count_simb(char **str)
{
	int		i;
	int		spaces;

	i = 0;
	while (**str && ft_iswhite_sp(**str))
	{
		i++;
		(*str)++;
	}
	spaces = i;
	while (**str && !ft_iswhite_sp(**str))
	{
		i++;
		(*str)++;
	}
	return (i - spaces);
}

static char	**copy_to_arr(const char *str, char **arr)
{
	int		i;
	int		wd;

	wd = 0;
	while (*str)
	{
		i = 0;
		while (ft_iswhite_sp(*str))
			str++;
		if (*str && !ft_iswhite_sp(*str))
		{
			while (*str && !ft_iswhite_sp(*str))
				arr[wd][i++] = *str++;
			arr[wd][i] = '\0';
			wd++;
		}
		if (*str)
			str++;
	}
	return (arr);
}

char		**strsplit_ws(const char *str)
{
	int		i;
	int		wd;
	char	**res;
	char	*copy;

	if (!str)
		return (NULL);
	wd = count_words(str);
	res = (char **)malloc(sizeof(char *) * wd + 1);
	i = 0;
	copy = (char *)str;
	while (i < wd)
		res[i++] = (char *)malloc(count_simb(&copy) + 1);
	res[i] = NULL;
	return (copy_to_arr(str, res));
}
