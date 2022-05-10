SRCS = 

MAIN = main.c

DIRECTORYS = srcs/

SRCSD =	$(addprefix ${DIRECTORYS}, $(SRCS))

EFLAGS = -Wall -Wextra -Werror

OBJS =	${SRCSD:.c=.o}

MLXHEADER = mlx/mlx.h

HEADER = include/so_long.h

OFLAGS = -c

NAME   = cub3D

HEAD = -I./include

%.o: %.c ${HEADER}
	gcc ${OFLAGS} ${EFLAGS} -o $@ $<

${NAME}: ${OBJS}
	gcc  -lmlx -framework OpenGL -framework AppKit $(EFLAGS) -o $(NAME) $(MAIN) ${HEAD} ${SRCSD}
			
all:	${NAME}

clean:
		rm  -f ${OBJS}

fclean:	clean
		rm  -f ${NAME}

mlx:	
	(cd mlx && make)
	make ${NAME}
	

mlxclean : 
	(cd mlx && make clean)
	make fclean

re:		fclean all

.PHONY:	all clean fclean re mlx mlxclean