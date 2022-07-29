SRC=atoi_errcode.c killer_thread.c main.c philo.c satiation_thread.c sems.c\
	timestamp.c
OBJ=${SRC:.c=.o}
CFLAGS=-Wall -Wextra -Werror
CC=gcc
LIB=-lpthread
NAME=philo_bonus

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o $@ $^ ${LIB}
	
all: ${NAME}
	@#empty

bonus: all
	@#empty

clean: 
	rm -rf ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all
	@#empty

.PHONY: all re fclean clean bonus all
