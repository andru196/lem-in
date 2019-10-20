/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:43:52 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/20 17:28:56 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** тихонечко сносим тупики
*/

static void	kill_deadlock(t_room *room)
{
	int		n;
	t_lst	*l;
	t_lst	*l2;
	t_room	*r;

	if (room->mark & (deadlock | start | end))
		return ;
	room->mark |= deadlock;
	l = room->tubes;
	while (l)
	{
		((t_tube *)(l->cont))->status = -1;
		r = other_room(l->cont, room);
		n = 0;
		if (!(r->mark & (deadlock | end | start)) && (l2 = r->tubes))
			while (l2)
			{
				if ((((t_tube *)l2->cont))->status != -1)
					n++;
				l2 = l2->nxt;
			}
		if (n < 2)
			kill_deadlock(r);
		l = l->nxt;
	}
}

void		deadlock_detect(t_cont *c)
{
	t_room *cpy;

	cpy = c->rooms;
	while (cpy)
	{
		if (cpy->tubes_len < 2 && !(cpy->mark & (deadlock | start | end)))
			kill_deadlock(cpy);
		cpy = cpy->next;
	}
}
