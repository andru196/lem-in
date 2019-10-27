/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pather0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:44:27 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/28 00:43:32 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int8_t	lem_queue(t_rooms *queue, t_room *room, int visit)
{
	size_t	i;
	t_room	*link;

	i = -1;
	while (++i < room->crossroad->len)
	{
		link = room->crossroad->room[i];
		if (link->mark & (end | closed) || link->visit == visit)
			continue;
		link->parent = room;
		if (link->mark & start)
			return (1);
		link->visit = visit;
		ft_array_push(queue, link);
	}
	return (0);
}

static int8_t	lem_bfs(t_cont *c)
{
	static int	bfs = 1;
	size_t		i;
	t_rooms		*queue;

	bfs++;
	queue = ft_array(c->num_of_rooms);
	lem_queue(queue, c->end, bfs);
	i = -1;
	while (++i < queue->len)
		if (lem_queue(queue, queue->room[i], bfs))
			break ;
	ft_array_free(queue);
	if (c->start->parent)
		return (1);
	return (0);
}

static size_t	paths_efficiency(t_cont *c)
{
	size_t	i;
	size_t	steps;
	size_t	ants;

	ants = 0;
	steps = 0;
	while (ants < c->num_of_ants)
	{
		steps++;
		i = -1;
		while (++i < c->paths->len)
			if (c->paths->path[i]->len - 2 < steps)
				ants++;
	}
	return (steps);
}

static void		save_path(t_cont *c)
{
	t_room	*room;
	t_rooms	*path;

	path = ft_array(1);
	room = c->start;
	while (room)
	{
		ft_array_push(path, room);
		if (!(room->mark & (start | end)))
			room->mark |= closed;
		room = room->parent;
	}
	c->start->parent = 0;
	ft_array_push(c->paths, path);
	if (path->room[1]->mark & end)
		start_end_exception(c);
}

void			pre_path(t_cont *c)
{
	size_t	efficiency;

	c->efficiency = -1;
	c->paths = ft_array(1);
	while (lem_bfs(c))
	{
		save_path(c);
		if (c->efficiency > (efficiency = paths_efficiency(c)))
			c->efficiency = efficiency;
		else
		{
			c->paths->len--;
			break ;
		}
	}
}
