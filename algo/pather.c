/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pather.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:44:27 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/29 17:24:18 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


/*
** Разрываем связи по условию для всех комнат
*/
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

void		connect_two_rooms(t_room *r1, t_room *r2)
{
	t_lst *l;

	l = r1->tubes;
	while (l)
	{
		if (other_room(l->cont, r1) == r2)
		{
			((t_tube *)l->cont)->status = 1;
			break ;
		}
		l = l->nxt;
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

/*
** если комната образует собой туннель идём дальше
*/
void	move_nxt(t_room *frst, t_room *end, t_tube *tfr)
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
			del_links(tfr);
			frst = cpy;
		}
		frst = frst->next;
	}
}

/*
** уничтожает way;
*/
void	destroy_path(t_room *r)
{
	int 	fl;
	t_lst	*l;
	t_room	*from;
	int		path;

	fl = 1;
	path = r->path;
	r->parent = NULL;
	r->path = -1;
	while (fl)
	{
		fl = 0;
		l = r->tubes;
		while (l)
		{
			if ((from = (other_room(l->cont, r)))->path == path)
			{
				((t_tube *)l->cont)->status = -1;
				r->parent = NULL;
				r->path = -1;
				fl = 1;
				from->parent = NULL;
				from->path = -1;
				r = from;
				break ;
			}
			l = l->nxt;
		}
	}

}

/*
** собираем маршруты в массивы
*/

void	make_path(t_cont *c)
{
	t_lst	*l;
	t_room	*r;
	size_t	i;
	t_rooms	*rms;
//утечка при замене паса строка 149 фт аррей
	l = c->start->tubes;
	i = -1;
	c->paths = ft_array(1);
	while (l)
	{
		if (((r = other_room(((t_tube *)l->cont), c->start))->parent != c->start && r->parent && r->path > -1) || r == c->end)
		{
			rms = ft_array(10);
			//r = other_room(l->cont, c->end);
			ft_array_push(rms, c->start);
			while (r != c->end)
			{
				ft_array_push(rms, r);
				r = r->parent;
			}
			ft_array_push(rms, c->end);
			ft_array_push(c->paths, rms);
		}
		else if (r->path != -1)
			destroy_path(other_room(((t_tube *)l->cont), c->start));
		l = l->nxt;
	}
}

void	after_makepath(t_cont *c)
{
	t_lst	*l1;
	t_lst	*l2;
	t_room	*r1;
	int		f;

	l1 = c->end->tubes;
	while (l1)
	{
		if ((r1 = other_room(l1->cont, c->end))->path < MID && r1->path > -1)
		{
			l2 = c->start->tubes;
			f = 1;
			while (l2)
			{
				if (other_room(l2->cont, c->start)->path == r1->path)
				{
					f = 0;
					break ;
				}
				l2 = l2->nxt;
			}
			if (f)
				destroy_path(r1);
		}
		l1 = l1->nxt;
	}
}

/*
** связываем путь со старта и конца
** разворачивая родительскую связь
** фром - комната с концевого маршрута
** r - комната с начала
*/

void	set_connection(t_room *r, t_room *from, int path)
{
	t_room	*rf;

	while (r->parent)
	{
		rf = r->parent;
		r->parent = from;
		from = r;
		r->path = path;
		r = rf;
	}
}

/*
** удаляем линки между комнатами разных путей
** и когда можем связвыаем пути со старта и конца
*/

void	del_links_mod(t_tube *frst)
{
	while (frst)
	{
		if (frst->status == 0)
		{
			if (((frst->in->path > MID && frst->out->path > MID)
			|| (frst->in->path < MID && frst->out->path < MID))
			&& (frst->in->path != -1 && frst->out->path != -1))
				frst->status = -1;
		}
		frst = frst->next;
	}
}

/*
** строим пути с энжa
*/

void	from_bottom(t_room *end, t_room *start)
{
	t_lst	*l;
	t_tube	*t;
	int		path;
	t_room	*r;

	path = 0x7fffffff;
	l = end->tubes;
	while (l)
	{
		t = l->cont;
		if (!t->status && (r = other_room(t, end))->path == -1 && r != start)
		{		
			r->path = path--;
			r->parent = end;
			t->status = 1;
		}
		else if (!t->status && r->path != -1)
			set_connection(r, end, r->path);
		l = l->nxt;
	}
}

void	room_disconnect(t_room *r)
{
	t_lst	*l;
	t_room	*or;
	t_tube	*t;

	l = r->tubes;
	while (l)
	{
		t = l->cont;
		if (!t->status)
		{
			or = other_room(t, r);
			if (or->path != r->path)
				t->status = -1;
		}
		l = l->nxt;
	}
}

/*
** устанавливает связь если у комнаты со стартового маршрута нет других не деактивированных связей
** r - комната с начала имеющая связь с комнатой с конца
*/
int		make_if_start_one(t_room **r, t_room *frst)
{
	t_lst	*l;
	t_tube	*t;
	t_room	*or;

	l = (*r)->tubes;
	while (l)
	{
		t = l->cont;
		if (t->status == 0)
		{
			or = other_room(t, (*r));
			if (or->path > MID)
			{
				set_connection((*r), or, or->path);
				room_disconnect(or);
				connect_two_rooms(*r, or);
				*r = frst;
				break ;
			}
		}
		l = l->nxt;
	}
	return (0);
}

/*
** устанавливает связь, если у финишного маршрута нет других связей
** (как в функции сверху, лень делать универсальную, да и хуй с ним, пир все равно питух)
*/
int		make_if_end_one(t_room **r, t_room *frst)
{
	t_lst	*l;
	t_tube	*t;
	t_room	*or;

	l = (*r)->tubes;
	while (l)
	{
		t = l->cont;
		if (t->status == 0)
		{
			or = other_room(t, (*r));
			if (or->path < MID && or->path != -1)
			{
				set_connection(or, (*r), (*r)->path);
				room_disconnect(or);
				connect_two_rooms(*r, or);
				*r = frst;
				break ;
			}
		}
		l = l->nxt;
	}
	return (0);
}

int		it_in(t_room *from[SIZE_B], t_room *r)
{
	int i;

	i = -1;
	while (++i < SIZE_B && from[i])
		if (from[i] == r)
			return (1);
	return (0);
}

t_room	**insert(t_room *from[SIZE_B], t_room *r)
{
	int i;

	i = -1;
	while (++i < SIZE_B && from[i])
		;
	if (i < SIZE_B)
		from[i] = r;
	return (from);
}

int		del_last(t_room *from[SIZE_B], int ret)
{
	int	i;

	i = -1;
	while (++i < SIZE_B && from[i])
		;
	from[i - 1] = 0;
	return (ret);
}

int		trash_link_check(t_room *r, t_room **r2, t_room *from[SIZE_B])
{
	t_lst	*l;
	t_tube	*t;
	t_room	*or;
	t_room	*rr;
	
	rr = NULL;
	if (!r2)
		r2 = &rr;
	l = r->tubes;
	while (l)
	{
		t = l->cont;
		if (!t->status)
		{
			if ((or = other_room(t, r))->path == -1)
			{
				if (!it_in(from, or) && trash_link_check(or, r2, insert(from, r)) == 0)
					return (del_last(from, 0));
			}
			else if (or->path != -1 && !it_in(from, or))
			{
				if (!*r2)
					*r2 = or;
				else if (or->path != (*r2)->path)
					return (del_last(from, 0));
			}
		}
		l = l->nxt;
	}
	return (del_last(from, 1));
}

/*
** посчитает, можно ли связывать
*/
int		num_of_links_mod(t_room **r, t_room *frst)
{
	int		rez1;
	int		rez2;
	int		rez0;
	t_lst	*l;
	t_tube	*t;
	t_room	*or;

	l = (*r)->tubes;
	rez0 = 0;
	rez1 = 0;
	rez2 = 0;
	while (l)
	{
		t = (t_tube *)l->cont;
		or = other_room(t, *r);
		if ((*r)->path > -1 && or->path > -1 && (((*r)->path > MID && or->path < MID)
		|| (or->path > MID && (*r)->path < MID)))
				rez2++;
		else if (t->status == 0)
			rez0++;
		else if (t->status == 1)
			rez1++;
		l = l->nxt;
	}
	t_room *from[SIZE_B];
	if (rez0)
		ft_bzero(from, sizeof(t_room *) * 5000);
	if (rez2 && (!rez0 || (trash_link_check(*r, NULL, from))))
	{
		if (rez2 == 1 && rez1 == 1 && MID < (*r)->path)
			return (make_if_end_one(r, frst));
		if (rez2 == 1 && rez1 == 1 && MID > (*r)->path && (*r)->path > -1)
			return (make_if_start_one(r, frst));
	}
	return (rez0 == 1 && rez1 == 1 && !rez2);
}

void	move_nxt_mod(t_cont *c)
{
	t_room	*r;
	t_lst	*l;
	t_room	*or;

	r = c->rooms;
	while (r)
	{
		if (r->path != -1 && r->crossroad && num_of_links_mod(&r, c->rooms))
		{
			l = r->tubes;
			while (((t_tube *)l->cont)->status != 0 || (or = other_room(l->cont, r))
				== r->parent)
				l = l->nxt;
			((t_tube *)l->cont)->status = 1;
			if (or != c->end && or != c->start)
			{
				or->parent = r;
				or->path = r->path;
			}
			del_links_mod(c->tubes);
			r = c->rooms;
		}
		r = r->next;
	}
}

void	before_makepath(t_cont *c)
{
	t_lst	*l1;
	t_lst	*l2;
	t_room	*r1;
	int		f;

	l1 = c->start->tubes;
	while (l1)
	{
		if ((r1 = other_room(l1->cont, c->start))->path < MID && r1->path > -1)
		{
			l2 = c->end->tubes;
			f = 1;
			while (l2)
			{
				if (other_room(l2->cont, c->end)->path == r1->path)
				{
					f = 0;
					break ;
				}
				l2 = l2->nxt;
			}
			if (f)
				destroy_path(r1);
			else
				set_connection(other_room(l2->cont, c->end), c->end, r1->path);
		}
		l1 = l1->nxt;
	}
}

int			hw_num_tube(t_room *r)
{
	int		rez0;
	int		rez1;
	t_lst	*l;

	rez0 = 0;
	rez1 = 0;
	l = r->tubes;
	while (l)
	{
		if (((t_tube *)l->cont)->status == 1)
			rez1++;
		else if (((t_tube *)l->cont)->status == 0)
			rez0++;
		l = l->nxt;
	}
	return (rez1 == 1 && rez0 > 1);
}

int			is_in_path(t_room *r, t_cont *c)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < c->paths->len)
	{
		j = -1;
		while (++j < c->paths->path[i]->len
		&&
		 c->paths->path[i]->room[j] != r)
		;
		if (c->paths->path[i]->room[j] == r)
				break ;
	}
	if (i >= c->paths->len)
		return (0);
	while (++j < c->paths->path[i]->len)
	{
		if (c->paths->path[i]->room[j]->path > MID)
			return (hw_num_tube(c->paths->path[i]->room[j]));
	}
	return (0);
}

int			set_svyaz(t_room *r, t_cont *c)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < c->paths->len)
	{
		j = -1;
		while (++j < c->paths->path[i]->len
			&& c->paths->path[i]->room[j] != r)
			;
		if (c->paths->path[i]->room[j] == r)
			break ;
	}
	while (++j < c->paths->path[i]->len
			&& c->paths->path[i]->room[j]->path < MID)
	{
		connect_two_rooms(c->paths->path[i]->room[j - 1], c->paths->path[i]->room[j]);
		c->paths->path[i]->room[j]->path = c->paths->path[i]->room[j - 1]->path;
		room_disconnect(c->paths->path[i]->room[j - 1]);
		c->paths->path[i]->room[j]->parent = c->paths->path[i]->room[j - 1];
	}
	connect_two_rooms(c->paths->path[i]->room[j - 1], c->paths->path[i]->room[j]);
	set_connection(c->paths->path[i]->room[j - 1], c->paths->path[i]->room[j],c->paths->path[i]->room[j]->path);
	return (1);
}

int hard_way(t_cont *c)
{
	t_room	*r;

	r = c->rooms;
	while (r)
	{
		if (r->path > -1 && r->path < MID && hw_num_tube(r) && r != c->end && r != c->start)
			if (is_in_path(r, c))
				return (set_svyaz(r, c));
		r = r->next;
	}
	return (0);
}

/*
** строим маршрут пуская поток по всем путям сразу и обрывая связи между ними
** сперва со старта
** затем со дна
** в конце обходим от не законченных путей в ширину граф и если получается найти маршрут строим его и возвращаемся к разрыванию лишних связей
** и построению маршрутов
*/

void	path(t_cont *c)
{
	int		path;
	t_lst	*l;
	t_room	*r;
	t_tube	*t;
	int		f;

	path = 0;
	l = c->start->tubes;
	while (l)
	{
		t = l->cont;
		r = other_room(t, c->start);
		if (r == c->end)
			t->status = 1;
		if (((t_tube *)l->cont)->status == 0)
		{
			((t_tube *)l->cont)->status = 1;
			r->parent = c->start;
			r->path = path++;
		}
		l = l->nxt;
	}
	del_links(c->tubes);
	move_nxt(c->rooms, c->end, c->tubes);
	from_bottom(c->end, c->start);
	f = 1;
	while (f)
	{
		del_links_mod(c->tubes);
		move_nxt_mod(c);
		f = hard_way(c);
	}
	before_makepath(c);
	make_path(c);
	after_makepath(c);
}
