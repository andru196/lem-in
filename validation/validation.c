/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:31:25 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/10/20 17:39:12 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		count_splits(char **split)
{
	int count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

static void		validate_comment(char *line, int *comment_flag)
{
	if (ft_strequ(line, "##start"))
		*comment_flag = 1;
	else if (ft_strequ(line, "##end"))
		*comment_flag = -1;
}

/*
** Проверка валидности вводимых данных: комментарии, комнаты, связи.
** flag_comment сначала для определения комментариев старта/энда.
** 12345 означает начало считывания связей труб.
*/

void			validate_data(char *line, t_cont *cont, int *comment_flag)
{
	char	**split;
	int		count;

	if (line[0] == '#' && (!(*comment_flag) || *comment_flag == 12345))
		validate_comment(line, comment_flag);
	else
	{
		split = ft_strsplit(line, ' ');
		if ((count = count_splits(split)) == 3 && *comment_flag != 12345)
			validate_rooms(split, comment_flag, cont);
		else if (count == 1 && (*comment_flag != 1 && *comment_flag != -1))
		{
			frees_split(split);
			if (count_splits(split = ft_strsplit(line, '-')) != 2)
				print_error("ERROR: WRONG LINE");
			validate_tubes(split, cont);
			*comment_flag = 12345;
		}
		else
		{
			frees_split(split);
			print_error("ERROR: WRONG LINE");
		}
		frees_split(split);
	}
}
