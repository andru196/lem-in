/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:58:45 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/20 17:26:56 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int8_t	check_alt(t_room *to)
{
	t_lst	*l;
	t_tube	*t;
	t_room	*other;
	t_room	*r;

	l = to->tubes;
	r = 0;
	while (l)
	{
		t = l->cont;
		other = other_room(t, to);
		if (other->mark & start)
			return (0);
		if (other->path == to->path && (!r
		|| r->path_to_end < other->path_to_end))
			r = other;
		l = l->nxt;
	}
	return (r->ant == NULL);
}

t_room			*room_selector(t_ant *ant, t_room *start)
{
	t_room	*r[3];
	t_tube	*t[2];
	t_lst	*lst;

	r[0] = NULL;
	r[1] = ant->cur_pos;
	lst = r[1]->tubes;
	while (lst)
	{
		t[1] = (t_tube *)lst->cont;
		r[2] = other_room(t[1], r[1]);
		if (!t[1]->ant && r[2]->mark & end)
			return (r[2]);
		if (!t[1]->ant && !r[2]->ant && r[2]->path != -1 &&
		(r[1] == start || r[1]->path_to_end > r[2]->path_to_end))
		{
			if ((r[1] == start && r[2]->path != -1 && (!r[0] ||
			r[0]->path_to_end > r[2]->path_to_end)) || (r[1] != start
			&& (r[2]->path == r[1]->path || check_alt(r[2]))))
				r[0] = r[2];
		}
		lst = lst->nxt;
	}
	return (r[0]);
}
