/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 16:02:05 by ahonchar          #+#    #+#             */
/*   Updated: 2018/08/23 17:45:54 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	g_glob;

int	main(void)
{
	int			i;
	static int	arr[] = {12, 12, 32, 23, 23, 23, 23, 23, 23, 23};

	i = 0;
	glob = 1;
	while (i < sizeof(arr) / sizeof(int))
		printf("%d, ", arr[i++]);
	printf("\n");
	return (0);
}
