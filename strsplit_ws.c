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
//
#include <stdio.h>
static int	parse_quotes(char **str, int *words)
{
	if (**str && **str == '"')
	{
		(*str)++;
		if (**str && **str == '"')
		{
			(*str)++;
			return (0);
		}
		if (!**str)
			return (0);
		while (**str && **str != '"')
			(*str)++;
		(*words)++;
		if (**str && **str != '"')
			(*str)++;
	}
	return (1);
}

static int	count_words(char *str)
{
	int words;
	int	in_word;

	words = 0;
	in_word = 0;
	while (*str)
	{
		while (*str && !ft_iswhite_sp(*str) && *str != '"')
		{
			in_word = 1;
			str++;
		}
		if (in_word)
			words++;
		in_word = 0;
		if (!parse_quotes(&str, &words))
			continue ;
		if (*str)
			str++;
	}
	return (words);
}

static int	count_simb(char **str)
{
	int		i;
	int		spaces;

	i = 0;
	while (**str && ft_iswhite_sp(**str) && ++i)
		(*str)++;
	spaces = i;
	if (**str && **str == '"')
	{
		(*str)++;
		while (**str && **str != '"')
		{
			(*str)++;
			i++;
		}
		if (**str && **str == '"')
			(*str)++;
	}
	else
		while (**str && !ft_iswhite_sp(**str) && **str != '"')
		{
			i++;
			(*str)++;
		}
	return (i - spaces);
}

static char	**copy_to_arr(char *str, char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (*str)
	{
		j = 0;
		while (*str && ft_iswhite_sp(*str))
			str++;
		if (*str && *str == '"' && str++)
			while (*str && *str != '"')
				arr[i][j++] = *str++;
		else
		{
			while (*str && !ft_iswhite_sp(*str) && *str != '"')
				arr[i][j++] = *str++;
			if (*str && *str == '"')
				str--;
		}
		if (j)
	    	arr[i][j] = '\0';
		if (*str)
        {
            str++;
            i = j ? i + 1 : i;
        }

	}
	return (arr);
}

char		**strsplit_ws(char *str)
{
	int		i;
	int		wd;
	char	**res;
	char	*copy;
	int temp;

	if (!str)
		return (NULL);
	wd = count_words(str);
	if (!wd)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * wd + 1);
	i = 0;
	copy = (char *)str;
	while (i < wd) {
        temp = count_simb(&copy);
        if (temp)
            res[i++] = (char *) malloc(temp + 1);
    }
	res[i] = NULL;
	return (copy_to_arr(str, res));
}
