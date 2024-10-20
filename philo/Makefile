CC = cc
CFLAGS = -Werror -Wall -Wextra -pthread
SRCS = philo_main.c philo_thread.c philo_utils.c philo_utils2.c philo_utils3.c philo_utils4.c philo_monitor.c 
OBJS = $(SRCS:.c=.o)
NAME = philo

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT_SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I./

%.o : %.c
	$(CC) $(CFLAGS) -c $^

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : re fclean clean all