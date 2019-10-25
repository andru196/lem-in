/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solover0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:35:18 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/25 21:07:01 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		summator(int *arr, int targ)
{
	int	i;
	int rez;

	i = 0;
	rez = 0;
	while (i < targ)
	{
		rez += arr[targ] - arr[i];
		i++;
	}
	return (rez);
}

int				num_check(t_room *dest, int *dists, t_cont *c)
{
	int		path;
	int		i;

	if (dest == c->end)
		return (1);
	path = dest->path_to_end;
	i = 0;
	while (dists[i] != path + 1)
		i++;
	return ((int)c->num_of_ants - c->start->reg > summator(dists, i));
}

void			end_turn(t_tube *frst)
{
	while (frst)
	{
		frst->ant = NULL;
		frst = frst->next;
	}
}

void			print_move(t_ant *ant, t_room *dest, int flag)
{
	if (flag)
		ft_putendl("");
	else
	{
		ft_putchar('L');
		ft_putnbr(ant->num);
		ft_putchar('-');
		ft_putstr(dest->name);
		ft_putchar(' ');
	}
}
