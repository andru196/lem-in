/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:15:18 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/10/09 18:05:13 by ycorrupt         ###   ########.fr       */
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

void			validate_rooms(char **split, int *flag, t_cont *cont)
{
	t_room		*new;
	t_room		*tmp;
	long		x;
	long		y;

	tmp = cont->rooms;
	if ((x = (check_num(split[1]))) == 0xffffffff ||
							(y = (check_num(split[2]))) == 0xffffffff)
		print_error("ERROR: INVALID COORDINATE");
	if (split[0][0] == 'L')
		print_error("ERROR: INVALID NAME");
	if (tmp)
		while (tmp)
		{
			if (ft_strequ(split[0], tmp->name))
				print_error("ERROR: ROOM NAME ALREADY EXISTS");
			if (tmp->x == x && tmp->y == y)
				print_error("ERROR: COORDINATES ALREADY OCCUPIED");
			tmp = tmp->next;
		}
	if (!(new = newroom(ft_strdup(split[0]), x, y)))
		print_error("ERROR: MALLOC");
	add_to(flag, new, cont);
}
