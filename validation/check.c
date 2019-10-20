/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:31:43 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/10/20 18:14:01 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		count_tubes(t_cont *cont)
{
	int		rez;
	t_tube	*tmp;

	rez = 0;
	tmp = cont->tubes;
	while (tmp)
	{
		rez++;
		tmp = tmp->next;
	}
	return (rez);
}

static int		count_rooms(t_cont *cont)
{
	int		rez;
	t_room	*tmp;

	rez = 0;
	tmp = cont->rooms;
	while (tmp)
	{
		rez++;
		tmp = tmp->next;
	}
	return (rez);
}

static void		ant_initialize(t_cont *cont)
{
	size_t i;

	i = 0;
	cont->ants = (t_ant *)malloc(sizeof(t_ant) * cont->num_of_ants);
	while (i < cont->num_of_ants)
	{
		cont->ants[i].num = i + 1;
		cont->ants[i].cur_pos = cont->start;
		i++;
	}
}

/*
** Финальная проверка: считаются значения для контейнера:
** комнта, трубы. Проверяется, что есть путь от старта до финиша.
*/

void			check_data(t_cont *cont)
{
	t_lst	*tmp;

	cont->num_of_rooms = count_rooms(cont);
	cont->num_of_tubes = count_tubes(cont);
	if (!cont->num_of_rooms || !cont->num_of_tubes)
		print_error("ERROR: INVALID MAP");
	tmp = cont->end->tubes;
	ant_initialize(cont);
}
