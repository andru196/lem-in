/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 21:31:07 by andru196          #+#    #+#             */
/*   Updated: 2019/10/20 19:58:51 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	t_cont cont;

	cont_initialize(&cont);
	read_data(&cont);
	cont.end->mark |= end;
	cont.start->mark |= start;
	deadlock_detect(&cont);
	bfs(&cont);
	tunnels(&cont);
	path(&cont);
	solover(&cont);
	free_cont(&cont);
	return (0);
}
