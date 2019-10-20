/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 19:32:01 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/09/29 20:36:04 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		frees_split(char **split)
{
	char	**cpy;

	cpy = split;
	while (*split)
		free(*split++);
	if (cpy)
		free(cpy);
}
