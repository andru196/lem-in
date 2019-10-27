/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 22:07:47 by andru196          #+#    #+#             */
/*   Updated: 2019/10/27 18:00:40 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*other_room(t_tube *t, t_room *current)
{
	return (t->in == current ? t->out : t->in);
}

void	swap_rooms(t_tube *tube)
{
	t_room *tmp;

	tmp = tube->in;
	tube->in = tube->out;
	tube->out = tmp;
}

int		num_of_tubes(t_tube *frst, int status)
{
	int rez;

	rez = 0;
	while (frst)
	{
		if (frst->status == status)
			rez++;
		frst = frst->next;
	}
	return (rez);
}

int		num_of_rooms(t_room *frst, int path)
{
	int	rez;

	rez = 0;
	while (frst)
	{
		if (frst->path == path)
			rez++;
		frst = frst->next;
	}
	return (rez);
}