/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:07:06 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/20 17:30:42 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ant	*newant(int num, t_room *start)
{
	t_ant *rez;

	rez = (t_ant *)malloc(sizeof(t_ant));
	if (rez)
	{
		rez->cur_pos = start;
		rez->num = num;
	}
	return (rez);
}

t_room	*newroom(char *name, int x, int y)
{
	t_room *rez;

	rez = (t_room *)ft_memalloc(sizeof(t_room));
	if (rez)
	{
		rez->x = x;
		rez->y = y;
		rez->name = name;
		rez->path = -1;
		rez->path_to_end = -1;
	}
	return (rez);
}

t_tube	*newtube(t_room *r1, t_room *r2)
{
	t_tube	*rez;

	rez = (t_tube *)ft_memalloc(sizeof(t_tube));
	if (rez)
	{
		rez->in = r1;
		add_tube(r1, rez);
		r1->tubes_len++;
		rez->out = r2;
		add_tube(r2, rez);
		r2->tubes_len++;
		rez->ant = NULL;
		rez->lenth = -1;
		rez->status = 0;
		rez->next = NULL;
		rez->p_len = -1;
	}
	return (rez);
}

t_lst	*newlst(void *cont)
{
	t_lst	*rez;

	rez = (t_lst *)malloc(sizeof(t_lst));
	if (rez)
	{
		rez->nxt = NULL;
		rez->cont = cont;
	}
	return (rez);
}
