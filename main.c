/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 21:31:07 by andru196          #+#    #+#             */
/*   Updated: 2019/10/28 18:10:45 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	drop_parent(t_room *frst)
{
	while (frst)
	{
		frst->parent = NULL;
		frst = frst->next;
	}
}

int		main(void)
{
	t_cont cont;

	cont_initialize(&cont);
	read_data(&cont);
	cont.end->mark |= end;
	cont.start->mark |= start;
	deadlock_detect(&cont);
	bfs(&cont);
	tunnels(&cont);
	pre_path(&cont);
	drop_parent(cont.rooms);
	path(&cont);
	solover(&cont);
	free_cont(&cont);
	return (0);
}
