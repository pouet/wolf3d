/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 09:56:03 by nchrupal          #+#    #+#             */
/*   Updated: 2015/12/02 08:55:48 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (*s2 == '\0')
		return (1);
	while (n > 0 && *s1 && *s1 == *s2)
	{
		n--;
		s1++;
		s2++;
	}
	return (n == 0 || *s1 == *s2);
}