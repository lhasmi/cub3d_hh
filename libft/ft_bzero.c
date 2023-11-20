/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 12:58:01 by lhasmi            #+#    #+#             */
/*   Updated: 2022/06/14 17:21:15 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			c;
	unsigned char	*d;

	d = (unsigned char *)s;
	c = 0;
	while (c < n)
	{
		d[c] = '\0';
		c++;
	}
}