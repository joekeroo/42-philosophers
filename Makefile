NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
PTHREAD = -pthread
RM = rm -f

MAIN = main.c
SRC = philo.c philo_utils.c
OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${MAIN} ${PTHREAD} ${OBJ} -o ${NAME}

clean:
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY = all clean fclean re
