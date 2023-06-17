NAME_S = server
NAME_C = client
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCL = minitalk.h
SRCS_S = server.c libftprintf_main.c ft_conversions.c
SRCS_C = client.c libftprintf_main.c ft_conversions.c

OBJS_S = $(SRCS_S:.c=.o)
OBJS_C = $(SRCS_C:.c=.o)

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(OBJS_S) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS_S) -o $(NAME_S) -I$(INCL)

$(NAME_C): $(OBJS_C) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS_C) -o $(NAME_C) -I$(INCL)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_S) $(OBJS_C)

fclean: clean
	rm -f $(NAME_S) $(NAME_C)

re: fclean all

.PHONY: all clean fclean re
