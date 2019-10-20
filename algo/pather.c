/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pather.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:44:27 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/20 19:58:09 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_links(t_tube *frst)
{
	while (frst)
	{
		if (frst->status == 0)
		{
			if (frst->in->path != -1 && frst->out->path != -1)
				frst->status = -1;
		}
		frst = frst->next;
	}
}

int		num_of_links(t_room *r)
{
	int		rez1;
	int		rez0;
	t_lst	*l;

	l = r->tubes;
	rez0 = 0;
	rez1 = 0;
	while (l)
	{
		if (((t_tube *)l->cont)->status == 0)
			rez0++;
		else if (((t_tube *)l->cont)->status == 1)
			rez1++;
		l = l->nxt;
	}
	return (rez0 == 1 && rez1 == 1);
}

void	move_nxt(t_room *frst, t_room *end)
{
	t_lst	*l;
	t_room	*r;
	t_room	*cpy;

	cpy = frst;
	while (frst)
	{
		if (frst->crossroad && frst->path != -1 && num_of_links(frst) && frst != end)
		{
			l = frst->tubes;
			while (((t_tube *)l->cont)->status != 0 || (r = other_room(l->cont, frst))
				== frst->parent)
				l = l->nxt;
			((t_tube *)l->cont)->status = 1;
			if (r != end)
			{
				r->parent = frst;
				r->path = frst->path;
			}
			del_links(l->cont);
			frst = cpy;
		}
		frst = frst->next;
	}
}

void	make_path(t_cont *c)
{
	t_lst	*l;
	t_room	*r;
	size_t	i;
	t_rooms	*rms;

	l = c->end->tubes;
	i = -1;
	c->paths = ft_array(1);
	while (l)
	{
		if (other_room(((t_tube *)l->cont), c->end)->path != -1)
		{
			rms = ft_array(1);
			r = other_room(l->cont, c->end);
			ft_array_push(rms, c->end);
			while (r != c->start)
			{
				ft_array_push(rms, r);
				r = r->parent;
			}
			ft_array_push(rms, c->start);
			ft_array_push(c->paths, rms);
		}
		l = l->nxt;
	}
}

void	path(t_cont *c)
{
	int		path;
	t_lst	*l;
	t_room	*r;
	t_tube	*t;
	//int		f;

	path = 0;
	l = c->start->tubes;
	while (l)
	{
		t = l->cont;
		r = other_room(t, c->start);
		r->parent = c->start;
		r->path = path++;
		((t_tube *)l->cont)->status = 1;
		l = l->nxt;
	}
	del_links(c->tubes);
	move_nxt(c->rooms, c->end);
	make_path(c);
}
