NAME = philo_bonus
CFILES = main.c parse.c 
# init.c 
# forks.c utils.c actions.c exit.c cycle.c monitor.c
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
