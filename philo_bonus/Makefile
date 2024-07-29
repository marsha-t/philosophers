NAME = philo_bonus
CFILES = main_bonus.c check_bonus.c init_bonus.c exit_bonus.c cycle_bonus.c monitor_bonus.c \
	single_philo_bonus.c philos_bonus.c utils_bonus.c libft_bonus.c
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
