NAME = philo_bonus

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -g3

RM = rm

RM_FLAGS = -f

SRCS = 	./srcs/lexer.c \
		./srcs/main.c \

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