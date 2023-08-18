NAME    =   pipex
SRCS    =   pipex.c
INC     =   -I libft
LIB     =   -L libft -lft
CFLAGS  =   -g -Wall -Wextra -Werror $(INC)
OBJS    =   $(SRCS:.c=.o)

all : $(NAME)

debug : $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	gcc $(OBJS) -o $(NAME) $(LIB)

$(OBJS) : $(SRCS)
	gcc $(CFLAGS) -c $(SRCS)

clean :
	make -C libft clean
	rm -f $(OBJS)

fclean :
	make -C libft fclean
	make -C . clean
	rm -f $(NAME)

re :
	make -C . clean
	make -C . fclean
	make -C .
