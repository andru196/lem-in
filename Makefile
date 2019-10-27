# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/28 20:41:38 by ycorrupt          #+#    #+#              #
#    Updated: 2019/10/28 00:33:50 by sfalia-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	lem-in
DIR_VALIDATION	=	./validation/
SRCS_VALIDATION	=	validation.c\
					validate_rooms.c\
					validate_tubes.c\
					cont_initialize.c\
					print_error.c\
					free.c\
					check.c\
					read.c
DIR_HELPERS		=	./helpers/
SRCS_HELPERS	=	add_struct.c\
					new_struct.c\
					help_func.c\
					error.c
DIR_ALGO		=	./algo/
SRCS_ALGO		=	bfs.c\
					exept.c\
					dead.c\
					pather.c\
					pather0.c\
					solover.c\
					solover0.c\
					selector.c
SRCS			=	$(addprefix $(DIR_VALIDATION), $(SRCS_VALIDATION)) \
					$(addprefix $(DIR_HELPERS), $(SRCS_HELPERS)) \
					$(addprefix $(DIR_ALGO), $(SRCS_ALGO))\
					main.c
OBJ				=	$(patsubst %.c, %.o, $(SRCS))
CC				=	clang
FLAGS			=	-Wall -Wextra -Werror -g
LIBRARY			=	./libftprintf/
LIBFT			=	$(LIBRARY)libft.a
HEADERS			=	inc/ $(LIBRARY)includes
INCLUDES		=	-I inc/ -I $(LIBRARY)includes

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LIBRARY) -lftprintf

$(LIBFT):
	make -C $(LIBRARY)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBRARY) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBRARY) fclean

re: fclean all
