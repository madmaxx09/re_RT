PROG	= mini_rt

SRCS 	= main.c store_data.c store_more.c store_utils.c array_to_double.c parse.c custom_malloc.c mlx_press.c raytrace.c \
			vec_math.c rgb_math.c more_math.c viewport.c random.c obj_inter.c 
OBJS 	= ${SRCS:.c=.o}

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g

.c.o:		%.o : %.c
					@gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all: 		${PROG}

${PROG}:	${OBJS}
					@echo "Compiling...\n"
					@make re -C ./libft
					@$(CC) ${OBJS}  -Llibft -lft -o ${PROG} -lmlx -framework OpenGL -framework AppKit
					@echo "mini_rt compiled"

clean:
					@make clean -C ./libft
					@rm -f ${OBJS} ${OBJS_B}
					@echo "Cleaned\n"

fclean: 	clean
					@make fclean -C ./libft
					@rm -f $(NAME)
					@rm -f ${PROG}
					@echo "F_Cleaned\n"

re:			fclean all

.PHONY: all clean fclean re%