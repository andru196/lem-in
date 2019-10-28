/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:15:18 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/10/28 21:08:20 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Проверка координат на валидность, переполнение. 0xffffffff - невозможный инт,
** с ним можно сравнивать в случае ошибки.
*/

static long		check_num(char *num)
{
	int		j;

	j = 0;
	while (num[j])
	{
		if (j == 0 && (num[j] == '-' || num[j] == '+'))
			++j;
		if (!(ft_isdigit(num[j])))
			return (0xffffffff);
		++j;
	}
	j = num[0] == '-' || num[0] == '+' ? j - 1 : j;
	if (j > 10)
		return (0xffffffff);
	if (j == 10)
		if ((num[0] != '-' && ft_strcmp("2147483647", num) < 0)
			|| (num[0] == '-' && ft_strcmp("-2147483648", num) < 0))
			return (0xffffffff);
	return (ft_atoi(num));
}

/*
** Если это стартовая/конечна комнаты, записываем в контейнер.
*/

static void		add_to(int *flag, t_room *new, t_cont *cont)
{
	if (cont->rooms)
		room_to_end(cont->rooms, new);
	else
		cont->rooms = new;
	if (*flag)
	{
		if (*flag == 1)
			cont->start = new;
		else if (*flag == -1)
			cont->end = new;
		*flag = 0;
	}
}

void			validate_rooms(char **splt, int *flag, t_cont *c, char *l)
{
	t_room		*new;
	t_room		*tmp;
	long		x;
	long		y;

	tmp = c->rooms;
	if ((x = (check_num(splt[1]))) == 0xffffffff ||
							(y = (check_num(splt[2]))) == 0xffffffff)
		print_error_here(c->bonus & err ? ERR_INV_COORD : ERR, c, l, splt);
	if (splt[0][0] == 'L' || ft_charinstr((const char *)splt[0], '-'))
		print_error_here(c->bonus & err ? ERR_INV_NAME : ERR, c, l, splt);
	if (tmp)
		while (tmp)
		{
			if (ft_strequ(splt[0], tmp->name))
				print_error_here(c->bonus & err ? ERR_NAME : ERR, c, l, splt);
			else if (tmp->x == x && tmp->y == y)
				print_error_here(c->bonus & err ? ERR_COORD : ERR, c, l, splt);
			tmp = tmp->next;
		}
	if (!(new = newroom(ft_strdup(splt[0]), x, y)))
		print_error_here(c->bonus & err ? ERR_MAL : ERR, c, l, splt);
	add_to(flag, new, c);
}
