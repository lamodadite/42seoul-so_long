SRCS 	= srcs/main.c srcs/utils.c srcs/get_next_line.c srcs/get_next_line_utils.c
OBJS	= $(SRCS:%.c=%.o)
NAME	= a.out
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror
CLIB	= -Lmlx -lmlx -framework OpenGL -framework Appkit
PRINTF	= ./ft_printf/libftprintf.a
#LIBFT	= ./libft/libft.a

all: $(NAME)

$(NAME): $(PRINTF) $(OBJS)
	$(CC) $(OBJS) $(PRINTF) $(CLIB) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(PRINTF):
	make -C ./ft_printf

#$(LIBFT):
#	make -C ./libft

bonus :
	make all

clean:
	$(RM) $(OBJS) $(OBJS_BNS)
	@make -C ./ft_printf clean
#	@make -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	@make -C ./ft_printf fclean
#	@make -C ./libft fclean

re: fclean all

.PHONY : all clean fclean re
