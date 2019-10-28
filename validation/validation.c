/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 20:31:25 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/10/28 21:04:59 by ycorrupt         ###   ########.fr       */
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

static int		count_char(char *line, char c)
{
	int i;
	int rez;

	i = 0;
	rez = 0;
	while (line[i])
	{
		if (line[i] == c)
			rez++;
		i++;
	}
	return (rez);
}

void		print_error_here(char *err, t_cont *cont, char *l, char **s)
{
	if (l)
		free(l);
	if (s)
		frees_split(s);
	print_error(err, cont);
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
		if (!(split = ft_strsplit(line, ' ')))
			print_error_here(cont->bonus & err ? ERR_MAL : ERR, cont, line, split);
		if ((count = count_splits(split)) == 3 && *comment_flag != 12345)
			validate_rooms(split, comment_flag, cont, line);
		else if (count == 1 && (*comment_flag != 1 && *comment_flag != -1))
		{
			frees_split(split);
			if (!(split = ft_strsplit(line, '-')))
				print_error_here(cont->bonus & err ? ERR_MAL : ERR, cont, line, split);
			if (count_splits(split) != 2 || count_char(line, '-') != 1)
				print_error_here(cont->bonus & err ? ERR_LINE : ERR, cont, line, split);
			validate_tubes(split, cont, line);
			*comment_flag = 12345;
		}
		else
			print_error_here(cont->bonus & err ? ERR_LINE : ERR, cont, line, split);
		frees_split(split);
	}
}
