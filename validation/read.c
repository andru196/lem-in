/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:44:19 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/10/09 18:36:27 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		validate_num_of_ants(char *line, t_cont *cont)
{
	int i;

	i = 0;
	if (line[0] == '-')
		print_error("ERROR: IVALID NUMBER OF ANTS");
	else if (line[0] == '+')
		++line;
	if (ft_strlen(line) > 10 ||
				(ft_strlen(line) == 10 && ft_strcmp("2147483647", line) < 0))
		print_error("ERROR: IVALID NUMBER OF ANTS");
	while (line[i])
		if (!(ft_isdigit(line[i++])))
			print_error("ERROR: IVALID NUMBER OF ANTS");
	if ((cont->num_of_ants = ft_atoi(line)) == 0)
		print_error("ERROR: IVALID NUMBER OF ANTS");
}

/*
** Чтение данных со стандартного инпута.
*/

void			read_data(t_cont *cont)
{
	int		comment_flag;
	char	*line;

	comment_flag = 0;
	if (get_next_line(0, &line) == 1)
	{
		validate_num_of_ants(line, cont);
		ft_putendl(line);
		free(line);
	}
	else
		print_error("ERROR: IVALID MAP");
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strlen(line) == 0)
			break ;
		validate_data(line, cont, &comment_flag);
		ft_putendl(line);
		free(line);
	}
	ft_putendl("");
	check_data(cont);
}
