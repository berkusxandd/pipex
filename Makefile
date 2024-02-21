NAME = pipex

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

LIBFT = ./Libft/libft.a

SRCS = ./src/pipex.c\

$(NAME) :
	$(CC) $(SRCS) $(LIBFT) -o $(NAME)

all : $(NAME)

fclean : clean
		$(RM) $(NAME)
		make fclean -C libft.a

clean :
		$(RM) $(NAME)
		make clean -C libft.a