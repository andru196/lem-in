/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solover.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:43:06 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/25 20:42:34 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		isnotready(t_ant *ants, int a_num, t_room *finish)
{
	while (a_num--)
	{
		if (ants[a_num].cur_pos != finish)
			return (1);
	}
	return (0);
}

static void		get_move(t_ant *ant, t_room *dest)
{
	t_tube	*t;
	t_lst	*lst;

	lst = ant->cur_pos->tubes;
	while (lst)
	{
		t = lst->cont;
		if (t->ant == ant)
			t->ant = NULL;
		if (other_room(t, ant->cur_pos) == dest)
			t->ant = ant;
		lst = lst->nxt;
	}
	ant->cur_pos->ant = NULL;
	ant->cur_pos->reg++;
	dest->ant = ant;
	ant->cur_pos = dest;
	print_move(ant, dest, 0);
}

void			path_lem(t_paths *paths)
{
	size_t	i;
	size_t	j;
	size_t	lentofin;

	i = -1;
	while (++i < paths->len)
	{
		j = 0;
		lentofin = paths->path[i]->len - 1;
		while (++j < paths->path[i]->len - 1)
		{
			paths->path[i]->room[j]->path = i;
			paths->path[i]->room[j]->path_to_end = --lentofin;
		}
	}
}

static int		*paths_len(t_paths *paths)
{
	size_t	i;
	int		*rez;
	int		flag;

	i = -1;
	rez = ft_memalloc(SIZE(int, paths->len));
	while (++i < paths->len)
		rez[i] = paths->path[i]->len - 1;
	flag = 1;
	while (flag)
	{
		i = -1;
		flag = 0;
		while (++i < paths->len - 1)
		{
			if (rez[i] > rez[i + 1])
			{
				flag = 1;
				rez[i] += rez[i + 1];
				rez[i + 1] = rez[i] - rez[i + 1];
				rez[i] -= rez[i + 1];
			}
		}
	}
	return (rez);
}

void			solover(t_cont *c)
{
	int		i;
	t_room	*dest;
	t_ant	*ant;
	int		*hh;

	path_lem(c->paths);
	hh = paths_len(c->paths);
	while (isnotready(c->ants, c->num_of_ants, c->end))
	{
		i = -1;
		while (++i < (int)c->num_of_ants)
		{
			ant = &c->ants[i];
			if (ant->cur_pos != c->end)
			{
				dest = room_selector(ant, c->start);
				if (dest && (ant->cur_pos != c->start ||
				num_check(dest, hh, c)))
					get_move(ant, dest);
			}
		}
		print_move(NULL, NULL, 1);
		end_turn(c->tubes);
	}
	free(hh);
}
