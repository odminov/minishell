/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 19:43:31 by ahonchar          #+#    #+#             */
/*   Updated: 2018/08/27 19:43:32 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdlib.h>

int		main(void)
{
	char **arr;
	char *line = {"asdas das djas dasd"};
	int i;

	arr = ft_strsplit(line, ' ');
	i = 0;
	while (arr[i])
		ft_printf("%s\n", arr[i++]);
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
	system("leaks -quiet test");
	return (0);
}