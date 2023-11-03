SRCS 	= ft_printf.c ft_printf_utils.c format.c
OBJS	= $(SRCS:%.c=%.o)
NAME	= libftprintf.a
LIBC	= ar rc
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $^

bonus :
	make all

clean:
	$(RM) $(OBJS) $(OBJS_BNS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
