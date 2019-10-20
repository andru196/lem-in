/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tubes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:23:04 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/10/20 18:11:57 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char			*rooms_exists(t_cont *cont)
{
	if (!(cont->start))
		return ("ERROR: NO START ROOM");
	else if (!(cont->end))
		return ("ERROR: NO END ROOM");
	return (NULL);
}

static t_room		*find_room(t_cont *cont, char **split, int n)
{
	t_room	*r;

	r = cont->rooms;
	while (r)
	{
		if (ft_strequ(split[n], r->name))
			break ;
		r = r->next;
	}
	if (!r)
	{
		frees_split(split);
		print_error("ERROR: ROOM NAME DOESN'T EXISTS");
	}
	return (r);
}

static void			add_to(t_cont *cont, char **split, t_room *r1, t_room *r2)
{
	int		flag;
	t_tube	*t;
	t_tube	*new;

	r1 = find_room(cont, split, 0);
	r2 = find_room(cont, split, 1);
	t = cont->tubes;
	flag = 0;
	if (t)
	{
		while (t)
		{
			if ((t->in == r1 && t->out == r2) || (t->in == r2 && t->out == r1))
				flag = 1;
			t = t->next;
		}
	}
	if (!flag)
	{
		new = newtube(r1, r2);
		if (cont->tubes)
			tube_to_end(cont->tubes, new);
		else
			cont->tubes = new;
	}
}

void				validate_tubes(char **split, t_cont *cont)
{
	char	*error;
	t_room	*r1;
	t_room	*r2;

	if ((error = rooms_exists(cont)))
	{
		frees_split(split);
		print_error(error);
	}
	r1 = NULL;
	r2 = NULL;
	add_to(cont, split, r1, r2);
}
