CC = cc
CFLAGS = -Werror -Wall -Wextra -pthread
SRCS = philo_main_bonus.c philo_set_bonus.c philo_utils_bonus.c philo_utils2_bonus.c philo_process_bonus.c philo_thread_bonus.c philo_monitor_bonus.c philo_libft_bonus.c
OBJS = $(SRCS:.c=.o)
NAME = philo_bonus

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