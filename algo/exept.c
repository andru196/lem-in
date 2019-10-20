/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exept.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:14:57 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/20 17:28:03 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			start_end_exception(t_cont *c)
{
	size_t	i;

	i = -1;
	while (++i < c->end->crossroad->len)
		if (c->end->crossroad->room[i] == c->start)
			break ;
	c->end->crossroad->len--;
	if (i != c->end->crossroad->len)
		ft_memcpy(&c->end->crossroad->room[i], &c->end->crossroad->room[i + 1],
		sizeof(void *) * c->end->crossroad->len - i);
	i = -1;
}
