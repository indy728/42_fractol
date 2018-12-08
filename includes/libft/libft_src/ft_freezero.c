/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freezero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 17:12:33 by kmurray           #+#    #+#             */
/*   Updated: 2017/03/22 19:16:23 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freezero(void *mem, size_t size)
{
	if (mem)
	{
		ft_bzero(mem, size);
		ft_memdel(&mem);
	}
}