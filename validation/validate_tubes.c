/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tubes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:23:04 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/10/28 21:10:34 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	return (r);
}

static void			add(int flag, t_room *r1, t_room *r2, t_cont *cont)
{
	t_tube	*new;

	if (!flag)
	{
		new = newtube(r1, r2);
		if (cont->tubes)
			tube_to_end(cont->tubes, new);
		else
			cont->tubes = new;
	}
}

static int			add_to(t_cont *cont, char **split, t_room *r1, t_room *r2)
{
	int		flag;
	t_tube	*t;

	if (!(r1 = find_room(cont, split, 0)))
		return (-2);
	if (!(r2 = find_room(cont, split, 1)))
		return (-2);
	if (r1 == r2)
		return (-1);
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
	add(flag, r1, r2, cont);
	return (0);
}

void				validate_tubes(char **split, t_cont *c, char *line)
{
	int		error;
	t_room	*r1;
	t_room	*r2;

	if (!(c->start))
		print_error_here(c->bonus & err ? ERR_START : ERR, c, line, split);
	else if (!(c->end))
		print_error_here(c->bonus & err ? ERR_END : ERR, c, line, split);
	r1 = NULL;
	r2 = NULL;
	error = add_to(c, split, r1, r2);
	if (error == -1)
		print_error_here(c->bonus & err ? ERR_TUBE : ERR, c, line, split);
	else if (error == -2)
		print_error_here(c->bonus & err ? ERR_ROOM : ERR, c, line, split);
}
