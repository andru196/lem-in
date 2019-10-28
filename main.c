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
/*
 TODO:
    где-то печатется еррор инвалид мэп
    сега биг мап 4 maps/valid/big/map_big_4
*/
 void            flags(char **argv, t_cont *cont)
{
    int            i;
    const char    *usage = "usage: ./lem-in [-l] [-q] [-s] [-e] [-h|--help]";
    const char    *h = "l - show leaks\nq - do not show map\ns - show statistics\n\
    e - show errors\nh|help - shows this message";
    
    i = 1;
    while (argv[i])
    {
        if (ft_strequ(argv[i], "-l"))
            cont->bonus |= leaks;
        else if (ft_strequ(argv[i], "-q"))
            cont->bonus |= quiet;
        else if (ft_strequ(argv[i], "-s"))
            cont->bonus |= stat;
        else if (ft_strequ(argv[i], "-e"))
            cont->bonus |= err;
        else if (ft_strequ(argv[i], "-h") || ft_strequ(argv[i], "--help"))
        {
            ft_putendl(usage);
            print_error((char *)h, cont);
        }
        else
        {
            ft_printf("lem-in: wrong flag -- %s\n", argv[i]);
            print_error((char *)usage, cont);
        }
        ++i;
    }
}

void	drop_parent(t_room *frst)
{
	while (frst)
	{
		frst->parent = NULL;
		frst = frst->next;
	}
}

int		main(int argc, char **argv)
{
	t_cont cont;

	cont_initialize(&cont);
    if (argc > 1)
        flags(argv, &cont);
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
    if (cont.bonus & stat)
    {
        ft_printf("\n{blue}Statistic for this map:\n{eoc}Ants: %d\nRooms:\
                  %d\nPaths: %d\nSteps: %d\n",\
                  cont.num_of_ants, cont.num_of_rooms, cont.paths->len, cont.steps);
    }
	free_cont(&cont);
    if (cont.bonus & leaks)
        system("leaks -q lem-in");
	return (0);
}
