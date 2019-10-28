/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:17:21 by andru196          #+#    #+#             */
/*   Updated: 2019/10/28 00:42:12 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#define MAX 0x7fffffff
#define MID 0x3fffffff


# include "ft_printf.h"
# include "libft.h"
# include <stdio.h>

# define ERR "ERROR"
# define ERR_ANTS "ERROR: IVALID NUMBER OF ANTS"
# define ERR_MAP "ERROR: IVALID MAP"
# define ERR_MAL "ERROR: MALLOC"
# define ERR_LINE "ERROR: WRONG LINE"
# define ERR_INV_COORD "ERROR: INVALID COORDINATE"
# define ERR_INV_NAME "ERROR: INVALID NAME"
# define ERR_NAME "ERROR: ROOM NAME ALREADY EXISTS"
# define ERR_COORD "ERROR: COORDINATES ALREADY OCCUPIED"
# define ERR_START "ERROR: NO START ROOM"
# define ERR_END "ERROR: NO END ROOM"
# define ERR_TUBE "ERROR: TUBE CONNECTS THE SAME ROOM"
# define ERR_ROOM "ERROR: ROOM NAME DOESN'T EXISTS"
# define ERR_PATH "ERROR: NO PATH TO END" //check leaks

typedef struct s_ant	t_ant;
typedef enum e_mark		t_mark;
typedef struct s_rooms	t_rooms;
typedef struct s_paths	t_paths;
typedef struct s_room	t_room;
typedef enum e_bonus    t_bonus;

enum                    e_bonus
{
    leaks = 1 << 0,
    quiet = 1 << 1,
    stat = 1 << 2,
    err = 1 << 3
};

typedef struct			s_lst
{
	void				*cont;
	struct s_lst		*nxt;
}						t_lst;

/*
** Комната хранит соединения со всеми комнатами
*/

struct					s_ant
{
	t_room			*cur_pos;
	int				num;
};

struct					s_rooms
{
	t_room	**room;
	size_t	len;
	size_t	max;
};

enum					e_mark
{
	start = 1 << 0,
	end = 1 << 1,
	closed = 1 << 2,
	deadlock = 1 << 3,
	tunnel = 1 << 4,
	reserved = 1 << 5,
};

struct					s_room
{
	t_ant				*ant;
	t_lst				*tubes;
	t_rooms				*crossroad;
	char				*name;
	int					path;
	int					path_to_end;
	int					reg;
	int					x;
	int					y;
	int					tubes_len;
	int					visit;
	t_room				*parent;
	t_mark				mark;
	struct s_room		*next;
};

struct					s_paths
{
	t_rooms				**path;
	size_t				len;
	size_t				max;
};

/*
** соединения хранят расстояние до финиша,
** соединяемые комнаты и список муравьёв
** с указанием номера хода
** каждый ход ко всем соединениям добавляется
** ход с/без муравьём
*/

typedef struct			s_tube
{
	int					lenth;
	int					p_len;
	t_room				*out;
	t_room				*in;
	t_ant				*ant;
	int					status;
	struct s_tube		*next;
}						t_tube;

/*
** Содержит полезные данные:
** всё что разумно многократно передавать
** num_of_ants - кол-во муравье
** rooms - массив указателей на структуры комнат (комнаты)
** tubes - массив указателей на структуры связей (тоннели)
** start - первая комната
** end - последняя комната
** num_of_rooms - кол-во комнат
*/

typedef struct			s_cont
{
	size_t	num_of_ants;
	size_t	num_of_deep;
	size_t	efficiency;
	size_t	num_of_rooms;
	size_t	num_of_tubes;
	t_ant	*ants;
	t_room	*rooms;
	t_tube	*tubes;
	t_room	*start;
	t_room	*end;
	t_paths	*paths;
    t_bonus bonus;
    size_t  steps;
}						t_cont;

/*
** Алоцирование
*/

t_room					*newroom(char *name, int x, int y);
t_ant					*newant(int num, t_room *start);
t_lst					*newlst(void *cont);
void					cont_initialize(t_cont *cont);
t_tube					*newtube(t_room *r1, t_room *r2);
void					add_tube(t_room *dist, t_tube *what);
void					add_cross(t_room *dist, t_tube *what);
void					room_to_end(t_room *start, t_room *new);
void					tube_to_end(t_tube *start, t_tube *new);

/*
** Валидация
*/

void					read_data(t_cont *cont);
void					frees_split(char **split);
void					validate_data(char *line, t_cont *cont,
						int *comment_flag);
void                    validate_rooms(char **split, int *flag, t_cont *cont, char *line);
void                    validate_tubes(char **split, t_cont *cont, char *line);
void					check_data(t_cont *cont);
void                    print_error_here(char *err, t_cont *cont, char *l, char **s);

/*
** Вывод
*/

void                    print_error(char *err, t_cont *cont);
void					cont_initialize(t_cont *cont);

/*
** Алгоритмический мусор
*/

int						num_of_rooms(t_room *frst, int path);
int						num_of_tubes(t_tube *frst, int status);
void					dist_counter(t_room *start, int len, t_room *finish);
void					calc(t_room *finish, int len);
void					router(t_cont *c);
void					ptlc(t_tube *first, t_room *start, int len);
t_room					*room_selector(t_ant *ant, t_room *start);
void					solover(t_cont *c);
t_room					**arr_init(t_room *room, int len);
void					add_room(t_room **rooms, t_tube *c, t_room
						*current, t_room *finish);
void					remove_rooms(t_room **rooms);
t_room					*other_room(t_tube *t, t_room *current);
void					deadlock_detect(t_cont *c);
void					free_cont(t_cont *cont);
void					error_exit(t_cont *c, int code);
void					bfs(t_cont *c);
void					tunnels(t_cont *c);
void					path(t_cont *c);
void					start_end_exception(t_cont *c);
int						num_check(t_room *dest, int *dists, t_cont *c);
void					print_move(t_ant *ant, t_room *dest, int flag);
void					end_turn(t_tube *frst);
void					pre_path(t_cont *c);

#endif
