/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:44:19 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/10/28 21:11:26 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		validate_num_of_ants(char *line, t_cont *cont)
{
	int i;
	int erro;

	i = 0;
	erro = 0;
	if (line[0] == '-')
		erro = 1;
	else if (line[0] == '+')
		++line;
	if (ft_strlen(line) > 10 ||
				(ft_strlen(line) == 10 && ft_strcmp("2147483647", line) < 0))
		erro = 1;
	while (line[i])
		if (!(ft_isdigit(line[i++])))
			erro = 1;
	if ((cont->num_of_ants = ft_atoi(line)) == 0)
		erro = 1;
	if (erro == 1)
	{
		free(line);
		print_error(cont->bonus & err ? ERR_ANTS : ERR, cont);
	}
}

static void		i_love_norme(void)
{
	return ;
}

/*
** Чтение данных со стандартного инпута.
*/

void			read_data(t_cont *cont)
{
	int		comment_flag;
	char	*line;
	int		ret;

	comment_flag = 0;
	if (get_next_line(0, &line) == 1)
	{
		cont->bonus & quiet ? i_love_norme() : ft_putendl(line);
		validate_num_of_ants(line, cont);
		free(line);
	}
	else
		print_error(cont->bonus & err ? ERR_MAP : ERR, cont);
	while ((ret = get_next_line(0, &line)) == 1)
	{
		if (ft_strlen(line) == 0)
			break ;
		cont->bonus & quiet ? i_love_norme() : ft_putendl(line);
		validate_data(line, cont, &comment_flag);
		free(line);
	}
	if (ret == 1)
		free(line);
	check_data(cont);
}
