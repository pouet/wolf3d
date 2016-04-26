/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_quit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 14:37:37 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 14:40:48 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_QUIT_H
# define INIT_QUIT_H

# include "wolf3d.h"

int		init_video(t_cont *cont);
void	quit_video(t_cont *cont);
void	init_var(t_cont *cont);

#endif
