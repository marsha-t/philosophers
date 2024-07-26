NAME = philo
CFILES = main.c check.c init.c exit.c monitor.c philos_cycle.c cycle.c single_philo.c utils.c 
OFILES = ${CFILES:.c=.o}
CFLAGS = -Wall -Wextra -Werror -pthread 


all: $(NAME)

%o: %c 
	cc ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OFILES)
	cc $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	rm -f $(OFILES) 

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re
