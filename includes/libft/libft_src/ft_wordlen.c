/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 04:54:35 by kmurray           #+#    #+#             */
/*   Updated: 2017/01/23 22:43:36 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordlen(char *str, char c)
{
	size_t	count;

	count = 0;
	while (*str && *str != c)
	{
		++str;
		++count;
	}
	return (count);
}
