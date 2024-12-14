NAME = philo_bonus

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -g3

RM = rm

RM_FLAGS = -f

SRCS = 	./srcs/lexer.c \
		./srcs/main.c \
		./srcs/main_philo.c \
		./srcs/initialization.c \
		./srcs/initialization_all_struct.c \
		./srcs/check_process.c \

SRCS += ./srcs/finalization/error.c \
		./srcs/finalization/free_logic.c \

SRCS += ./srcs/actions_philos/die.c \
		./srcs/actions_philos/eat.c \
		./srcs/actions_philos/sleep.c \
		./srcs/actions_philos/think.c \

SRCS += ./srcs/utils/time.c \
		./srcs/utils/libft_funcs.c

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