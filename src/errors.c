/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:29:28 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 12:34:18 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "libft.h"
#include "errors.h"

void	exit_sdlerror(void)
{
	ft_putendl_fd(SDL_GetError(), 2);
	exit(EXIT_FAILURE);
}
