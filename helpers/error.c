/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:32:06 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/20 17:31:08 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_lst(t_lst *f)
{
	t_lst *l;

	l = f;
	while (l)
	{
		f = f->nxt;
		free(l);
		l = f;
	}
}

void	free_tube(t_tube *f)
{
	t_tube *l;

	l = f;
	while (l)
	{
		f = f->next;
		free(l);
		l = f;
	}
}

void	free_room(t_room *f)
{
	t_room *l;

	l = f;
	while (l)
	{
		f = f->next;
		free_lst(l->tubes);
		ft_array_free(l->crossroad);
		free(l->name);
		free(l);
		l = f;
	}
}

void	free_cont(t_cont *cont)
{
	free(cont->ants);
	ft_array_free(cont->paths);
	free_room(cont->rooms);
	free_tube(cont->tubes);
}

void	error_exit(t_cont *c, int code)
{
	if (code == 5)
		ft_printf("Theren't way to finish!");
	free_cont(c);
	exit(1);
}
