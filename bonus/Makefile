NAME = philo_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.# -fsanitize=address -g3
PTHREAD = -pthread
RM = rm -f

MAIN = main.c
SRC = philo_bonus.c philo_utils_bonus.c main_utils_bonus.c
OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	@${CC} ${CFLAGS} ${MAIN} ${PTHREAD} ${OBJ} -o ${NAME}

clean:
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY = all clean fclean re
