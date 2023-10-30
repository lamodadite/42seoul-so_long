SRCS 	= main.c
OBJS	= $(SRCS:%.c=%.o)
NAME	= a.out
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror
CLIB	= -Lmlx -lmlx -framework OpenGL -framework Appkit
PRINTF	= ./ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(PRINTF) $(OBJS) 
	$(CC) $(OBJS) $(PRINTF) $(CLIB) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(PRINTF):
	@make -C ./ft_printf

bonus :
	make all

clean:
	$(RM) $(OBJS) $(OBJS_BNS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
