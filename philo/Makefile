NAME = philo

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -g3

RM = rm

RM_FLAGS = -f

SRCS = 	./srcs/initialization.c \
	 	./srcs/initialization_all_struct.c \
		./srcs/lexer.c \
		./srcs/main_philo.c \
		./srcs/main.c \

SRCS +=	./srcs/actions_philos/eat.c \
		./srcs/actions_philos/sleep.c \
		./srcs/actions_philos/think.c \
		./srcs/actions_philos/die.c \

SRCS +=	./srcs/utils/libft_funcs.c \
		./srcs/utils/time.c \

SRCS +=	./srcs/finalization/error.c \
		./srcs/finalization/free_logic.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CC_FLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(RM_FLAGS) $(OBJS)

fclean: clean
	$(RM) $(RM_FLAGS) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re