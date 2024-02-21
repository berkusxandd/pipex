NAME = pipex

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

LIBFT = ./Libft/libft.a

SRCS = ./src/pipex.c\
		./src/utils.c

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

all : $(NAME)

re :	fclean all

fclean : clean
		$(RM) $(NAME)

clean :
		$(RM) $(NAME)
