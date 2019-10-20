/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 22:07:47 by andru196          #+#    #+#             */
/*   Updated: 2019/10/11 15:32:04 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*other_room(t_tube *t, t_room *current)
{
	return (t->in == current ? t->out : t->in);
}

void	swap_rooms(t_tube *tube)
{
	t_room *tmp;

	tmp = tube->in;
	tube->in = tube->out;
	tube->out = tmp;
}
