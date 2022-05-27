SRCS = main.c parsing.c error.c utils1.c gnl.c parsing_map.c parsing_utils.c

DIRECTORYS = srcs/

SRCSD =	$(addprefix ${DIRECTORYS}, $(SRCS))

EFLAGS = -Wall -Wextra -Werror -g

OBJS =	${SRCSD:.c=.o}

MLXHEADER = mlx/mlx.h

OFLAGS = -c

NAME   = cub3D

%.o: %.c
	gcc ${OFLAGS} ${EFLAGS}  ${INCLUD} -o $@ $<

INCLUD = -I./include

LIBFT = -Llibft -lft

${NAME}: ${OBJS}
	(cd libft && make)
	gcc  -lmlx -framework OpenGL -framework AppKit $(EFLAGS) -o $(NAME) ${INCLUD}  ${SRCSD} ${LIBFT}
			
all:	${NAME}

clean:
		rm  -f ${OBJS}
		(cd libft && make clean)

fclean:	clean
		rm  -f ${NAME}
		(cd libft && make fclean)

mlx:	
	(cd mlx && make)
	make ${NAME}
	

mlxclean : 
	(cd mlx && make clean)
	make fclean

re:		fclean all

.PHONY:	all clean fclean re mlx mlxclean