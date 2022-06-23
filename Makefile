SRCS = main.c parsing_map.c gnl.c gnl_utils.c parsing.c parsing_utils.c raycasting.c mouve.c \
utils1.c utils2.c error.c event.c event2.c minimap.c texndda.c utils3.c

DIRECTORYS = srcs/

BONUSD = bonus/

SRCSD =	$(addprefix ${DIRECTORYS}, $(SRCS))

SRCSB =	$(addprefix ${BONUSD}, $(SRCS))

EFLAGS = -Wall -Wextra -Werror -ffast-math

OBJS =	${SRCSD:.c=.o}

BONUSO = ${SRCSB:.c=.o}

MLXHEADER = mlx/mlx.h

OFLAGS = -c

NAME   = cub3D

%.o: %.c
	gcc ${OFLAGS} ${EFLAGS}  ${INCLUD} -o $@ $<

INCLUD = -I./include -I./mlx

LIBFT = -Llibft -lft

MLXL = -Lmlx -lmlx

${NAME}: ${OBJS}
	(cd libft && make)
	(cd mlx && make)
	gcc -lmlx -framework OpenGL -framework AppKit $(EFLAGS) -o $(NAME) ${INCLUD}  ${SRCSD} ${LIBFT} ${MLXL}


all:	${NAME}

clean:
		rm  -f ${OBJS}
		(cd libft && make clean)
		(cd mlx && make clean)

fclean:	clean
		rm  -f ${NAME}
		(cd libft && make fclean)

bonus: ${BONUSO}
	(cd libft && make)
	(cd mlx && make)
	gcc -lmlx -framework OpenGL -framework AppKit $(EFLAGS) -o $(NAME) ${INCLUD}  ${SRCSB} ${LIBFT} ${MLXL}
	
bonusclean:
		rm  -f ${BONUSO}

mlxclean : 
	(cd mlx && make clean)
	make fclean

re:		fclean all

.PHONY:	all clean fclean re mlx mlxclean bonus bonusclean