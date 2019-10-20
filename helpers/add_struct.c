/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:37:35 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/20 17:31:40 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_tube(t_room *dist, t_tube *what)
{
	t_lst *lst;
	t_lst *cpy;

	if (dist)
	{
		if ((lst = newlst(what)))
		{
			if (!dist->tubes)
				dist->tubes = lst;
			else
			{
				cpy = dist->tubes;
				while (cpy->nxt)
					cpy = cpy->nxt;
				cpy->nxt = lst;
			}
		}
		else
			exit(1);
	}
}

void	room_to_end(t_room *start, t_room *new)
{
	t_room *tmp;

	tmp = start;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	tube_to_end(t_tube *start, t_tube *new)
{
	t_tube *tmp;

	tmp = start;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
