/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:27:47 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/19 23:15:16 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		bfs_queue(t_rooms *queue, t_room *room)
{
	t_room	*r;
	t_lst	*lst;
	t_tube	*t;

	lst = room->tubes;
	while (lst)
	{
		t = lst->cont;
		r = other_room(t, room);
		if (r->mark & (deadlock | start))
		{
			lst = lst->nxt;
			continue;
		}
		if (r->visit != 1)
			ft_array_push(queue, r);
		r->visit = 1;
		if (!r->crossroad)
			r->crossroad = ft_array(room->tubes_len);
		ft_array_push(r->crossroad, room);
		lst = lst->nxt;
	}
}

void			bfs(t_cont *c)
{
	t_rooms	*queue;
	size_t	i;

	queue = ft_array(c->num_of_rooms);
	bfs_queue(queue, c->start);
	i = -1;
	while (++i < queue->len)
		bfs_queue(queue, queue->room[i]);
	ft_array_free(queue);
    if (!c->end->crossroad)
        print_error(c->bonus & err ? ERR_PATH : ERR, c);
    else
        c->bonus & quiet ? ft_isalpha('a') : ft_putendl("");
}

void			tunnels(t_cont *c)
{
	t_room	*r;

	r = c->rooms;
	while (r)
	{
		if (!(r->mark & (start | end)))
			if (r->crossroad && r->crossroad->len < 3)
				r->mark |= tunnel;
		r = r->next;
	}
}
