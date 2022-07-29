SRC=atoi_errcode.c main.c philo.c timestamp.c xmutex.c \
	philo_utils.c launch_threads.c
OBJ=${SRC:.c=.o}
CFLAGS=-Wall -Wextra -Werror
CC=gcc
LIB=-lpthread
NAME=philo
BONUS_DIR=bonus
BONUS_NAME=philo_bonus

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o $@ $^ ${LIB}
	
all: ${NAME} bonus
	@#empty

bonus: 
	cd ${BONUS_DIR} && make all
	cp "${BONUS_DIR}/${BONUS_NAME}" .

clean: 
	cd ${BONUS_DIR} && make clean
	rm -rf ${OBJ}

fclean: clean
	cd ${BONUS_DIR} && make fclean
	rm -f ${NAME}
	rm -f ${BONUS_NAME}

re: fclean all
	@#empty

.PHONY: all re fclean clean bonus all
