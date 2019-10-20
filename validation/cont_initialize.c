/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_initialize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:22:38 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/10/11 17:55:46 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	cont_initialize(t_cont *cont)
{
	cont->num_of_rooms = 0;
	cont->num_of_deep = 0;
	cont->num_of_ants = 0;
	cont->num_of_tubes = 0;
	cont->rooms = NULL;
	cont->tubes = NULL;
	cont->start = NULL;
	cont->end = NULL;
}
