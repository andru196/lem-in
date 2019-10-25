/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pather.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:44:27 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/25 22:34:05 by sfalia-f         ###   ########.fr       */
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

/*
** уничтожает way;
*/
void	destroy_path(t_room *r)
{
	int 	fl;
	t_lst	*l;
	t_room	*from;

	fl = 1;
	while (fl)
	{
		fl = 0;
		l = r->tubes;
		while (l)
		{
			if ((from = (other_room(l->cont, r)))->path == r->path)
			{
				((t_tube *)l->cont)->status = -1;
				r->parent = NULL;
				r->path = -1;
				fl = 1;
				r = from;
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
	size_t 	i;
	t_lst	*l;
	int		f;
	t_room	*r;

	l = c->end->tubes;
	while (l)
	{
		i = -1;
		f = 1;
		r = other_room(l->cont, c->end);
		while (++i < c->paths->len)
		{
			if (c->paths->path[i]->room[c->paths->path[i]->len - 2] == r)
				f = 0;
		}
		if (f)
			destroy_path(r);
		l = l->nxt;
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
		t = l->cont; // много труб со статусом -1
		if (!t->status && (r = other_room(t, end)) != start)
		{
			
			r->path = path--;
			r->parent = end;
			t->status = 1;
		}
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
	}
}

/*
** устанавливает связь если у комнаты со стартового маршрута нет других не деактивированных связей
** r - комната с начала имеющая связь с комнатой с конца
*/
int		make_if_start_one(t_room *r)
{
	t_lst	*l;
	t_tube	*t;
	t_room	*or;

	l = r->tubes;
	while (l)
	{
		t = l->cont;
		if (t->status == 0)
		{
			or = other_room(t, r);
			if (or->path > MID)
			{
				set_connection(r, or, or->path);
				room_disconnect(or);
			}
		}
	}
	return (0);
}

/*
** устанавливает связь, если у финишного маршрута нет других связей
** (как в функции сверху, лень делать универсальную, да и хуй с ним, пир все равно питух)
*/
int		make_if_end_one(t_room *r)
{
	t_lst	*l;
	t_tube	*t;
	t_room	*or;

	l = r->tubes;
	while (l)
	{
		t = l->cont;
		if (t->status == 0)
		{
			or = other_room(t, r);
			if (or->path < MID && or->path != -1)
			{
				set_connection(or, r, or->path);
				room_disconnect(or);
			}
		}
	}
	return (0);
}

/*
** посчитает, можно ли связывать
*/
int		num_of_links_mod(t_room *r)
{
	int		rez1;
	int		rez2;
	int		rez0;
	t_lst	*l;
	t_tube	*t;
	t_room	*or;

	l = r->tubes;
	rez0 = 0;
	rez1 = 0;
	rez2 = 0;
	while (l)
	{
		t = (t_tube *)l->cont;
		or = other_room(t, r);
		if (r->path > -1 && or->path > -1 && ((r->path > MID && or->path < MID)
		|| (or->path > MID && r->path < MID)))
				rez2++;
		if (t->status == 0)
			rez0++;
		else if (t->status == 1)
			rez1++;
		l = l->nxt;
	}
	if (rez2 == 1 && rez1 == 1 && !rez0 && MID < r->path)
		return (make_if_end_one(r));
	if (rez2 == 1 && rez1 == 1 && !rez0 && MID > r->path && r->path > -1)
		return (make_if_start_one(r));
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
		if (r->path != -1 && r->crossroad && num_of_links_mod(r))
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
			l = r->tubes;
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
	move_nxt(c->rooms, c->end);
	from_bottom(c->end, c->start);
	del_links_mod(c->tubes);
	move_nxt_mod(c);
	before_makepath(c);
	make_path(c);
	after_makepath(c);
}
