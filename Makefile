SRC=atoi_errcode.c main.c philo.c timestamp.c xmutex.c \
	philo_utils.c launch_threads.c
OBJ=${SRC:.c=.o}
CFLAGS=-Wall -Wextra -Werror
CC=gcc
LIB=-lpthread
NAME=philo

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
