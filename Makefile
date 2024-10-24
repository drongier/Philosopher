NAME = philo

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

SOURCES = sources/main.c \
			sources/check_errors.c \
			sources/utils.c \
			sources/philo_routine.c \
			sources/spy_philo.c

all: 
	${CC} ${FLAGS} ${SOURCES} -o ${NAME}

fclean:
	${RM} ${NAME}

re: fclean all