/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 22:15:12 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/10/28 01:19:12 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_error(char *err, t_cont *cont)
{
	free_cont(cont);
	close(0);
	get_next_line(0, (char **)-1);
	ft_putendl(err);
	if (cont->bonus & leaks)
		system("leaks -q lem-in");
	exit(1);
}
