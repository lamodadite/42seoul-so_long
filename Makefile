SRCS 	= srcs/so_long.c srcs/utils.c srcs/get_next_line.c srcs/get_next_line_utils.c srcs/map.c srcs/move.c srcs/exit.c srcs/check.c
OBJS	= $(SRCS:%.c=%.o)
NAME	= so_long
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
	make -C ./ft_printf

bonus :
	make all

clean:
	$(RM) $(OBJS) $(OBJS_BNS)
	@make -C ./ft_printf clean

fclean: clean
	$(RM) $(NAME)
	@make -C ./ft_printf fclean

re: fclean all

.PHONY : all clean fclean re
