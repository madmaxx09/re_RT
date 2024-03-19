PROG	= mini_rt

SRCS 	= main.c store_data.c store_more.c store_utils.c array_to_double.c parse.c custom_malloc.c mlx_press.c raytrace.c \
			vec_math.c rgb_math.c
OBJS 	= ${SRCS:.c=.o}

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g

.c.o:		%.o : %.c
					@gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all: 		${PROG}

${PROG}:	${OBJS}
					@echo "Compiling...\n"
					@make re -C ./LIBFT
					@$(CC) ${OBJS}  -Llibft -lft -o ${PROG} -lmlx -framework OpenGL -framework AppKit
					@echo "mini_rt compiled"

clean:
					@make clean -C ./LIBFT
					@rm -f ${OBJS} ${OBJS_B}
					@echo "Cleaned\n"

fclean: 	clean
					@make fclean -C ./LIBFT
					@rm -f $(NAME)
					@rm -f ${PROG}
					@echo "F_Cleaned\n"

re:			fclean all

.PHONY: all clean fclean re%