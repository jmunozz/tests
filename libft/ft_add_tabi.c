/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 19:46:15 by jmunoz            #+#    #+#             */
/*   Updated: 2016/09/08 18:52:12 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

int		*ft_add_tabi(int *tab, int size_tab)
{
	int	*new_tab;

	if (!(new_tab = (int*)malloc(sizeof(int) * (size_tab + 1))))
		return (0);
	new_tab[size_tab] = 0;
	if (size_tab == 1)
		return (new_tab);
	size_tab -= 2;
	while (size_tab >= 0)
	{
		new_tab[size_tab] = tab[size_tab];
		size_tab--;
	}
	return (new_tab);
}
